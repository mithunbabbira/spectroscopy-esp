#include <Wire.h>
#include "SparkFun_AS7265X.h"
#include "BluetoothSerial.h"

AS7265X sensor;
BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_Spectral"); // Bluetooth device name
  delay(2000);  // Wait for serial to initialize
  
  Wire.begin(21, 22);  // SDA = 21, SCL = 22
  Wire.setClock(100000);
  delay(500);  // Short delay to stabilize I2C
  
  Serial.println("AS7265x Spectral Triad Example");
  
  // Retry sensor initialization
  for (int i = 0; i < 5; i++) {
    if (sensor.begin() == true) {
      Serial.println("Sensor initialized successfully!");
      break;
    } else {
      Serial.println("Sensor not found. Retrying...");
      delay(1000);  // Wait before retrying
    }
  }
  
  if (!sensor.isConnected()) {
    Serial.println("Sensor does not appear to be connected. Please check wiring. Freezing...");
    while (1);
  }

  Serial.println("A,B,C,D,E,F,G,H,R,I,S,J,T,U,V,W,K,L");
}

void loop() {
  sensor.takeMeasurements();  // This is a hard wait while all 18 channels are measured
  String data = String(sensor.getCalibratedA()) + "," +
                String(sensor.getCalibratedB()) + "," +
                String(sensor.getCalibratedC()) + "," +
                String(sensor.getCalibratedD()) + "," +
                String(sensor.getCalibratedE()) + "," +
                String(sensor.getCalibratedF()) + "," +
                String(sensor.getCalibratedG()) + "," +
                String(sensor.getCalibratedH()) + "," +
                String(sensor.getCalibratedR()) + "," +
                String(sensor.getCalibratedI()) + "," +
                String(sensor.getCalibratedS()) + "," +
                String(sensor.getCalibratedJ()) + "," +
                String(sensor.getCalibratedT()) + "," +
                String(sensor.getCalibratedU()) + "," +
                String(sensor.getCalibratedV()) + "," +
                String(sensor.getCalibratedW()) + "," +
                String(sensor.getCalibratedK()) + "," +
                String(sensor.getCalibratedL());

  SerialBT.println(data); // Send data over Bluetooth
  delay(2000);
}