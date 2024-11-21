#include <ArduinoBLE.h>

BLEService customService("12345678-1234-5678-1234-56612abcdef0"); // Custom BLE service

// BLE Characteristics for sending and receiving data
BLEStringCharacteristic sendCharacteristic("12345678-1234-5678-1234-56612abcdef1", BLERead | BLENotify, 20);
BLEStringCharacteristic receiveCharacteristic("12345678-1234-5678-1234-56612abcdef2", BLEWrite | BLEWriteWithoutResponse, 20);

void setup() {
  Serial.begin(9600);
  while (!Serial);  

  if (!BLE.begin()) {
    Serial.println("Starting BLE failed!");
    while (1);
  }

  BLE.setLocalName("Arduino Nano 33 BLE");
  BLE.setAdvertisedService(customService);

  // Add characteristics
  customService.addCharacteristic(sendCharacteristic);
  customService.addCharacteristic(receiveCharacteristic);

  // Add service
  BLE.addService(customService);

  // Start advertising
  BLE.advertise();

  Serial.println("Bluetooth device active, waiting for connections...");
}

void loop() {
  // Listen for BLE peripherals to connect:
  BLEDevice central = BLE.central();

  // If a central is connected to the peripheral:
  if (central) {
    Serial.print("Connected to central: ");
    Serial.println(central.address());

    // While the central is still connected:
    while (central.connected()) {
      if (receiveCharacteristic.written()) {
        // When something is written to the receiveCharacteristic
        String receivedData = receiveCharacteristic.value();
        Serial.print("Received data: ");
        Serial.println(receivedData);

        // Optionally, send data back to central
        sendCharacteristic.writeValue("Hello Central!");
      }
    }

    // When the central disconnects, print it out:
    Serial.print(F("Disconnected from central: "));
    Serial.println(central.address());
  }
}
