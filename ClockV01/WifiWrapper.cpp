#include "WifiWrapper.h"

void WifiWrapper::setupScan()
{
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);
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