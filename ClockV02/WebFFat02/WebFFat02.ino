#include "file_stuff.h"
#include "wifi_stuff.h"

#define FIRMWARE_VERSION "v0.0.3"

void setup() {
  Serial.begin(115200);
  Serial.print("Firmware: "); Serial.println(FIRMWARE_VERSION);
  Serial.println("Booting ...");

  if (!mount_ffat()) {
    rebootESP("ERROR: Cannot mount FFat, Rebooting");
  }
  
  configWiFi();
  confWebSrv();
}

void loop() {
  // reboot if we've told it to reboot
  if (shouldReboot) {
    rebootESP("Web Admin Initiated Reboot");
  }
}

void rebootESP(String message) {
  Serial.print("Rebooting ESP32: "); Serial.println(message);
  ESP.restart();
}