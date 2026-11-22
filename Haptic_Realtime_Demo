#include <Wire.h>
#include "Adafruit_DRV2605.h"

Adafruit_DRV2605 drv;

void setup() {
  Serial.begin(115200);

  if (!drv.begin()) {
    Serial.println("Could not find DRV2605L!");
    while (1) delay(10);
  }

  // Uncomment the line below if you are using an LRA motor instead of a standard ERM motor:
  // drv.useLRA();

  // 1. Set the driver to Real-Time Playback (RTP) mode
  drv.setMode(DRV2605_MODE_REALTIME);

  // 2. Set the continuous vibration strength (0 = off, 127 = max strength)
  drv.setRealtimeValue(100); 
}

void loop() {
  // Nothing needed here—the motor will vibrate continuously on its own
}
