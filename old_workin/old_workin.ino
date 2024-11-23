#include <Wire.h>
#include "SparkFun_AS7265X.h"

AS7265X sensor;

void setup() {
  Serial.begin(115200);
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

  Serial.print(sensor.getCalibratedA()); // 410nm
  Serial.print(",");
  Serial.print(sensor.getCalibratedB()); // 435nm
  Serial.print(",");
  Serial.print(sensor.getCalibratedC()); // 460nm
  Serial.print(",");
  Serial.print(sensor.getCalibratedD()); // 485nm
  Serial.print(",");
  Serial.print(sensor.getCalibratedE()); // 510nm
  Serial.print(",");
  Serial.print(sensor.getCalibratedF()); // 535nm
  Serial.print(",");

  Serial.print(sensor.getCalibratedG()); // 560nm
  Serial.print(",");
  Serial.print(sensor.getCalibratedH()); // 585nm
  Serial.print(",");
  Serial.print(sensor.getCalibratedR()); // 610nm
  Serial.print(",");
  Serial.print(sensor.getCalibratedI()); // 645nm
  Serial.print(",");
  Serial.print(sensor.getCalibratedS()); // 680nm
  Serial.print(",");
  Serial.print(sensor.getCalibratedJ()); // 705nm
  Serial.print(",");

  Serial.print(sensor.getCalibratedT()); // 730nm
  Serial.print(",");
  Serial.print(sensor.getCalibratedU()); // 760nm
  Serial.print(",");
  Serial.print(sensor.getCalibratedV()); // 810nm
  Serial.print(",");
  Serial.print(sensor.getCalibratedW()); // 860nm
  Serial.print(",");
  Serial.print(sensor.getCalibratedK()); // 900nm
  Serial.print(",");
  Serial.print(sensor.getCalibratedL()); // 940nm
  Serial.println();

  delay(2000);
}