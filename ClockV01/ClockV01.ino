#include "Display.h"
#include "WifiWrapper.h"
#include <fabgl.h>
fabgl::PS2Controller PS2Controller;
fabgl::Keyboard Keys;
fabgl::Keyboard *keyboard = nullptr;
Display disp;
WifiWrapper wifi;
uint8_t totalNetworks = 0;
int8_t highlighted = 0;
uint8_t first = 0;
uint8_t last = 9;

void setup()
{
  Serial.begin(115200);
  Keys.begin(GPIO_NUM_4, GPIO_NUM_32, true, true); // clk, dat

  disp.setup();
  disp.textSetup();
  delay(100);
  Serial.println(F("Dispaly Setup done"));
  
  wifi.setupScan();
  Serial.println("wifi setupScan done");
  Serial.println("scan start");
  disp.print("scan start...");
  totalNetworks = wifi.scan();
  char *line;
  Serial.println("scan done");
  disp.print(" done\n");
  if (totalNetworks == 0)
  {
      Serial.println("no networks found");
      disp.print("no networks found\n");
  }
  else
  {
    Serial.print(totalNetworks);
    Serial.println(" networks found");
    for (int i = 0; i < totalNetworks; ++i)
    {
      line = wifi.getSSID(i);
      Serial.print(line);
      delay(5);
      }
      displayHighlight(totalNetworks, 0);
  }

  keyboard = PS2Controller.keyboard();
}

bool keyDown;
fabgl::VirtualKey vKey;

void loop(void)
{
  if (keyboard->virtualKeyAvailable())
  {
    //disp.clearScreen(ILI9341_DARKGREEN);
    // ascii mode (show ASCII and VirtualKeys)
    vKey = keyboard->getNextVirtualKey(&keyDown);
    if (vKey == fabgl::VirtualKey::VK_UP && !keyDown)
    {
      //disp.print("UP!!!");
      // highlighted--;
      // if (highlighted < 0)
      // {
      //   highlighted = 0;
      // }
      // displayNets(totalNetworks, highlighted, first, last);
      moveUp();
    }
    if (vKey == fabgl::VirtualKey::VK_DOWN && !keyDown)
    {
      moveDown();
    }
  }
}

void moveDown()
{
  char *line;
  if (highlighted < last - 1)
  {
    highlighted++;
    line = wifi.getSSID(highlighted);
    disp.printAtH(highlighted - first + 1, line);
    line = wifi.getSSID(highlighted - 1);
    disp.printAtUH(highlighted - first, line);
  }
}

void moveUp()
{
  char *line;
  if (highlighted > first)
  {
    highlighted--;
    line = wifi.getSSID(highlighted);
    disp.printAtH(highlighted - first + 1, line);
    line = wifi.getSSID(highlighted + 1);
    disp.printAtUH(highlighted - first + 2, line);
  }
}

void displayNets(uint8_t total, int8_t highlight, uint8_t firstLine, uint8_t lastLine)
{
  char *line;
  disp.clearScreen(ILI9341_BLACK);
  disp.print(total);
  disp.print(" networks found\n");
  for (uint8_t i = firstLine; i < lastLine; ++i)
  {
    line = wifi.getSSID(i);
    if (i == (uint8_t)highlight)
    {
      disp.testPrint(line);
    }
    else
    {
      disp.print(line);
    }
    //delay(5);
  }
}

void displayHighlight(uint8_t total, int8_t highlight)
{
  char *line;
  disp.clearScreen(ILI9341_BLACK);
  disp.print(total);
  disp.print(" networks found\n");
  for (uint8_t i = 0; i < total; ++i)
  {
    line = wifi.getSSID(i);
    if (i == (uint8_t)highlight)
    {
      disp.testPrint(line);
    }
    else
    {
      disp.print(line);
    }
    //delay(5);
  }
}