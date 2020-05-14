// Dispaly handeling
#include "Arduino.h"
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <Fonts/FreeMono12pt7b.h>

// screen       ESP32
// 1 VCC        3v3
// 2 GND        GND
// 3 CS         IO5
// 4 RESET      IO13
// 5 DC/RS      IO26
// 6 SDI/MOSI   IO23 (MOSI)
// 7 SCK        IO18 (CLK)
// 8 LED        IO14
// 9 SDO/MISO   IO19 (MISO)

//MOSI 23
//MISO 19
//CLK  18

class Display
{
private:
    const uint8_t TFT_CS = 5;
    const uint8_t TFT_DC = 26;
    const uint8_t TFT_RST = 13;
    const uint8_t TFT_LED = 14;
    const int PWM_FREQ = 5000;
    const int LED_CHANNEL = 0;
    const int PWM_RESOLUTION = 8;
    Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
    char linesBuf[512];
    char *lineStart[32];
    uint8_t currentLine = 0;
    uint16_t textHeight = 0;

public:
    void setup();
    void readDiagnostics();
    void setBacklightBrightness(uint8_t dutyCycle);
    // Text
    void textSetup();
    void clearScreen(uint16_t backgroundColor);
    void print(const char *str);
    void print(const int num);
    void addLine(const char *str);
    void printLines(uint8_t start, uint8_t stop);
    void testPrint(const char *str);

    void scrollY(uint16_t y);
    // Tests:
    unsigned long testFillScreen();
    unsigned long testText();
    unsigned long testLines(uint16_t color);
    unsigned long testFastLines(uint16_t color1, uint16_t color2);
    unsigned long testRects(uint16_t color);
    unsigned long testFilledRects(uint16_t color1, uint16_t color2);
    unsigned long testFilledCircles(uint8_t radius, uint16_t color);
    unsigned long testCircles(uint8_t radius, uint16_t color);
    unsigned long testTriangles();
    unsigned long testFilledTriangles();
    unsigned long testRoundRects();
    unsigned long testFilledRoundRects();
    void runBenchmark(const int8_t testNum);
};
