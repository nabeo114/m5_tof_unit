/* This example shows how to use continuous mode to take
range measurements with the VL53L0X. It is based on
vl53l0x_ContinuousRanging_Example.c from the VL53L0X API.

The range readings are in units of mm. */

#include <M5StickC.h>
#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor;

void setup() {
  // put your setup code here, to run once:
  M5.begin();
  M5.Lcd.setRotation(3);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0, 2);
  M5.Lcd.println("ToF TEST");

  Serial.begin(115200);
  Wire.begin(32,33); // M5StickC ToF UNIT

  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }

  // Start continuous back-to-back mode (take readings as
  // fast as possible).  To use continuous timed mode
  // instead, provide a desired inter-measurement period in
  // ms (e.g. sensor.startContinuous(100)).
  sensor.startContinuous();
}

void loop() {
  // put your main code here, to run repeatedly:
  uint16_t range = sensor.readRangeContinuousMillimeters();
  M5.Lcd.setCursor(0, 20, 2);
  M5.Lcd.printf("Range: %4d mm", range);
  if (sensor.timeoutOccurred())
  {
    Serial.print(" TIMEOUT");
  }

  delay(10);
}
