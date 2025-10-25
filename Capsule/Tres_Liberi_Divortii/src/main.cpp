#include <Arduino.h>
#include "uv.cpp" // Include the UV module;



// put function declarations here:
int myFunction(int, int);

void setup() {
  Serial.println(UV_S()); // Initialize the UV sensor
}

void loop() {
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}