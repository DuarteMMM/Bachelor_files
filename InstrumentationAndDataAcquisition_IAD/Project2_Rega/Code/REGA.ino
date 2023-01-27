// Water tank (index 0); Well Pump (index 1)
// Humidity mode (MODE 0); Pre-Scheduled mode - Daily mode (MODE 1); Pre-Scheduled mode - Weekly mode (MODE 2)

// Define maximum and minimum humidities
#define SPTR_SIZE 53
char *sPtr[SPTR_SIZE];
int minH, maxH = -1;

// Program MODE=1 (daily)
int intervalo_dias;

// Program MODE=2 (weekly)
int* dias_semana;
int N_dias; // Number of days in MODE=2
int N_intervalos; // Number of time intervals in MODE=2
int** intervalos_horas;
String Status;

// 'day' represents the number of days elapsed (0 being the current day)
// weekday, hour, minute and second are absolute
enum d {day, weekday, hour, minute, second};
int datetime[5];
unsigned long set_time = 0;
int flag = 0;

// Defining baud rate and renaming variables
#define v3 A3
#define v5 A5 // LED
int fonte;
int MODE;

// Setup
void setup() {
  Serial.begin(9600);
  pinMode(v3, OUTPUT);
  pinMode(v5, OUTPUT);
  fonte = 0;
  fonteWrite(fonte);
}

// Loop funtion
void loop() {
  // Function that tracks and updates time
  update_time();
  int sensorVal = analogRead(A0); // Value read from humidity sensor
  // Read information from Raspberry Pi if it is available
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    // If the command received is "h", send value from analog port 0 to Raspberry Pi
    if (data[0] == 'h') {
      if (maxH == -1)
        Serial.println((String) (1023 - sensorVal) + "," + -1 + "," + -1);
      else
        Serial.println((String) (1023 - sensorVal) + "," + (1023 - minH) + "," + (1023 - maxH));
    }
    // If the command received is "s", send value of 'fonte' to Raspberry Pi
    else if (data[0] == 's') {
      Serial.println(fonte);
    }
    // If the command received is "S", change the value of 'fonte' to the one received from Raspberry Pi
    else if (data[0] == 'S') {
      fonte = String(data[2]).toInt();
      fonteWrite(fonte);
    }
    // If the command received is "H", select MODE 0, define parameters with info received from Raspberry Pi (minH, maxH)
    else if (data[0] == 'H') {
      String minH2, maxH2;
      separate(data, sPtr, SPTR_SIZE, ',');
      minH2 = sPtr[1];
      minH = 1023 - String(minH2).toInt();
      maxH2 = sPtr[2];
      maxH = 1023 - String(maxH2).toInt();
      MODE = 0;
      memset(sPtr, 0, SPTR_SIZE);
    }
    // If the command received is "T", reset number of days elapsed, set time sent from Raspberry Pi
    else if (data[0] == 'T') {
      separate(data, sPtr, SPTR_SIZE, ',');
      String vals[5];
      // 0 days elapsed
      datetime[0] = 0;
      for (int i = 1; i < 5; i++) {
        vals[i] = sPtr[i];
        datetime[i] = String(vals[i]).toInt();
      }
      set_time = millis();
      memset(sPtr, 0, SPTR_SIZE);
    }
    // If the command received is "t", send elapsed time to Rasberry Pi
    else if (data[0] == 't') {
      String s = "";
      for (int i = 0; i < 4; i++) {
        s += datetime[i];
        s += ",";
      }
      Serial.println(s + datetime[4]);
    }
    // If the command received is "m", send mode to Rasberry Pi
    else if (data[0] == 'm') {
      Serial.println(MODE);
    }

    // Daily program
    // If the command received is "D", select MODE 1, define parameters with info received from Raspberry Pi, define all variables needed for daily program
    else if (data[0] == 'D') {
      separate(data, sPtr, SPTR_SIZE, ',');
      String VAL1 = String(sPtr[1]);
      String VAL2 = String(sPtr[2]);

      // Value of day interval between waterings
      intervalo_dias = VAL1.toInt();

      // Obtain strings with hours intervals
      N_intervalos = VAL2.toInt();
      intervalos_horas = new int*[N_intervalos];
      String vec1[N_intervalos];
      for (int i = 0; i < N_intervalos; i++) {
        intervalos_horas[i] = new int[4];
        // sPtr2 for the string of hours intervals in the weekdays in MODE==2
        char *sPtr2[SPTR_SIZE];
        vec1[i] = String(sPtr[3 + i]);
        separate(vec1[i], sPtr2, SPTR_SIZE, ';');
        for (int j = 0; j < 4; j++) {
          intervalos_horas[i][j] = String(sPtr2[j]).toInt();
        }
      }
      String help1;
      for (int j = 0; j < N_intervalos; j++) {
        help1 += "," + String(sPtr[j + 3]);
      }
      Status = String(intervalo_dias) + help1;
      memset(sPtr, 0, SPTR_SIZE);
      MODE = 1;
    }

    // Weekly program
    // If the command received is "W", select MODE 2, define parameters with info received from Raspberry Pi, define all variables needed for weekly program
    else if (data[0] == 'W') {
      separate(data, sPtr, SPTR_SIZE, ',');
      String VAL1 = String(sPtr[1]);

      // sPtr 1 for the string of weekdays in MODE==2 (weekly)
      char *sPtr1[SPTR_SIZE];
      // Separate string with days and obtain number of days
      N_dias = separate(VAL1, sPtr1, SPTR_SIZE, ';');
      // Save days of the week in vector
      dias_semana = new int[N_dias];
      for (int i = 0; i < N_dias; i++) {
        dias_semana[i] = String(sPtr1[i]).toInt();
      }

      // Obtain strings with hours intervals
      N_intervalos = String(sPtr[2]).toInt();
      intervalos_horas = new int*[N_intervalos];
      String vec1[N_intervalos];
      for (int i = 0; i < N_intervalos; i++) {
        intervalos_horas[i] = new int[4];
        // sPtr2 for the string of hours intervals in the weekdays in MODE==2
        char *sPtr2[SPTR_SIZE];
        vec1[i] = String(sPtr[3 + i]);
        separate(vec1[i], sPtr2, SPTR_SIZE, ';');
        for (int j = 0; j < 4; j++) {
          intervalos_horas[i][j] = String(sPtr2[j]).toInt();
        }
      }
      String help;
      String help1;
      for (int j = 0; j < N_intervalos; j++) {
        help += "," + String(sPtr[j + 3]);
      }
      help1 = String(dias_semana[0]);
      for (int i1 = 1; i1 < N_dias; i1++) {
        help1 += ";" + String(dias_semana[i1]);
      }
      Status = help1 + help;
      memset(sPtr, 0, SPTR_SIZE);
      MODE = 2;
    }

    // If the command received is "d" or "w", send back status of the Arduino, meaning value of variables defined in Arduino for mode 1 or 2, respectively
    else if (data[0] == 'd' || data[0] == 'w') {
      Serial.println(Status);
    }
  }

  // Check only every 5 seconds
  if (datetime[second] % 5 == 0) {
    // Use flag to check only once every 5 seconds
    if (!flag) {
      // Open and close valves using humidity values (MODE 0)
      if (MODE == 0) {
        if (maxH > 0) {
          if (sensorVal > minH) {
            dWrite(HIGH);
          }
          else if (sensorVal < maxH) {
            dWrite(LOW);
          }
        }
      }

      // Open and close valves with pre-scheduled timetable
      // MODE 1 - daily
      if (MODE == 1) {
        // Check day
        if (datetime[0] % intervalo_dias == 0) {
          // Check hours and minutes
          bool val = LOW;
          for (int j = 0; j < N_intervalos; j++) {
            if ( (datetime[2] > intervalos_horas[j][0]) && (datetime[2] < intervalos_horas[j][2]) ) {
              val = HIGH;
              break;
            }
            else if ((datetime[2] == intervalos_horas[j][0]) || (datetime[2] == intervalos_horas[j][2])) {
              if (intervalos_horas[j][0] == intervalos_horas[j][2]) {
                if (datetime[3] >= intervalos_horas[j][1] && datetime[3] <= intervalos_horas[j][3]) {
                  val = HIGH;
                  break;
                }
                else
                  continue;
              }
              else if (datetime[3] <= intervalos_horas[j][3] && datetime[2] == intervalos_horas[j][2]) {
                val = HIGH;
                break;
              }
              else if (datetime[2] == intervalos_horas[j][0] && datetime[3] >= intervalos_horas[j][1]) {
                val = HIGH;
                break;
              }
            }
          }
          dWrite(val);
        }
        else {
          dWrite(LOW);
        }
      }

      // MODE 2 - weekly
      if (MODE == 2) {
        for (int i = 0; i < N_dias; i++) {
          // Check day
          if (datetime[1] == dias_semana[i]) {
            // Check hours and minutes
            bool val = LOW;
            for (int j = 0; j < N_intervalos; j++) {
              if ( (datetime[2] > intervalos_horas[j][0]) && (datetime[2] < intervalos_horas[j][2]) ) {
                val = HIGH;
                break;
              }
              else if ((datetime[2] == intervalos_horas[j][0]) || (datetime[2] == intervalos_horas[j][2])) {
                if (intervalos_horas[j][0] == intervalos_horas[j][2]) {
                  if (datetime[3] >= intervalos_horas[j][1] && datetime[3] <= intervalos_horas[j][3]) {
                    val = HIGH;
                    break;
                  }
                  else
                    continue;
                }
                else if (datetime[3] <= intervalos_horas[j][3] && datetime[2] == intervalos_horas[j][2]) {
                  val = HIGH;
                  break;
                }
                else if (datetime[2] == intervalos_horas[j][0] && datetime[3] >= intervalos_horas[j][1]) {
                  val = HIGH;
                  break;
                }
              }
            }
            dWrite(val);
            break;
          }
          else {
            dWrite(LOW);
          }
        }
      }
      flag = 1;
    }
  }
  else {
    flag = 0;
  }
}

// ---- EXTRA FUNCTIONS ----
// Funtion to separate string into list with separator sep_char
int separate (String str, char **p, int size, char sep_char) {
  int n;
  char s[100];
  strcpy(s, str.c_str());
  char sep[1];
  sep[0] = sep_char;

  *p++ = strtok(s, sep);
  for (n = 1; NULL != (*p++ = strtok (NULL, sep)); n++)
    if (size == n)
      break;

  return n;
}

// Function that updates time when it is called
void update_time() {
  // If more than a second has elapsed
  unsigned long elapsed = millis() - set_time;
  if (elapsed >= 1000) {
    int secs = elapsed / 1000;
    datetime[second] += secs;
    set_time += secs * 1000;
    while (datetime[second] >= 60) {
      datetime[second] -= 60;
      datetime[minute] += 1;
    }
    while (datetime[minute] >= 60) {
      datetime[minute] -= 60;
      datetime[hour] += 1;
    }
    while (datetime[hour] >= 24) {
      datetime[hour] -= 24;
      datetime[day] += 1;
      datetime[weekday] += 1;
      while (datetime[weekday] >= 7)
        datetime[weekday] -= 7;
    }
  }
}

// Function to open all relays; if any more are added to the board, add them to this funtion as well
void dWrite(bool val) {
  digitalWrite(v3, val);
  digitalWrite(v5, val);
}

// Function to control which water source is selected
void fonteWrite(int val) {
  if (val == 1) {
    //digitalWrite(Port that controls relay for sources, HIGH or LOW);
  }
  else if (val == 0) {
    //digitalWrite(Port that controls relay for sources, HIGH or LOW (the one not used before));
  }
}
