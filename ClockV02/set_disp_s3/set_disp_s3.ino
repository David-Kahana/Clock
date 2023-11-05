#include <Wire.h>
#include "disp_stuff.h"

struct tm timeinfo;
struct timeval t_now;

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

void setup() {
  Serial.begin(115200);
  Wire.begin(8, 9);
  delay(500);
  scan_i2c();

  init_lcd();
  t_now.tv_sec = 24 * 60 * 60 - 10;
  settimeofday(&t_now, NULL);
  char tmpbuf[16];
  dt.x = 10;
  dt.y = 320 - (int32_t)(fonts::Font4.height);

  localtime_r(&(t_now.tv_sec), &timeinfo);
  drawDate(&timeinfo);
  gettimeofday(&t_now, NULL);

  xt[0] = 8;
  lcd.setFont(&fonts::Font7);
  strftime(tmpbuf, 128, "%H:%M:%S.00", &timeinfo);
  //Serial.println(tmpbuf);
  for (uint8_t i = 1; i < 12; ++i) {
    xt[i] = lcd.drawChar(tmpbuf[i - 1], xt[i - 1], yt) + xt[i - 1];
  }
}

void loop() {
  gettimeofday(&t_now, NULL);
  lcd.drawChar((t_now.tv_usec / 10000) % 10 + '0', xt[10], yt);  // s/100
  ds = (int16_t)(t_now.tv_usec / 100000);
  if (last_ds != ds) {
    drawDigits(t_now, &timeinfo);
  }
  int32_t x, y;
  if (lcd.getTouch(&x, &y)) {
    Serial.printf("x = %d, y = %d\n", x, y);
  }
  delay(8);
}
