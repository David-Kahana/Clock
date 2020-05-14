#include "Display.h"

void Display::setup()
{
    ledcSetup(LED_CHANNEL, PWM_FREQ, PWM_RESOLUTION);
    // attach the channel to the GPIO to be controlled
    ledcAttachPin(TFT_LED, LED_CHANNEL);
    ledcWrite(LED_CHANNEL, 180);
    tft.begin();
}

void Display::readDiagnostics()
{
    // read diagnostics (optional but can help debug problems)
    uint8_t x = tft.readcommand8(ILI9341_RDMODE);
    Serial.print("Display Power Mode: 0x");
    Serial.println(x, HEX);
    x = tft.readcommand8(ILI9341_RDMADCTL);
    Serial.print("MADCTL Mode: 0x");
    Serial.println(x, HEX);
    x = tft.readcommand8(ILI9341_RDPIXFMT);
    Serial.print("Pixel Format: 0x");
    Serial.println(x, HEX);
    x = tft.readcommand8(ILI9341_RDIMGFMT);
    Serial.print("Image Format: 0x");
    Serial.println(x, HEX);
    x = tft.readcommand8(ILI9341_RDSELFDIAG);
    Serial.print("Self Diagnostic: 0x");
    Serial.println(x, HEX);
}

void Display::setBacklightBrightness(uint8_t dutyCycle)
{
    // changing the LED brightness with PWM
    ledcWrite(LED_CHANNEL, dutyCycle);
}

void Display::textSetup()
{
    int16_t x1, y1;
    uint16_t w;
    tft.setRotation(3);
    tft.fillScreen(ILI9341_BLACK);
    tft.setFont(&FreeMono12pt7b);
    tft.getTextBounds("A", 30, 30, &x1, &y1, &w, &textHeight);
    tft.setCursor(0, textHeight);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextWrap(false);
    memset(linesBuf, 0, 512);
    lineStart[0] = linesBuf;
}

void Display::clearScreen(uint16_t backgroundColor)
{
    tft.fillScreen(backgroundColor);
    tft.setCursor(0, textHeight);
}

void Display::testPrint(const char* str)
{
    int16_t x, y, x1, y1;
    uint16_t w, h;
    x = tft.getCursorX();
    y = tft.getCursorY();
    tft.getTextBounds(str, x, y, &x1, &y1, &w, &h);
    tft.fillRect(x1, y1, (int16_t)w, (int16_t)h, ILI9341_CYAN);
    tft.setTextColor(ILI9341_BLACK);
    tft.print(str);
    tft.setTextColor(ILI9341_WHITE);
}

void Display::print(const char* str)
{
    tft.print(str);
}

void Display::print(const int num)
{
    tft.print(num);
}

void Display::addLine(const char *str)
{
    size_t len = strlen(str);
    strcpy(lineStart[currentLine], str);
    *(lineStart[currentLine] + len) = 0;
    currentLine++;
    lineStart[currentLine] = lineStart[currentLine - 1] + len + 1;
}

void Display::printLines(uint8_t start, uint8_t stop)
{
    tft.fillScreen(ILI9341_BLACK);
    tft.setCursor(0, 0);
    for (uint8_t ind = start; ind <= stop; ++ind)
    {
        tft.println(lineStart[ind]);
    }
}

void Display::scrollY(uint16_t y)
{
    tft.scrollTo(y);
}

unsigned long Display::testFillScreen()
{
    unsigned long start = micros();
    tft.fillScreen(ILI9341_BLACK);
    yield();
    tft.fillScreen(ILI9341_RED);
    yield();
    tft.fillScreen(ILI9341_GREEN);
    yield();
    tft.fillScreen(ILI9341_BLUE);
    yield();
    tft.fillScreen(ILI9341_BLACK);
    yield();
    return micros() - start;
}

unsigned long Display::testText()
{
    tft.fillScreen(ILI9341_BLACK);
    unsigned long start = micros();
    tft.setCursor(0, 0);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(1);
    tft.println("Hello World!");
    tft.setTextColor(ILI9341_YELLOW);
    tft.setTextSize(2);
    tft.println(1234.56);
    tft.setTextColor(ILI9341_RED);
    tft.setTextSize(3);
    tft.println(0xDEADBEEF, HEX);
    tft.println();
    tft.setTextColor(ILI9341_GREEN);
    tft.setTextSize(5);
    tft.println("Groop");
    tft.setTextSize(2);
    tft.println("I implore thee,");
    tft.setTextSize(1);
    tft.println("my foonting turlingdromes.");
    tft.println("And hooptiously drangle me");
    tft.println("with crinkly bindlewurdles,");
    tft.println("Or I will rend thee");
    tft.println("in the gobberwarts");
    tft.println("with my blurglecruncheon,");
    tft.println("see if I don't!");
    return micros() - start;
}

unsigned long Display::testLines(uint16_t color)
{
    unsigned long start, t;
    int x1, y1, x2, y2,
        w = tft.width(),
        h = tft.height();

    tft.fillScreen(ILI9341_BLACK);
    yield();

    x1 = y1 = 0;
    y2 = h - 1;
    start = micros();
    for (x2 = 0; x2 < w; x2 += 6)
        tft.drawLine(x1, y1, x2, y2, color);
    x2 = w - 1;
    for (y2 = 0; y2 < h; y2 += 6)
        tft.drawLine(x1, y1, x2, y2, color);
    t = micros() - start; // fillScreen doesn't count against timing

    yield();
    tft.fillScreen(ILI9341_BLACK);
    yield();

    x1 = w - 1;
    y1 = 0;
    y2 = h - 1;
    start = micros();
    for (x2 = 0; x2 < w; x2 += 6)
        tft.drawLine(x1, y1, x2, y2, color);
    x2 = 0;
    for (y2 = 0; y2 < h; y2 += 6)
        tft.drawLine(x1, y1, x2, y2, color);
    t += micros() - start;

    yield();
    tft.fillScreen(ILI9341_BLACK);
    yield();

    x1 = 0;
    y1 = h - 1;
    y2 = 0;
    start = micros();
    for (x2 = 0; x2 < w; x2 += 6)
        tft.drawLine(x1, y1, x2, y2, color);
    x2 = w - 1;
    for (y2 = 0; y2 < h; y2 += 6)
        tft.drawLine(x1, y1, x2, y2, color);
    t += micros() - start;

    yield();
    tft.fillScreen(ILI9341_BLACK);
    yield();

    x1 = w - 1;
    y1 = h - 1;
    y2 = 0;
    start = micros();
    for (x2 = 0; x2 < w; x2 += 6)
        tft.drawLine(x1, y1, x2, y2, color);
    x2 = 0;
    for (y2 = 0; y2 < h; y2 += 6)
        tft.drawLine(x1, y1, x2, y2, color);

    yield();
    return micros() - start;
}

unsigned long Display::testFastLines(uint16_t color1, uint16_t color2)
{
    unsigned long start;
    int x, y, w = tft.width(), h = tft.height();

    tft.fillScreen(ILI9341_BLACK);
    start = micros();
    for (y = 0; y < h; y += 5)
        tft.drawFastHLine(0, y, w, color1);
    for (x = 0; x < w; x += 5)
        tft.drawFastVLine(x, 0, h, color2);

    return micros() - start;
}

unsigned long Display::testRects(uint16_t color)
{
    unsigned long start;
    int n, i, i2,
        cx = tft.width() / 2,
        cy = tft.height() / 2;

    tft.fillScreen(ILI9341_BLACK);
    n = min(tft.width(), tft.height());
    start = micros();
    for (i = 2; i < n; i += 6)
    {
        i2 = i / 2;
        tft.drawRect(cx - i2, cy - i2, i, i, color);
    }

    return micros() - start;
}

unsigned long Display::testFilledRects(uint16_t color1, uint16_t color2)
{
    unsigned long start, t = 0;
    int n, i, i2,
        cx = tft.width() / 2 - 1,
        cy = tft.height() / 2 - 1;

    tft.fillScreen(ILI9341_BLACK);
    n = min(tft.width(), tft.height());
    for (i = n; i > 0; i -= 6)
    {
        i2 = i / 2;
        start = micros();
        tft.fillRect(cx - i2, cy - i2, i, i, color1);
        t += micros() - start;
        // Outlines are not included in timing results
        tft.drawRect(cx - i2, cy - i2, i, i, color2);
        yield();
    }

    return t;
}

unsigned long Display::testFilledCircles(uint8_t radius, uint16_t color)
{
    unsigned long start;
    int x, y, w = tft.width(), h = tft.height(), r2 = radius * 2;

    tft.fillScreen(ILI9341_BLACK);
    start = micros();
    for (x = radius; x < w; x += r2)
    {
        for (y = radius; y < h; y += r2)
        {
            tft.fillCircle(x, y, radius, color);
        }
    }

    return micros() - start;
}

unsigned long Display::testCircles(uint8_t radius, uint16_t color)
{
    unsigned long start;
    int x, y, r2 = radius * 2,
              w = tft.width() + radius,
              h = tft.height() + radius;

    // Screen is not cleared for this one -- this is
    // intentional and does not affect the reported time.
    start = micros();
    for (x = 0; x < w; x += r2)
    {
        for (y = 0; y < h; y += r2)
        {
            tft.drawCircle(x, y, radius, color);
        }
    }

    return micros() - start;
}

unsigned long Display::testTriangles()
{
    unsigned long start;
    int n, i, cx = tft.width() / 2 - 1,
              cy = tft.height() / 2 - 1;

    tft.fillScreen(ILI9341_BLACK);
    n = min(cx, cy);
    start = micros();
    for (i = 0; i < n; i += 5)
    {
        tft.drawTriangle(
            cx, cy - i,     // peak
            cx - i, cy + i, // bottom left
            cx + i, cy + i, // bottom right
            tft.color565(i, i, i));
    }

    return micros() - start;
}

unsigned long Display::testFilledTriangles()
{
    unsigned long start, t = 0;
    int i, cx = tft.width() / 2 - 1,
           cy = tft.height() / 2 - 1;

    tft.fillScreen(ILI9341_BLACK);
    start = micros();
    for (i = min(cx, cy); i > 10; i -= 5)
    {
        start = micros();
        tft.fillTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
                         tft.color565(0, i * 10, i * 10));
        t += micros() - start;
        tft.drawTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
                         tft.color565(i * 10, i * 10, 0));
        yield();
    }

    return t;
}

unsigned long Display::testRoundRects()
{
    unsigned long start;
    int w, i, i2,
        cx = tft.width() / 2 - 1,
        cy = tft.height() / 2 - 1;

    tft.fillScreen(ILI9341_BLACK);
    w = min(tft.width(), tft.height());
    start = micros();
    for (i = 0; i < w; i += 6)
    {
        i2 = i / 2;
        tft.drawRoundRect(cx - i2, cy - i2, i, i, i / 8, tft.color565(i, 0, 0));
    }

    return micros() - start;
}

unsigned long Display::testFilledRoundRects()
{
    unsigned long start;
    int i, i2,
        cx = tft.width() / 2 - 1,
        cy = tft.height() / 2 - 1;

    tft.fillScreen(ILI9341_BLACK);
    start = micros();
    for (i = min(tft.width(), tft.height()); i > 20; i -= 6)
    {
        i2 = i / 2;
        tft.fillRoundRect(cx - i2, cy - i2, i, i, i / 8, tft.color565(0, i, 0));
        yield();
    }

    return micros() - start;
}

void Display::runBenchmark(const int8_t testNum)
{
    switch (testNum)
    {
    case 0:
        readDiagnostics();
        break;
    case 1:
        Serial.print(F("Screen fill              "));
        Serial.println(testFillScreen());
        break;
    case 2:
        Serial.print(F("Text                     "));
        Serial.println(testText());
        break;
    case 3:
        Serial.print(F("Lines                    "));
        Serial.println(testLines(ILI9341_CYAN));
        break;
    case 4:
        Serial.print(F("Horiz/Vert Lines         "));
        Serial.println(testFastLines(ILI9341_RED, ILI9341_BLUE));
        break;
    case 5:
        Serial.print(F("Rectangles (outline)     "));
        Serial.println(testRects(ILI9341_GREEN));
        break;
    case 6:
        Serial.print(F("Rectangles (filled)      "));
        Serial.println(testFilledRects(ILI9341_YELLOW, ILI9341_MAGENTA));
        break;
    case 7:
        Serial.print(F("Circles (filled)         "));
        Serial.println(testFilledCircles(10, ILI9341_MAGENTA));
        break;
    case 8:
        Serial.print(F("Circles (outline)        "));
        Serial.println(testCircles(10, ILI9341_WHITE));
        break;
    case 9:
        Serial.print(F("Triangles (outline)      "));
        Serial.println(testTriangles());
        break;
    case 10:
        Serial.print(F("Triangles (filled)       "));
        Serial.println(testFilledTriangles());
        break;
    case 11:
        Serial.print(F("Rounded rects (outline)  "));
        Serial.println(testRoundRects());
        break;
    case 12:
        Serial.print(F("Rounded rects (filled)   "));
        Serial.println(testFilledRoundRects());
        break;
    default:
        Serial.print(F("Text                     "));
        Serial.println(testText());
        break;
    }
}