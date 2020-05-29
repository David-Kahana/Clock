#include "Arduino.h"

/*
connecting Rotary encoder
CLK (A pin) - to any microcontroler intput pin with interrupt -> in this example pin 33
DT (B pin) - to any microcontroler intput pin with interrupt -> in this example pin 35
SW (button pin) - to any microcontroler intput pin -> in this example pin 34
GND - to microcontroler GND
*/

class EncoderBtn
{
private:
    portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;
    const uint8_t ROTARY_ENCODER_A_PIN = 33;
    const uint8_t ROTARY_ENCODER_B_PIN = 35;
    const uint8_t ROTARY_ENCODER_BUTTON_PIN = 34;
    //const int8_t enc_states[16] = {0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};
    const int8_t enc_states[16] = {0, -1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    uint8_t old_AB = 0;
    volatile int16_t lastReadEncoder0Pos = 0;
    volatile bool button = false;
    bool lastButton = false;
    bool isEnabled = true;
    int16_t _minEncoderValue = -300;
    int16_t _maxEncoderValue = 300;
    volatile int16_t encoder0Pos = 0;
    volatile uint32_t entries = 0;

public:
    void IRAM_ATTR readEncoder_ISR();
    void setup(void (*ISR_callback)(void));
    //void inLoop();
    //void loopTest();
    void setRange(int16_t minEnc, int16_t maxEnc);
    bool changedUp();
    bool changedDown();
};

