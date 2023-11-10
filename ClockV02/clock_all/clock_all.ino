#include <DS3231.h>
#include <Wire.h>
#include "disp_stuff.h"


struct tm timeinfo;
struct timeval t_now;
DS3231 myRTC;
bool century = false;
bool h12 = false;
bool PM_time = false;
disp scr;

void scan_i2c() {
  int8_t error, address;
  int nDevices = 0;
  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
      nDevices++;
    } else if (error == 4) {
      Serial.print("Unknow error at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0) {
    Serial.println("No I2C devices found\n");
  } else {
    Serial.println("done\n");
  }
}

void timeFromRTC() {
  timeinfo.tm_year = myRTC.getYear() + 100;
  timeinfo.tm_mon = myRTC.getMonth(century) - 1;
  timeinfo.tm_mday = myRTC.getDate();
  timeinfo.tm_wday = myRTC.getDoW();
  timeinfo.tm_hour = myRTC.getHour(h12, PM_time);
  timeinfo.tm_min = myRTC.getMinute();
  timeinfo.tm_sec = myRTC.getSecond();

  t_now.tv_sec = mktime(&timeinfo);
  t_now.tv_usec = 0;
  settimeofday(&t_now, NULL);
}

void setup() {
  Serial.begin(115200);
  Wire.begin(8, 9);
  //delay(500);
  //scan_i2c();

  scr.init_lcd();
  timeFromRTC();
  scr.initDigits(&timeinfo);
  gettimeofday(&t_now, NULL);
}

void loop() {
  gettimeofday(&t_now, NULL);
  scr.drawDigitFast(t_now, &timeinfo);
  int32_t x, y;
  if (lcd.getTouch(&x, &y)) {
    Serial.printf("x = %d, y = %d\n", x, y);
  }
  delay(8);
}
