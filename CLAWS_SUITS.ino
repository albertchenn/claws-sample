#include <ArduinoBLE.h>

BLEService ledService("19B10000-E8F2-537E-4F6C-D104768A1214");
BLEByteCharacteristic switchChar("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);

// Change this to the exact pin your breadboard LED is connected to (e.g., D7, D0, D1, etc.)
const int externalLedPin = D7; 

void setup() {
  Serial.begin(115200);

  pinMode(externalLedPin, OUTPUT);
  digitalWrite(externalLedPin, LOW); // Start OFF (active-HIGH)

  if (!BLE.begin()) {
    Serial.println("Starting BLE failed!");
    while (1);
  }

  BLE.setLocalName("CLAWS-Haptic");
  BLE.setAdvertisedService(ledService);

  ledService.addCharacteristic(switchChar);
  BLE.addService(ledService);

  BLE.setEventHandler(BLEConnected, bleConnectHandler);
  BLE.setEventHandler(BLEDisconnected, bleDisconnectHandler);
  switchChar.setEventHandler(BLEWritten, switchCharacteristicWritten);

  switchChar.writeValue((byte)0x00);
  BLE.advertise();
  Serial.println("BLE advertising started for external LED");
}

void loop() {
  BLE.poll();
}

void bleConnectHandler(BLEDevice central) {
  Serial.print("Connected to central: ");
  Serial.println(central.address());
}

void bleDisconnectHandler(BLEDevice central) {
  Serial.print("Disconnected from central: ");
  Serial.println(central.address());
  BLE.advertise();
}

void switchCharacteristicWritten(BLEDevice central, BLECharacteristic characteristic) {
  byte value = switchChar.value();
  Serial.print("Received byte: ");
  Serial.println(value);

  // External LEDs wired to GND are active-HIGH:
  if (value == 1) {
    digitalWrite(externalLedPin, HIGH); // Turn ON external LED
  } else if (value == 0) {
    digitalWrite(externalLedPin, LOW);  // Turn OFF external LED
  }
}