#include <time.h>
#include <LovyanGFX.hpp>
#include "LGFX_ESP32_S3_d3.hpp"

static LGFX lcd;

struct Loc {
  int32_t x;
  int32_t y;
};

class disp{
  int16_t last_ds = 0;
  int16_t ds;
  int32_t s;
  int16_t h;
  const int32_t yt = 90;
  int32_t xt[13];
  const int32_t yd = 210;
  Loc dt;
  int last_cx = 0;
  public:

  void init_lcd() {
    lcd.init();
    lcd.setRotation(1);
    lcd.fillScreen(TFT_BLACK);
    lcd.setTextColor(TFT_YELLOW, TFT_BLACK);
    lcd.setTextSize(1);
  }
  
  void drawDate(struct tm* timeinfo) {
    lcd.setFont(&fonts::Font4);
    lcd.setCursor(dt.x, dt.y);
    lcd.print(timeinfo, "%A, %B %d %Y");
    int cx = lcd.getCursorX();
    while (cx <= last_cx && cx < lcd.width() - 5) {
      lcd.print(' ');
      cx = lcd.getCursorX();
    }
    last_cx = cx;
    lcd.setFont(&fonts::Font7);
  }

  void initDigits(struct tm* timeinfo) {
    char tmpbuf[16];
    dt.x = 10;
    dt.y = 320 - (int32_t)(fonts::Font4.height);
    drawDate(timeinfo);
    xt[0] = 8;
    lcd.setFont(&fonts::Font7);
    strftime(tmpbuf, 128, "%H:%M:%S.00", timeinfo);
    for (uint8_t i = 1; i < 12; ++i) {
      xt[i] = lcd.drawChar(tmpbuf[i - 1], xt[i - 1], yt) + xt[i - 1];
    }
  }

  inline void drawDigits(struct timeval& tv_now, struct tm* timeinfo) {
    lcd.drawChar(ds + '0', xt[9], yt);  // s/10
    last_ds = ds;
    if (ds == 0) {
      s = (int32_t)tv_now.tv_sec;
      lcd.drawChar(s % 10 + '0', xt[7], yt);  // s 1
      if (s % 10 == 0) {
        lcd.drawChar((s % 60) / 10 + '0', xt[6], yt);  // s 10
        if (s % 60 == 0) {
          lcd.drawChar((s / 60) % 10 + '0', xt[4], yt);  // m 1
          if ((s / 60) % 10 == 0) {
            lcd.drawChar((s / 600) % 6 + '0', xt[3], yt);  // m 10
            if (s % 3600 == 0) {
              h = (s / 3600) % 24;
              lcd.drawChar(h % 10 + '0', xt[1], yt);  // h 1
              if (h % 10 == 0) {
                lcd.drawChar(h / 10 + '0', xt[0], yt);  // h 10
                localtime_r(&(tv_now.tv_sec), timeinfo);
                drawDate(timeinfo);
              }
            }
          }
        }
      }
    }
  }
  
  inline void drawDigitFast(struct timeval& tv_now, struct tm* timeinfo) {
    lcd.drawChar((tv_now.tv_usec / 10000) % 10 + '0', xt[10], yt);  // s/100
    ds = (int16_t)(tv_now.tv_usec / 100000);
    if (last_ds != ds) {
      drawDigits(tv_now, timeinfo);
    }
  }

};

