#include "MyClock.h"
//#include "EncoderBtn.h"

MyClock clockD;

//EncoderBtn enc;

void setup()
{
  Serial.begin(115200);
  //enc.setup([] { enc.readEncoder_ISR(); });
  delay(30);
  clockD.setup();
  while (!Serial.availableForWrite())
  {
    delay(2);
  }
  delay(300);
  Serial.println("MyClock test");
  //Serial.println("enc test");
}

void loop(void)
{
  // if (enc.changedUp())
  // {
  //   Serial.println("enc up");
  // }
  // if (enc.changedDown())
  // {
  //   Serial.println("enc down");
  // }
  // delay(1);
  clockD.inLoop();
}
