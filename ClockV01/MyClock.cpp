#include "MyClock.h"

EncoderBtn MyClock::enc;

void MyClock::setup()
{
    Keys.begin(GPIO_NUM_4, GPIO_NUM_32, true, true); // clk, dat
    disp.setup();
    disp.textSetup();
    delay(100);
    Serial.println(F("Dispaly Setup done"));

    enc.setup([] { enc.readEncoder_ISR(); });

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
        last = _min(totalNetworks, totalLines);
        displayNets();
    }
    keyboard = PS2Controller.keyboard();
}

void MyClock::inLoop()
{
    if (keyboard->virtualKeyAvailable())
    {
        vKey = keyboard->getNextVirtualKey(&keyDown);
        if (vKey == fabgl::VirtualKey::VK_UP && !keyDown)
        {
            moveUp();
        }
        if (vKey == fabgl::VirtualKey::VK_DOWN && !keyDown)
        {
            moveDown();
        }
    }
    if (enc.changedUp())
    {
        //moveUp();
    }
    if (enc.changedDown())
    {
        //moveDown();
    }
}

void MyClock::moveDown()
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
    else
    {
        if (highlighted < totalNetworks - 1)
        {
            last++;
            first++;
            highlighted++;
            displayNets();
        }
    }
}

void MyClock::moveUp()
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
    else
    {
        if (highlighted > 0)
        {
            first--;
            last--;
            highlighted--;
            displayNets();
        }
    }
}

void MyClock::displayNets()
{
    char *line;
    disp.clearScreen(ILI9341_BLACK);
    disp.print(totalNetworks);
    disp.print(" networks found\n");
    for (uint8_t i = first; i < last; ++i)
    {
        line = wifi.getSSID(i);
        if (i == (uint8_t)highlighted)
        {
            disp.printAtH(highlighted - first + 1, line);
        }
        else
        {
            disp.print(line);
        }
    }
}
