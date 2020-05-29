#include "EncoderBtn.h"

void EncoderBtn::setup(void (*ISR_callback)(void))
{
    pinMode(ROTARY_ENCODER_A_PIN, INPUT);
    pinMode(ROTARY_ENCODER_B_PIN, INPUT);
    pinMode(ROTARY_ENCODER_BUTTON_PIN, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(ROTARY_ENCODER_A_PIN), ISR_callback, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ROTARY_ENCODER_B_PIN), ISR_callback, CHANGE);
    //attachInterrupt(digitalPinToInterrupt(ROTARY_ENCODER_BUTTON_PIN), ISR_callback, CHANGE);
}

// void EncoderBtn::loopTest()
// {
//     if (encoder0Pos != lastReadEncoder0Pos)
//     {
//         lastReadEncoder0Pos = encoder0Pos;
//         Serial.println(encoder0Pos);
//     }
//     if (lastButton != button)
//     {
//         lastButton = button;
//         if (button)
//         {
//             Serial.println("button down");
//         }
//         else
//         {
//             Serial.println("button up");
//         }
//     }
//     delay(2);
// }

//void EncoderBtn::inLoop()
//{
    // //first lets handle rotary encoder button click
    // if (rotaryEncoder.currentButtonState() == BUT_RELEASED)
    // {
    //     //we can process it here or call separate function like:
    //    // rotary_onButtonClick();
    // }

    // //lets see if anything changed
    // int16_t encoderDelta = rotaryEncoder.encoderChanged();

    // //optionally we can ignore whenever there is no change
    // if (encoderDelta == 0)
    //     return;

    // //for some cases we only want to know if value is increased or decreased (typically for menu items)
    // if (encoderDelta > 0)
    //     Serial.print("+");
    // if (encoderDelta < 0)
    //     Serial.print("-");

    // //for other cases we want to know what is current value. Additionally often we only want if something changed
    // //example: when using rotary encoder to set termostat temperature, or sound volume etc

    // //if value is changed compared to our last read
    // if (encoderDelta != 0)
    // {
    //     //now we need current value
    //     int16_t encoderValue = rotaryEncoder.readEncoder();
    //     //process new value. Here is simple output.
    //     Serial.print("Value: ");
    //     Serial.println(encoderValue);
    // }

    // delay(5);
    // if (millis() > 20000)
    //     rotaryEncoder.enable();
//};

void IRAM_ATTR EncoderBtn::readEncoder_ISR()
{
    //uint32_t state = portENTER_CRITICAL_NESTED();
    portENTER_CRITICAL_ISR(&(mux));
    entries++;
    if (isEnabled)
    {
        //button = digitalRead(ROTARY_ENCODER_BUTTON_PIN) == 1;
        //delayMicroseconds(1);
        int8_t ENC_PORT = ((digitalRead(ROTARY_ENCODER_B_PIN)) ? (1 << 1) : 0) | ((digitalRead(ROTARY_ENCODER_A_PIN)) ? (1 << 0) : 0);
        if ((ENC_PORT & 0x03) != (old_AB & 0x03))
        {
            old_AB <<= 2; //remember previous state
            old_AB |= (ENC_PORT & 0x03); //add current state
            encoder0Pos += enc_states[(old_AB & 0x0f)];
            encoder0Pos = _max(_minEncoderValue, encoder0Pos);
            encoder0Pos = _min(_maxEncoderValue, encoder0Pos);
            //Serial.println(entries);
        }
    }
    portEXIT_CRITICAL_ISR(&(mux));
    //portEXIT_CRITICAL_NESTED(state);
}

void EncoderBtn::setRange(int16_t minEnc, int16_t maxEnc)
{
    _minEncoderValue = minEnc;
    _maxEncoderValue = maxEnc;
}

bool EncoderBtn::changedUp()
{
    if (encoder0Pos > lastReadEncoder0Pos)
    {
        Serial.print(entries);
        Serial.print(" ");
        Serial.println(encoder0Pos);
        lastReadEncoder0Pos = encoder0Pos;
        return true;
    }
    return false;
}

bool EncoderBtn::changedDown()
{
    if (encoder0Pos < lastReadEncoder0Pos)
    {
        Serial.print(entries);
        Serial.print(" ");
        Serial.println(encoder0Pos);
        lastReadEncoder0Pos = encoder0Pos;
        return true;
    }
    return false;
}