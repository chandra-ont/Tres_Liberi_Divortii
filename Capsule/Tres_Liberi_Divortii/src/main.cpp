#include <Arduino.h>
#include "uv.cpp" // Include the UV module;
#include "Light.cpp" // Include the Light module;
#include "M_SD.cpp"
#include "SG90.cpp"
#include "VOC.cpp"
#include "bmp280.cpp"


void setup() {
/*
  Serial.begin(115200);
  U_setup(); // Initialize the UV sensor
  lightSetup(); // Initialize the Light sensor
  SD_setup(12, "x-axis", "y-axiz", "z-axis", "uv", "pressure" );
  SerSetup();
  B_setup();
  vocSetup(readTemperature(), readPressure());
*/
}

void loop() {
  //servo
  int sensorValues[8] = {calSunPos()};
  TurnServo(sensorValues);
}

