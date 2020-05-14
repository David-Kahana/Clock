#include "Display.h"
#include "WiFi.h"
#include <fabgl.h>
fabgl::PS2Controller PS2Controller;
fabgl::Keyboard Keys;
fabgl::Keyboard *keyboard = nullptr;
Display disp;

uint32_t delayBetweenTests = 1000;
void WiFiSetup()
{
  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  Serial.println("Wifi Setup done");
}

void setup()
{
  Serial.begin(115200);
  Keys.begin(GPIO_NUM_4, GPIO_NUM_32, true, true); // clk, dat
  WiFiSetup();
  disp.setup();
  disp.textSetup();
  delay(100);
  Serial.println(F("Dispaly Setup done"));
  //Serial.print("012345678901234567890");
  //disp.print("012345678901234567890");
  //Serial.print("\n");
  //disp.print("\n");
  //Serial.print(32000);
  //disp.print(32000);

  scanWifi();
  WiFi.disconnect();
  keyboard = PS2Controller.keyboard();
}
bool keyDown;
fabgl::VirtualKey vKey;
//uint16_t y = 0;
void loop(void)
{
  if (keyboard->virtualKeyAvailable())
  {
    disp.clearScreen(ILI9341_DARKGREEN);
    // ascii mode (show ASCII and VirtualKeys)
    vKey = keyboard->getNextVirtualKey(&keyDown);
    if (vKey == fabgl::VirtualKey::VK_UP && !keyDown)
    {
      disp.print("UP!!!");
    }
    if (vKey == fabgl::VirtualKey::VK_DOWN && !keyDown)
    {
      disp.print("DOWN!!!");
    }
    Serial.printf("VirtualKey = %s", keyboard->virtualKeyToString(vKey));
    int c = keyboard->virtualKeyToASCII(vKey);
    if (c > -1)
    {
      Serial.printf("  ASCII = 0x%02X   ", c);
      if (c >= ' ')
        Serial.write(c);
    }
    if (!keyDown)
      Serial.write(" UP");
    Serial.write('\n');
    //disp.scrollY(y);
    //y += 1;
    //y %= 100;
    //delay(50);
  }
}
char charBuf[64] = "";
void scanWifi()
{
  Serial.println("scan start");
  disp.print("WiFi scan...");
  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  disp.print("done\n");
  if (n == 0)
  {
    Serial.println("no networks found");
  }
  else
  {
    Serial.print(n);
    Serial.println(" networks found");
    disp.print(n);
    disp.print(" networks found\n");
    for (int i = 0; i < n; ++i)
    {
      //Print SSID and RSSI for each network found
      //sprintf(charBuf, "%d: %s (%d)%s\n", i + 1, WiFi.SSID(i).c_str(), WiFi.RSSI(i), (WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
      sprintf(charBuf, "%d: %s (%d)\n", i + 1, WiFi.SSID(i).c_str(), WiFi.RSSI(i));
      Serial.print(charBuf);
      //charBuf[15] = '\n';
      disp.testPrint(charBuf);
      // Serial.print(i + 1);
      // Serial.print(": ");
      // Serial.print(WiFi.SSID(i));
      // Serial.print(" (");
      // Serial.print(WiFi.RSSI(i));
      // Serial.print(")");
      // Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
      // disp.print(i + 1);
      // disp.print(": ");
      // disp.print(WiFi.SSID(i).c_str());
      // disp.print(" (");
      // disp.print(WiFi.RSSI(i));
      // disp.print(")");
      // disp.print((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
      // disp.print("\n");
      delay(10);
    }
  }
  Serial.println("");

  // Wait a bit before scanning again
  delay(500);
}
