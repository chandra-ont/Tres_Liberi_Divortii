#include <Wire.h>
#include "Adafruit_SGP40.h"

Adafruit_SGP40 sgp;

int trys = 0;
int SGP_setup() {
 while (!sgp.begin() && trys < 10) {
    Serial.println("Sensor not found :(");
    trys++;
    delay(1000);
  }
  
  if (trys >= 10) {
    return false;
  }
  return true;
}

int counter = 0;
uint16_t Get_raw(float t ) {
  uint16_t sraw;
  float h = 80.0;

  
  sraw = sgp.measureRaw(t, h);
  Serial.print("Raw measurement: ");
  Serial.println(sraw);
  return sraw;
}
int32_t SGP_loop(float t ) {
  float h = 80.0;
  int32_t voc_index;
  
  


  voc_index = sgp.measureVocIndex(t, h);
  Serial.print("Voc Index: ");
  Serial.println(voc_index);

  
  return voc_index;
}