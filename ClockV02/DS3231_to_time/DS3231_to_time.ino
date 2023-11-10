#include <DS3231.h>
#include <Wire.h>
#include <time.h>

struct tm timeinfo;
struct timeval t_now;

DS3231 myRTC;
bool century = false;
bool h12Flag = false;
bool pmFlag;
byte alarmDay, alarmHour, alarmMinute, alarmSecond, alarmBits;
bool alarmDy, alarmH12Flag, alarmPmFlag;
char tmpbuf[16];

void timeFromRTC() {
  timeinfo.tm_year = myRTC.getYear() + 100;
  timeinfo.tm_mon = myRTC.getMonth(century) - 1;
  timeinfo.tm_mday = myRTC.getDate();
  timeinfo.tm_wday = myRTC.getDoW();
  timeinfo.tm_hour = myRTC.getHour(h12Flag, pmFlag);
  timeinfo.tm_min = myRTC.getMinute();
  timeinfo.tm_sec = myRTC.getSecond();

  t_now.tv_sec = mktime(&timeinfo);
  t_now.tv_usec = 0;
  settimeofday(&t_now, NULL);
}

void setup() {
	Wire.begin();
	Serial.begin(115200);
  timeFromRTC();
}

void loop() {
  gettimeofday(&t_now, NULL);
  localtime_r(&(t_now.tv_sec), &timeinfo);
	strftime(tmpbuf, 16, "%H:%M:%S.00", &timeinfo);
  Serial.println(tmpbuf);
	delay(1000);
}
