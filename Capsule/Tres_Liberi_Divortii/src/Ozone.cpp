#include <Arduino.h>
#include <Wire.h>
#include <DFRobot_OzoneSensor.h>

// Use default Wire (hardware I2C)
// If sensor address is one of the defined addresses, set it here:
#define SENSOR_ADDR OZONE_ADDRESS_0  // 0x70

DFRobot_OzoneSensor ozone; // uses default Wire

int Osetup() {
  int t=0;
  delay(1000); // wait for sensor to power up
  // initialize sensor at address SENSOR_ADDR
  if (!ozone.begin(SENSOR_ADDR)) {
    Serial.println("Ozone sensor init failed. Check wiring and address.");
    while (1) delay(1000);
    t++;
    if (t > 3) {
    t=0;
    return false;
    };
  }
  Serial.println("Ozone sensor initialized.");
  return true;
  // Set measurement mode: automatic (active) or passive
  // MEASURE_MODE_AUTOMATIC = 0x00, MEASURE_MODE_PASSIVE = 0x01
  ozone.setModes(MEASURE_MODE_AUTOMATIC);
}

int16_t readOzoneData() {
  // readOzoneData() returns ozone concentration in ppb (int16_t)
  int16_t ppb = ozone.readOzoneData(20); // collect 20 samples (default is 20)

  return ppb;
}