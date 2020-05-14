#include "WifiWrapper.h"

void WifiWrapper::setupScan()
{
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);
}

void WifiWrapper::scanAll()
{
    Serial.println("scan start");
    // WiFi.scanNetworks will return the number of networks found
    int n = WiFi.scanNetworks();
    Serial.println("scan done");
    if (n == 0)
    {
        Serial.println("no networks found");
    }
    else
    {
        Serial.print(n);
        Serial.println(" networks found");
        for (int i = 0; i < n; ++i)
        {
            //Print SSID and RSSI for each network found
            //sprintf(charBuf, "%d: %s (%d)%s\n", i + 1, WiFi.SSID(i).c_str(), WiFi.RSSI(i), (WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
            sprintf(charBuf, "%d: %s (%d)\n", i + 1, WiFi.SSID(i).c_str(), WiFi.RSSI(i));
            Serial.print(charBuf);
            delay(10);
        }
    }
    WiFi.disconnect();
}

uint8_t WifiWrapper::scan()
{
    // WiFi.scanNetworks will return the number of networks found
    int16_t n = WiFi.scanNetworks();
    delay(10);
    WiFi.disconnect();
    return (uint8_t)n;
}

char *WifiWrapper::getSSID(uint8_t i)
{
    sprintf(charBuf, "%d: %s (%d)\n", i + 1, WiFi.SSID(i).c_str(), WiFi.RSSI(i));
    return charBuf;
}