// Wifi handeling
#include "Arduino.h"
#include "WiFi.h"

class WifiWrapper
{
public:
    char charBuf[38] = "";
    void setupScan();
    uint8_t scan();
    char *getSSID(uint8_t i);
};