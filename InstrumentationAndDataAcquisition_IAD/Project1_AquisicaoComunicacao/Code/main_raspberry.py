import serial
import time
import sys
import os
from PyQt5.QtWidgets import QApplication, QMainWindow, QPushButton, QWidget, QGridLayout, QLabel, QSpinBox
from PyQt5 import QtCore
import pyqtgraph as pg

# Classe que forma a janela
class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        
        # Encontrar a porta correta
        path = ""
        for i in range(5):
            if os.path.exists('/dev/ttyACM' + str(i)):
                path = '/dev/ttyACM' + str(i)
                break
        # Se a porta não for encontrada, sair
        if path == "":
            print("Arduino not found")
            exit()

        # Título da janela e margem (padding) interior
        self.setWindowTitle("IAD")
        self.setContentsMargins(10, 10, 10, 10)

        # Botão de start, conectar ao handler
        start = QPushButton("Start")
        start.clicked.connect(self.start_clicked)

        # Botão de stop, conectar ao handler
        stop = QPushButton("Stop")
        stop.clicked.connect(self.stop_clicked)

        # Botão de command, conectar ao handler
        command = QPushButton("Command")
        command.clicked.connect(self.command_clicked)

        # Label do rate
        rate = QLabel("Rate (ms):")
        rate.setAlignment(QtCore.Qt.AlignCenter)

        # Spinbox de seleção do rate, conectar ao handler
        rate_spinbox = QSpinBox()
        rate_spinbox.setMaximum(10000)
        rate_spinbox.setMinimum(100)
        rate_spinbox.setValue(1000)
        rate_spinbox.valueChanged.connect(self.rate_changed)
        
        # Label do window width
        window = QLabel("Window width (s):")
        window.setAlignment(QtCore.Qt.AlignCenter)

        # Spinbox de seleção do window width, conectar ao handler
        window_spinbox = QSpinBox()
        window_spinbox.setMaximum(10000)
        window_spinbox.setMinimum(1)
        window_spinbox.setValue(10)
        window_spinbox.valueChanged.connect(self.window_changed)
        self.window_width = 10
        
        # Criar o plot, colocar labels e título
        self.plot_widget = pg.plot()
        self.plot_widget.setLabel('bottom', 'Time (s)')
        self.plot_widget.setLabel('left', 'Voltage (V)')
        self.plot_widget.setTitle("Data Acquisition", fontsize=20)

        # Formar a grid, colocar os widgets
        grid_layout = QGridLayout()
        grid_layout.setSpacing(10)
        grid_layout.addWidget(start, 0, 0, 1, 1)
        grid_layout.addWidget(stop, 0, 1, 1, 1)
        grid_layout.addWidget(command, 0, 2, 1, 1)
        grid_layout.addWidget(rate, 1, 0, 1, 1)
        grid_layout.addWidget(rate_spinbox, 1, 1, 1, 2)
        grid_layout.addWidget(window, 2, 0, 1, 1)
        grid_layout.addWidget(window_spinbox, 2, 1, 1, 2)
        grid_layout.addWidget(self.plot_widget, 3, 0, 1, 3)

        # Colocar a grid no widget principal
        widget = QWidget()
        widget.setLayout(grid_layout)
        # Colocar o widget principal na janela como central
        self.setCentralWidget(widget)

        # Esta variável controla se está a ocorrer aquisição de dados
        self.running = False
        # Esta variável regista o tempo em que começou a aquisição
        self.start_time = 0

        # Timeout para pedir dados, conectar ao handler
        self.timer = QtCore.QTimer()
        self.timer.timeout.connect(self.update)
        self.timer.setInterval(1000)
        
        # Abrir a porta serial para enviar e receber dados
        self.ser = serial.Serial(path, 9600, timeout=1)

    # Handler do botão start
    def start_clicked(self):
        if not self.running:
            self.running = True
            print("Started")
            self.plot_widget.clear()
            self.start_time = time.time_ns()
            self.timer.start()
        else:
            print("Already running!")

    # Handler do botão stop
    def stop_clicked(self):
        if self.running:
            self.running = False
            print("Stopped")
            self.timer.stop()
        else:
            print("Not running!")

    # Handler do botão command
    def command_clicked(self):
        print("Send command to Arduino")
        self.update()

    # Handler do timeout, pede e recebe os dados
    def update(self):
        #print("Get data")
        self.ser.reset_input_buffer()
        self.ser.write(b"1\n")
        line = self.ser.readline().decode('utf-8').rstrip()
        val = int(line)/1023*5
        # Imprimir o valor
        print(val)
        if line.isdigit():
            time_diff = (time.time_ns()-self.start_time)/1000000000
            self.plot_widget.plot([time_diff], [val], pen=None, symbol='o')
            if (time_diff > 10 * self.window_width):
                self.stop_clicked()
                self.start_clicked()
                return
            if (time_diff > self.window_width):
                self.plot_widget.setXRange(time_diff-self.window_width, time_diff)
            else:
                self.plot_widget.setXRange(0, self.window_width)
        else:
            print("ERRO")

    # Handler do spinbox do rate
    def rate_changed(self, new_rate):
        # Parar
        self.stop_clicked()
        self.timer.setInterval(new_rate)
        
    # Handler do spinbox do window width
    def window_changed(self, new_window):
        # Parar
        self.stop_clicked()
        self.window_width = new_window
    
# Criar a aplicação e a janela, colocar visível
app = QApplication(sys.argv)
window = MainWindow()
window.show()

# Executar
app.exec()