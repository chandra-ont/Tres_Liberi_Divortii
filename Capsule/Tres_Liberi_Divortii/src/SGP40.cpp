#include <Wire.h>
#include "Adafruit_SGP40.h"

Adafruit_SGP40 sgp;


void SGP_setup() {
  while (!Serial) { delay(10); } // Wait for serial console to open!

  Serial.println("SGP40 test");

  if (! sgp.begin()){
    Serial.println("Sensor not found :(");
    while (1);
  }
  Serial.print("Found SGP40 serial #");
  Serial.print(sgp.serialnumber[0], HEX);
  Serial.print(sgp.serialnumber[1], HEX);
  Serial.println(sgp.serialnumber[2], HEX);
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

  if (true){
    return voc_index;
  
  }
}