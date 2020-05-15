#include "Display.h"
#include "WifiWrapper.h"
#include <fabgl.h>

class MyClock
{
private:
    // keyboard
    fabgl::PS2Controller PS2Controller;
    fabgl::Keyboard Keys;
    fabgl::Keyboard *keyboard = nullptr;
    bool keyDown = false;
    fabgl::VirtualKey vKey;

    // WiFi
    WifiWrapper wifi;
    uint8_t totalNetworks = 0;

    //display
    Display disp;
    int8_t highlighted = 0;
    uint8_t first = 0;
    uint8_t totalLines = 9;
    uint8_t last = totalLines;

public:
    void setup();
    void inLoop();
private:
    void moveUp();
    void moveDown();
    void displayNets();
};
