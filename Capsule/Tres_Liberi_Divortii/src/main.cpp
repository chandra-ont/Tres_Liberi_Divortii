#include <Arduino.h>
#include "uv.cpp" // Include the UV module;
#include "Light.cpp" // Include the Light module;



// put function declarations here:
int myFunction(int, int);

void setup() {
  Serial.begin(115200);
  U_setup(); // Initialize the UV sensor
  lightSetup(); // Initialize the Light sensor
}

void loop() {
  // put your main code here, to run repeatedly:
}

