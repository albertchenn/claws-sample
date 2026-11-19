#include <Wire.h>
#include "Adafruit_DRV2605.h"

Adafruit_DRV2605 drv;

void setup() {
  Serial.begin(115200);
  Serial.println("Initializing DRV2605L Haptic Driver...");

  // Initialize the DRV2605L (Default I2C address is 0x5A)
  if (!drv.begin()) {
    Serial.println("Could not find DRV2605L! Check your SDA/SCL wiring.");
    while (1) delay(10);
  }

  // Select the internal ROM waveform library (1-5 are for ERM motors, 6 is for LRA)
  drv.selectLibrary(1);

  // Set mode to Internal Trigger (triggered by the drv.go() command over I2C)
  drv.setMode(DRV2605_MODE_INTTRIG);

  // Motor Type Configuration:
  // By default, the library uses ERM (standard coin/pager vibration motors).
  // If you are using a Linear Resonant Actuator (LRA), uncomment the line below:
  // drv.useLRA();
}

void loop() {
  // --- Example 1: Single Crisp Click ---
  Serial.println("Playing Effect #1: Strong Click");
  drv.setWaveform(0, 1);  // Slot 0: Effect #1 (Strong Click - 100%)
  drv.setWaveform(1, 0);  // Slot 1: 0 signals the end of the sequence
  drv.go();               // Trigger the playback
  delay(1000);

  // --- Example 2: Double Click ---
  Serial.println("Playing Effect #10: Double Click");
  drv.setWaveform(0, 10); // Slot 0: Effect #10 (Double Click - 100%)
  drv.setWaveform(1, 0);  // End of sequence
  drv.go();
  delay(1000);

  // --- Example 3: Chaining Multiple Effects Together ---
  // You can queue up to 8 waveforms in slots 0 through 7
  Serial.println("Playing Chained Sequence: Ramp Up -> Buzz -> Click");
  drv.setWaveform(0, 82); // Slot 0: Transition Ramp Up Long Smooth 1
  drv.setWaveform(1, 47); // Slot 1: Buzz 1 (100%)
  drv.setWaveform(2, 1);  // Slot 2: Strong Click
  drv.setWaveform(3, 0);  // Slot 3: End of sequence
  drv.go();

  delay(2500);
}
