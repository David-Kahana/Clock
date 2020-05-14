// Wifi handeling
#include "Arduino.h"
#include "WiFi.h"

class WifiWrapper
{
private:
public:
    char charBuf[38] = "";
    void setupScan();
    void scanAll();
    uint8_t scan();
    char *getSSID(uint8_t i);
};