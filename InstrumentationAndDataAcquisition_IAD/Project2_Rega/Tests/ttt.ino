
#define SPTR_SIZE 20
char *sPtr[SPTR_SIZE];
// day represents the number of days elapsed (0 being the current day)
// weekday, hour, minute and second are absolute
enum d {day, weekday, hour, minute, second};
int datetime[5];
unsigned long set_time = 0;

int separate (String str, char **p, int size) {
  int n;
  char s[100];
  strcpy(s, str.c_str());

  *p++ = strtok(s, ",");
  for (n = 1; NULL != (*p++ = strtok (NULL, ",")); n++)
    if (size == n)
      break;

  return n;
}

void setup() {
  Serial.begin(9600);
   for (int i = 0; i < 5; i++) {
    datetime[i] = 0;
  }
}

void loop() {
  update_time();
  for (int i = 0; i < 4; i++) {
    Serial.print(datetime[i]);
    Serial.print(" ");
  }
  Serial.println(datetime[4]);
}

void update_time() {
  // if more than a second has elapsed
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
