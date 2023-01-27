from cProfile import label
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
import sys
from source_arduino import *

## Global variable - font
font = 'Times'

## Global variable - 3 font sizes
fontsizes = [12, 16, 24]

## Shortcut to define a label
def label_shortcut(text, align = 0, size = 0):
    label = QLabel(text)
    alignment = [Qt.AlignLeft, Qt.AlignHCenter, Qt.AlignRight]
    label.setAlignment(alignment[align])
    label.setFont(QFont(font, fontsizes[size]))
    return label

## Shortcut to define a button
def button_shortcut(text, size = 0):
    button = QPushButton(text)
    button.setFont(QFont(font, fontsizes[size]))
    return button

## Main class
# Initializes the Application, opens, controls and closes the windows
class Master():
    def __init__(self):
        super().__init__()
        self.mode = -1
        self.app = QApplication(sys.argv)
        self.app.setQuitOnLastWindowClosed(False)
        self.running = False

    ## Runs the main window
    def run(self):
        window = StartWindow()
        window.show()
        self.app.exec()
    
    ## Called when an operation mode is selected
    def selected(self):
        if self.mode == 0:
            # ---- Humidity control ----
            # Important to save as class variable
            self.window = HumidityWindow()
            self.window.show()
        elif self.mode == 1:
            # ---- Pre-scheduled ----
            # Important to save as class variable
            self.window = ScheduledWindow()
            self.window.show()

    ## Called to exit the Application
    def exit_clicked(self):
        if self.ser != None:
            stop_serial(self.ser)
        self.app.quit()

## Controls the Start window, where an operation mode is selected
class StartWindow(Master, QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("H2O Delivery System")
        self.setContentsMargins(40, 40, 40, 40)
        grid_layout = QGridLayout()
        grid_layout.setSpacing(40)
        widget = QWidget()
        widget.setLayout(grid_layout)
        self.setCentralWidget(widget)

        label = label_shortcut("Welcome!", 1 , 2)
        grid_layout.addWidget(label, 0, 0, 1, 1)

        label2 = label_shortcut("Select operation mode:", 1, 0)
        grid_layout.addWidget(label2, 1, 0, 1, 1)
        
        self.ser = start_serial(False)

        self.combo = QComboBox(self)
        self.combo.addItem("Humidity control mode")
        self.combo.addItem("Pre-scheduled mode")
        self.combo.setFont(QFont(font, fontsizes[0]))
        self.combo.setCurrentIndex(get_mode(self.ser))
        grid_layout.addWidget(self.combo, 2, 0, 1, 1)
        
        stop_serial(self.ser)

        start = button_shortcut("Start", 1)
        start.clicked.connect(self.start_clicked)
        grid_layout.addWidget(start, 3, 0, 1, 1)

        develop_label = label_shortcut("Developed by:\n\nAna Sousa\nDuarte Marques\nJoão Chaves", 1, 1)
        grid_layout.addWidget(develop_label, 4, 0, 1, 1)

    ## Handler for the Start button
    def start_clicked(self):
        self.mode = self.combo.currentIndex()
        self.running = True
        self.close()
        self.selected()

    ## Handler for the Close button
    # @warning Will ignore the event if the program is running normally, otherwise the Application closes prematurely.
    def closeEvent(self, event):
        if not self.running:
            self.exit_clicked()

## Humidity control mode window
class HumidityWindow(Master, QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("H2O Delivery System")
        self.setContentsMargins(40, 40, 40, 40)
        grid_layout = QGridLayout()
        grid_layout.setSpacing(40)
        widget = QWidget()
        widget.setLayout(grid_layout)
        self.setCentralWidget(widget)

        self.ser = start_serial()
        self.source = get_source(self.ser)

        label = label_shortcut("Humidity control mode", 1, 2)
        grid_layout.addWidget(label, 0, 0, 1, 2)

        source_label = label_shortcut("Select source:", 0, 0)
        grid_layout.addWidget(source_label, 1, 0, 1, 1)

        self.combo = QComboBox(self)
        self.combo.addItem("Water tank")
        self.combo.addItem("Well pump")
        self.combo.setFont(QFont(font, fontsizes[0]))
        self.combo.setCurrentIndex(self.source)
        grid_layout.addWidget(self.combo, 1, 1, 1, 1)

        current_parameters = label_shortcut("Current parameters:", 0, 0)
        grid_layout.addWidget(current_parameters, 2, 0, 1, 1)

        self.current_parameters2 = label_shortcut("-", 1, 0)
        grid_layout.addWidget(self.current_parameters2, 2, 1, 1, 1)
        self.update_parameters()  

        tabs = QTabWidget()
        tabs.setFont(QFont(font, fontsizes[1]))
        tabs.addTab(self.calibrate_tab(), "Calibrate")
        tabs.addTab(self.manual_tab(), "Manual")
        grid_layout.addWidget(tabs, 3, 0, 1, 2)

    ## Updates the current parameters label
    def update_parameters(self):
        now, minH, maxH = get_humidity(self.ser, True)
        if (maxH != None):
            self.current_parameters2.setText("{:.2f}%".format(minH*100) + " ↔ " + "{:.2f}%".format(maxH*100))
        else:
            self.current_parameters2.setText("-")    

    ## Calibrate mode
    def calibrate_tab(self):
        calibrateTab = QWidget()
        grid_layout = QGridLayout()
        grid_layout.setSpacing(20) 

        calibrate = button_shortcut("Calibrate", 1)
        calibrate.clicked.connect(self.calibrate_clicked)
        grid_layout.addWidget(calibrate, 0, 0, 1, 2)

        calibrate_result = label_shortcut("Calibration result:", 0, 0)
        grid_layout.addWidget(calibrate_result, 1, 0, 1, 1)

        self.calibrate_result2 = label_shortcut("-", 1, 0)
        grid_layout.addWidget(self.calibrate_result2, 1, 1, 1, 1)
        self.calib = -1

        margin_label = label_shortcut("Set margin (%): ", 0, 0)
        grid_layout.addWidget(margin_label, 2, 0, 1, 1)

        self.margin_spinbox = QDoubleSpinBox()
        self.margin_spinbox.setMinimum(0.1)
        self.margin_spinbox.setMaximum(20)
        self.margin_spinbox.setValue(10)
        self.margin_spinbox.setSingleStep(0.5)
        self.margin_spinbox.setFont(QFont(font, fontsizes[0]))
        grid_layout.addWidget(self.margin_spinbox, 2, 1, 1, 1)     

        send = button_shortcut("Send", 1)
        send.clicked.connect(self.send_clicked_calibrate)
        grid_layout.addWidget(send, 3, 0, 1, 2)

        calibrateTab.setLayout(grid_layout)
        return calibrateTab

    ## Handler for the Calibrate button
    def calibrate_clicked(self):
        self.calib = get_humidity(self.ser)
        self.calibrate_result2.setText("{:.2f}%".format(self.calib*100))

    ## Handler for the Calibrate Send button
    def send_clicked_calibrate(self):
        if self.calib > 0:
            m = self.margin_spinbox.value()/100
            if not set_humidity(self.ser, int(max(self.calib-m, 0)*1023), int(min(self.calib+m, 1)*1023)):
                dlg = CustomDialog("Warning!", "Unable to set humidity parameters")
                dlg.exec()
            else:
                dlg = CustomDialog("Sucess!", "Humidity parameters set correctly.")
                dlg.exec()
            self.update_parameters()
            if self.source != self.combo.currentIndex():
                self.source = self.combo.currentIndex()
                if not set_source(self.ser, self.combo.currentIndex()):
                    dlg = CustomDialog("Warning!", "Unable to set source")
                    dlg.exec()
                else:
                    dlg = CustomDialog("Success!", "Source set correctly.")
                    dlg.exec()
        else:
            dlg = CustomDialog("Warning!", "No calibration performed yet.")
            dlg.exec()

    ## Manual mode
    def manual_tab(self):
        calibrateTab = QWidget()
        grid_layout = QGridLayout()
        grid_layout.setSpacing(20) 

        label = label_shortcut("Set parameters:", 1, 1)
        grid_layout.addWidget(label, 0, 0, 1, 2)

        min_label = label_shortcut("Minimum humidity (%):")
        grid_layout.addWidget(min_label, 1, 0, 1, 1)

        self.min_spin = QDoubleSpinBox()
        self.min_spin.setMinimum(0)
        self.min_spin.setMaximum(100)
        self.min_spin.setValue(0)
        self.min_spin.setSingleStep(0.1)
        self.min_spin.setFont(QFont(font, fontsizes[0]))
        grid_layout.addWidget(self.min_spin, 1, 1, 1, 1)

        max_label = label_shortcut("Maximum humidity (%):")
        grid_layout.addWidget(max_label, 2, 0, 1, 1)

        self.max_spin = QDoubleSpinBox()
        self.max_spin.setMinimum(0)
        self.max_spin.setMaximum(100)
        self.max_spin.setValue(0)
        self.max_spin.setSingleStep(0.1)
        self.max_spin.setFont(QFont(font, fontsizes[0]))
        grid_layout.addWidget(self.max_spin, 2, 1, 1, 1)

        suggestion_label = label_shortcut("Suggestion: ~30% is dry soil and ~45% is moist soil.")
        grid_layout.addWidget(suggestion_label, 3, 0, 1, 2)

        send = button_shortcut("Send", 1)
        send.clicked.connect(self.send_clicked_manual)
        grid_layout.addWidget(send, 4, 0, 1, 2)

        calibrateTab.setLayout(grid_layout)
        return calibrateTab

    ## Handler for the Manual Send button
    def send_clicked_manual(self):
        minH = int(self.min_spin.value() / 100 * 1023)
        maxH = int(self.max_spin.value() / 100 * 1023)
        if maxH <= minH:
            dlg = CustomDialog("Warning!", "Invalid range selected.")
            dlg.exec()
            return
        if not set_humidity(self.ser, minH, maxH):
            dlg = CustomDialog("Warning!", "Unable to set humidity parameters")
            dlg.exec()
        else:
            dlg = CustomDialog("Sucess!", "Humidity parameters set correctly.")
            dlg.exec()
        self.update_parameters()
        if self.source != self.combo.currentIndex():
            self.source = self.combo.currentIndex()
            if not set_source(self.ser, self.combo.currentIndex()):
                dlg = CustomDialog("Warning!", "Unable to set source")
                dlg.exec()
            else:
                dlg = CustomDialog("Success!", "Source set correctly.")
                dlg.exec()

    ## Handler for the Close button
    def closeEvent(self, event):
        self.exit_clicked()

## Pre-scheduled mode window
class ScheduledWindow(Master, QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("H2O Delivery System")
        self.setContentsMargins(40, 40, 40, 40)
        grid_layout = QGridLayout()
        grid_layout.setSpacing(40)
        widget = QWidget()
        widget.setLayout(grid_layout)
        self.setCentralWidget(widget)

        self.ser = start_serial()
        self.source = get_source(self.ser)

        label = label_shortcut("Pre-scheduled mode", 1, 2)
        grid_layout.addWidget(label, 0, 0, 1, 2)

        source_label = label_shortcut("Select source:", 0, 0)
        grid_layout.addWidget(source_label, 1, 0, 1, 1)

        self.combo = QComboBox(self)
        self.combo.addItem("Water tank")
        self.combo.addItem("Well pump")
        self.combo.setFont(QFont(font, fontsizes[0]))
        self.combo.setCurrentIndex(self.source)
        grid_layout.addWidget(self.combo, 1, 1, 1, 1)

        tabs = QTabWidget()
        tabs.setFont(QFont(font, fontsizes[1]))
        tabs.addTab(self.daily_mode(), "Daily")
        tabs.addTab(self.weekly_mode(), "Weekly")
        grid_layout.addWidget(tabs, 6, 0, 1, 2)
        tabs.setCurrentIndex(get_mode(self.ser, True)-1)

    ## Create the Daily mode tab
    def daily_mode(self):
        mode, interval, self.daily_times = get_prescheduled(self.ser)
        if mode != 1:
            interval = 1
            self.daily_times = []
        else:
            if interval == None:
                interval = 1
            if self.daily_times == None:
                self.daily_times = []

        self.last_changed_daily = [-1, -1, -1]

        dayTab = QWidget()
        layout = QGridLayout()
        layout.setSpacing(20)

        dl = label_shortcut("Daily interval:", 1, 1)
        layout.addWidget(dl, 0, 0, 1, 1)
        dl1 = label_shortcut("1 for every day\n2 for every other day\netc.", 1, 0)
        layout.addWidget(dl1, 1, 0, 2, 1)

        self.inter = QSpinBox()
        self.inter.setMinimum(1)
        self.inter.setMaximum(28)
        self.inter.setValue(interval)
        self.inter.setSingleStep(1)
        self.inter.setFont(QFont(font, fontsizes[0]))
        layout.addWidget(self.inter, 3, 0, 2, 1)

        splt1 = label_shortcut("")
        splt1.setStyleSheet("background-color: black")
        splt1.setFixedWidth(2)
        layout.addWidget(splt1, 0, 1, 7, 1)

        sel = label_shortcut("Selected times:", 1, 1)
        layout.addWidget(sel, 0, 2, 1, 1)

        self.sel_times_daily = label_shortcut("", 1)
        layout.addWidget(self.sel_times_daily, 1, 2, 6, 1)
        self.label_update_daily()

        splt2 = label_shortcut("")
        splt2.setStyleSheet("background-color: black")
        splt2.setFixedWidth(2)
        layout.addWidget(splt2, 0, 3, 7, 1)

        sta = label_shortcut("Start time:")
        layout.addWidget(sta, 0, 4, 1, 3)

        sta_hours = QSpinBox()
        sta_hours.setMinimum(0)
        sta_hours.setMaximum(23)
        sta_hours.setValue(0)
        sta_hours.setSingleStep(1)
        sta_hours.setFont(QFont(font, fontsizes[0]))
        layout.addWidget(sta_hours, 1, 4, 1, 1)

        sta_h = label_shortcut(":", 1)
        layout.addWidget(sta_h, 1, 5, 1, 1)

        sta_mins = QSpinBox()
        sta_mins.setMinimum(0)
        sta_mins.setMaximum(59)
        sta_mins.setValue(0)
        sta_mins.setSingleStep(1)
        sta_mins.setFont(QFont(font, fontsizes[0]))
        layout.addWidget(sta_mins, 1, 6, 1, 1)

        sto = label_shortcut("Stop time:")
        layout.addWidget(sto, 2, 4, 1, 3)

        sto_hours = QSpinBox()
        sto_hours.setMinimum(0)
        sto_hours.setMaximum(23)
        sto_hours.setValue(0)
        sto_hours.setSingleStep(1)
        sto_hours.setFont(QFont(font, fontsizes[0]))
        layout.addWidget(sto_hours, 3, 4, 1, 1)

        sto_h = label_shortcut(":", 1)
        layout.addWidget(sto_h, 3, 5, 1, 1)

        sto_mins = QSpinBox()
        sto_mins.setMinimum(0)
        sto_mins.setMaximum(59)
        sto_mins.setValue(0)
        sto_mins.setSingleStep(1)
        sto_mins.setFont(QFont(font, fontsizes[0]))
        layout.addWidget(sto_mins, 3, 6, 1, 1)

        self.daily_spinboxes = [sta_hours, sta_mins, sto_hours, sto_mins]

        add = button_shortcut("Add")
        add.clicked.connect(self.time_set_daily)
        layout.addWidget(add, 4, 4, 1, 3)

        undo = button_shortcut("Undo")
        undo.clicked.connect(self.time_undo_daily)
        layout.addWidget(undo, 5, 4, 1, 3)

        clear = button_shortcut("Clear")
        clear.clicked.connect(self.time_clear_daily)
        layout.addWidget(clear, 6, 4, 1, 3)
        
        send = button_shortcut("Send", 1)
        send.clicked.connect(self.send_clicked_daily)
        layout.addWidget(send, 7, 2, 1, 1)

        dayTab.setLayout(layout)
        return dayTab

    ## Handler for the Daily mode - Set button
    def time_set_daily(self):
        if (len(self.daily_times) == 50):
            dlg = CustomDialog("Information", "Limited to 50 separate time limits.\nTry starting again or sending the current parameters,\nwhich will be automatically optimized.\nThis may result in less than 50 intervals.")
            dlg.exec()
            return
        startH = self.daily_spinboxes[0].value()
        startM = self.daily_spinboxes[1].value()
        stopH = self.daily_spinboxes[2].value()
        stopM = self.daily_spinboxes[3].value()
        if (stopH > startH or (stopH == startH and stopM > startM)):
            for i in range(len(self.daily_times)):
                if (startH == self.daily_times[i][0] and startM == self.daily_times[i][1] and stopH == self.daily_times[i][2] and stopM == self.daily_times[i][3]):
                    dlg = CustomDialog("Information", "Duplicate entry! Please try again.")
                    dlg.exec()
                    return
                later_hour = (startH >= self.daily_times[i][0])
                same_hour_later_minute = (startH == self.daily_times[i][0] and startM > self.daily_times[i][0])
                same_hour_same_minute = (startH == self.daily_times[i][0] and startM == self.daily_times[i][1])
                later_stop = (stopH > self.daily_times[i][2] or (stopH == self.daily_times[i][2] and stopM >= self.daily_times[i][3]))
                if same_hour_same_minute:
                    if later_stop:
                        self.last_changed_daily = [i, self.daily_times[i][2], self.daily_times[i][3]]
                        self.daily_times[i][2] = stopH
                        self.daily_times[i][3] = stopM
                        self.label_update_daily()
                    return
                if same_hour_later_minute:
                    self.daily_times.insert(i+1, [startH, startM, stopH, stopM])
                    self.last_changed_daily = [i+1,-1,-1]
                    self.label_update_daily()
                    return
                elif not later_hour:
                    self.daily_times.insert(i, [startH, startM, stopH, stopM])
                    self.last_changed_daily = [i,-1,-1]
                    self.label_update_daily()
                    return

            self.daily_times.append([startH, startM, stopH, stopM])
            self.label_update_daily()
            self.last_changed_daily = [len(self.daily_times) - 1,-1,-1]
            return
        else:
            dlg = CustomDialog("Warning!", "Start and stop times not compatible!")
            dlg.exec()

    ## Handler for the Daily mode - Undo button
    # @warning Only allows for 1 undo
    def time_undo_daily(self):
        if (self.last_changed_daily[0] != -1):
            if (self.last_changed_daily[1] == -1):
                self.daily_times.pop(self.last_changed_daily[0])
                self.last_changed_daily = [-1,-1,-1]
            else:
                self.daily_times[self.last_changed_daily[0]][2] = self.last_changed_daily[1]
                self.daily_times[self.last_changed_daily[0]][3] = self.last_changed_daily[2]
                self.last_changed_daily = [-1,-1,-1]
            self.label_update_daily()
        else:
            dlg = CustomDialog("Warning!", "Unable to undo any further!")
            dlg.exec()

    ## Handler for the Daily mode - Clear button
    def time_clear_daily(self):
        self.daily_times = []
        self.label_update_daily()

    ## Updated the Daily mode time selection label
    def label_update_daily(self):
        times = ""
        for i in self.daily_times:
            times += str(i[0]).zfill(2) + ":" + str(i[1]).zfill(2) + " → " + str(i[2]).zfill(2) + ":" + str(i[3]).zfill(2) + "\n"
        self.sel_times_daily.setText(times)

    ## Handler for the Daily mode - Send button
    def send_clicked_daily(self):
        # Check for consecutive or overlapping entries
        flag = True
        while flag:
            flag = False
            for i in range(len(self.daily_times)-1):
                hour_overlap = self.daily_times[i][2] > self.daily_times[i+1][0]
                minute_overlap = (self.daily_times[i][2] == self.daily_times[i+1][0]) and (self.daily_times[i][3] >= self.daily_times[i+1][1])
                if hour_overlap or minute_overlap:
                    if (self.daily_times[i][2] > self.daily_times[i+1][2] or (self.daily_times[i][2] == self.daily_times[i+1][2] and self.daily_times[i][3] >= self.daily_times[i+1][3])):
                        maxH = self.daily_times[i][2]
                        maxM = self.daily_times[i][3]
                    else:
                        maxH = self.daily_times[i+1][2]
                        maxM = self.daily_times[i+1][3]

                    self.daily_times[i] = [self.daily_times[i][0], self.daily_times[i][1], maxH, maxM]
                    self.daily_times.pop(i+1)
                    flag = True
                    break
        self.label_update_daily()
        
        if self.source != self.combo.currentIndex():
            if not set_source(self.ser, self.combo.currentIndex()):
                dlg = CustomDialog("Warning!", "Unable to set source")
                dlg.exec()

        if len(self.daily_times) == 0:
            dlg = CustomDialog("Information", "No times selected. Unable to proceed")
            dlg.exec()
            return

        if not set_daily(self.ser, self.inter.value(), self.daily_times):
            dlg = CustomDialog("Warning!", "Unable to set daily mode configurations")
            dlg.exec()
        else:
            dlg = CustomDialog("Success!", "Daily mode configurations set correctly.")
            dlg.exec()
        if self.source != self.combo.currentIndex():
            self.source = self.combo.currentIndex()
            if not set_source(self.ser, self.combo.currentIndex()):
                dlg = CustomDialog("Warning!", "Unable to set source")
                dlg.exec()
            else:
                dlg = CustomDialog("Success!", "Source set correctly.")
                dlg.exec()

    ## Create the Weekly mode tab
    def weekly_mode(self):
        mode, days_list, self.weekly_times = get_prescheduled(self.ser)
        if mode != 2:
            days_list = 7 * [False]
            self.weekly_times = []
        else:
            if days_list == None:
                days_list = 7 * [False]
            if self.weekly_times == None:
                self.weekly_times = []
        self.last_changed_weekly = [-1, -1, -1]

        weekTab = QWidget()
        layout = QGridLayout()
        layout.setSpacing(20)
        self.days_checkboxes = []
        days = ["Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"]
        for i in range(len(days)):
            self.days_checkboxes.append(QCheckBox(days[i]))
            self.days_checkboxes[-1].setFont(QFont(font, fontsizes[0]))
            self.days_checkboxes[-1].setChecked(days_list[i])
            layout.addWidget(self.days_checkboxes[-1], i, 0, 1, 1)

        splt1 = label_shortcut("")
        splt1.setStyleSheet("background-color: black")
        splt1.setFixedWidth(2)
        layout.addWidget(splt1, 0, 1, 7, 1)

        sel = label_shortcut("Selected times:", 1, 1)
        layout.addWidget(sel, 0, 2, 1, 1)

        self.sel_times_weekly = label_shortcut("", 1)
        layout.addWidget(self.sel_times_weekly, 1, 2, 6, 1)
        self.label_update_weekly()

        splt2 = label_shortcut("")
        splt2.setStyleSheet("background-color: black")
        splt2.setFixedWidth(2)
        layout.addWidget(splt2, 0, 3, 7, 1)

        sta = label_shortcut("Start time:")
        layout.addWidget(sta, 0, 4, 1, 3)

        sta_hours = QSpinBox()
        sta_hours.setMinimum(0)
        sta_hours.setMaximum(23)
        sta_hours.setValue(0)
        sta_hours.setSingleStep(1)
        sta_hours.setFont(QFont(font, fontsizes[0]))
        layout.addWidget(sta_hours, 1, 4, 1, 1)

        sta_h = label_shortcut(":", 1)
        layout.addWidget(sta_h, 1, 5, 1, 1)

        sta_mins = QSpinBox()
        sta_mins.setMinimum(0)
        sta_mins.setMaximum(59)
        sta_mins.setValue(0)
        sta_mins.setSingleStep(1)
        sta_mins.setFont(QFont(font, fontsizes[0]))
        layout.addWidget(sta_mins, 1, 6, 1, 1)

        sto = label_shortcut("Stop time:")
        layout.addWidget(sto, 2, 4, 1, 3)

        sto_hours = QSpinBox()
        sto_hours.setMinimum(0)
        sto_hours.setMaximum(23)
        sto_hours.setValue(0)
        sto_hours.setSingleStep(1)
        sto_hours.setFont(QFont(font, fontsizes[0]))
        layout.addWidget(sto_hours, 3, 4, 1, 1)

        sto_h = label_shortcut(":", 1)
        layout.addWidget(sto_h, 3, 5, 1, 1)

        sto_mins = QSpinBox()
        sto_mins.setMinimum(0)
        sto_mins.setMaximum(59)
        sto_mins.setValue(0)
        sto_mins.setSingleStep(1)
        sto_mins.setFont(QFont(font, fontsizes[0]))
        layout.addWidget(sto_mins, 3, 6, 1, 1)

        self.weekly_spinboxes = [sta_hours, sta_mins, sto_hours, sto_mins]

        add = button_shortcut("Add")
        add.clicked.connect(self.time_set_weekly)
        layout.addWidget(add, 4, 4, 1, 3)

        undo = button_shortcut("Undo")
        undo.clicked.connect(self.time_undo_weekly)
        layout.addWidget(undo, 5, 4, 1, 3)

        clear = button_shortcut("Clear")
        clear.clicked.connect(self.time_clear_weekly)
        layout.addWidget(clear, 6, 4, 1, 3)
        
        send = button_shortcut("Send", 1)
        send.clicked.connect(self.send_clicked_weekly)
        layout.addWidget(send, 7, 2, 1, 1)

        weekTab.setLayout(layout)
        return weekTab

    ## Handler for the Weekly mode - Set button
    def time_set_weekly(self):
        if (len(self.weekly_times) == 50):
            dlg = CustomDialog("Information", "Limited to 50 separate time limits.\nTry starting again or sending the current parameters,\nwhich will be automatically optimized.\nThis may result in less than 50 intervals.")
            dlg.exec()
            return
        startH = self.weekly_spinboxes[0].value()
        startM = self.weekly_spinboxes[1].value()
        stopH = self.weekly_spinboxes[2].value()
        stopM = self.weekly_spinboxes[3].value()
        if (stopH > startH or (stopH == startH and stopM > startM)):
            for i in range(len(self.weekly_times)):
                if (startH == self.weekly_times[i][0] and startM == self.weekly_times[i][1] and stopH == self.weekly_times[i][2] and stopM == self.weekly_times[i][3]):
                    dlg = CustomDialog("Information", "Duplicate entry! Please try again.")
                    dlg.exec()
                    return
                later_hour = (startH >= self.weekly_times[i][0])
                same_hour_later_minute = (startH == self.weekly_times[i][0] and startM > self.weekly_times[i][0])
                same_hour_same_minute = (startH == self.weekly_times[i][0] and startM == self.weekly_times[i][1])
                later_stop = (stopH > self.weekly_times[i][2] or (stopH == self.weekly_times[i][2] and stopM >= self.weekly_times[i][3]))
                if same_hour_same_minute:
                    if later_stop:
                        self.last_changed_weekly = [i, self.weekly_times[i][2], self.weekly_times[i][3]]
                        self.weekly_times[i][2] = stopH
                        self.weekly_times[i][3] = stopM
                        self.label_update_weekly()
                    return
                if same_hour_later_minute:
                    self.weekly_times.insert(i+1, [startH, startM, stopH, stopM])
                    self.last_changed_weekly = [i+1,-1,-1]
                    self.label_update_weekly()
                    return
                elif not later_hour:
                    self.weekly_times.insert(i, [startH, startM, stopH, stopM])
                    self.last_changed_weekly = [i,-1,-1]
                    self.label_update_weekly()
                    return

            self.weekly_times.append([startH, startM, stopH, stopM])
            self.label_update_weekly()
            self.last_changed_weekly = [len(self.weekly_times) - 1,-1,-1]
            return
        else:
            dlg = CustomDialog("Warning!", "Start and stop times not compatible!")
            dlg.exec()

    ## Handler for the Weekly mode - Undo button
    # @warning Only allows for 1 undo
    def time_undo_weekly(self):
        if (self.last_changed_weekly[0] != -1):
            if (self.last_changed_weekly[1] == -1):
                self.weekly_times.pop(self.last_changed_weekly[0])
                self.last_changed_weekly = [-1,-1,-1]
            else:
                self.weekly_times[self.last_changed_weekly[0]][2] = self.last_changed_weekly[1]
                self.weekly_times[self.last_changed_weekly[0]][3] = self.last_changed_weekly[2]
                self.last_changed_weekly = [-1,-1,-1]
            self.label_update_weekly()
        else:
            dlg = CustomDialog("Warning!", "Unable to undo any further!")
            dlg.exec()

    ## Handler for the Weekly mode - Clear button
    def time_clear_weekly(self):
        self.weekly_times = []
        self.label_update_weekly()

    ## Updated the Weekly mode time selection label
    def label_update_weekly(self):
        times = ""
        for i in self.weekly_times:
            times += str(i[0]).zfill(2) + ":" + str(i[1]).zfill(2) + " → " + str(i[2]).zfill(2) + ":" + str(i[3]).zfill(2) + "\n"
        self.sel_times_weekly.setText(times)

    ## Handler for the Weekly mode - Send button
    def send_clicked_weekly(self):
        # Check for consecutive or overlapping entries
        flag = True
        while flag:
            flag = False
            for i in range(len(self.weekly_times)-1):
                hour_overlap = self.weekly_times[i][2] > self.weekly_times[i+1][0]
                minute_overlap = (self.weekly_times[i][2] == self.weekly_times[i+1][0]) and (self.weekly_times[i][3] >= self.weekly_times[i+1][1])
                if hour_overlap or minute_overlap:
                    if (self.weekly_times[i][2] > self.weekly_times[i+1][2] or (self.weekly_times[i][2] == self.weekly_times[i+1][2] and self.weekly_times[i][3] >= self.weekly_times[i+1][3])):
                        maxH = self.weekly_times[i][2]
                        maxM = self.weekly_times[i][3]
                    else:
                        maxH = self.weekly_times[i+1][2]
                        maxM = self.weekly_times[i+1][3]

                    self.weekly_times[i] = [self.weekly_times[i][0], self.weekly_times[i][1], maxH, maxM]
                    self.weekly_times.pop(i+1)
                    flag = True
                    break
        self.label_update_weekly()
        
        if self.source != self.combo.currentIndex():
            if not set_source(self.ser, self.combo.currentIndex()):
                dlg = CustomDialog("Warning!", "Unable to set source")
                dlg.exec()
            
        days = []
        if self.days_checkboxes[6].isChecked():
            days.append(0)
        for i in range(6):
            if self.days_checkboxes[i].isChecked():
                days.append(i+1)
        if len(days) == 0:
            dlg = CustomDialog("Information", "No days selected. Unable to proceed")
            dlg.exec()
            return
        if len(self.weekly_times) == 0:
            dlg = CustomDialog("Information", "No times selected. Unable to proceed")
            dlg.exec()
            return

        if not set_weekly(self.ser, days, self.weekly_times):
            dlg = CustomDialog("Warning!", "Unable to set weekly mode configurations")
            dlg.exec()
        else:
            dlg = CustomDialog("Success!", "Weekly mode configurations set correctly.")
            dlg.exec()
        if self.source != self.combo.currentIndex():
            self.source = self.combo.currentIndex()
            if not set_source(self.ser, self.combo.currentIndex()):
                dlg = CustomDialog("Warning!", "Unable to set source")
                dlg.exec()
            else:
                dlg = CustomDialog("Success!", "Source set correctly.")
                dlg.exec()

    ## Handler for the Close button
    def closeEvent(self, event):
        self.exit_clicked()

## Custom dialog window with OK button
# @param type Window title
# @param custom_message Message to be displayed
class CustomDialog(QDialog):
    def __init__(self, type, custom_message):
        super().__init__()

        self.setWindowTitle(type)

        QBtn = QDialogButtonBox.Ok

        self.buttonBox = QDialogButtonBox(QBtn)
        self.buttonBox.accepted.connect(self.accept)

        self.layout = QVBoxLayout()
        message = QLabel(custom_message)
        message.setFont(QFont(font, fontsizes[0]))
        self.layout.addWidget(message)
        self.layout.addWidget(self.buttonBox)
        self.setLayout(self.layout)