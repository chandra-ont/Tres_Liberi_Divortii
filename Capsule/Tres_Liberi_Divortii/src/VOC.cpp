#include <Wire.h>
#include "Adafruit_SGP40.h"

Adafruit_SGP40 sgp;
float heat, hum;

void vocSetup(float t, float h) {
     heat = t;
     hum = h;
  Serial.println("SGP40 Starting");

  if (! sgp.begin()){
    Serial.println("SGP40 sensor not found :(");
    while (1);
  }

  

  Serial.print("Found SGP40 serial #");
  Serial.print(sgp.serialnumber[0], HEX);
  Serial.print(sgp.serialnumber[1], HEX);
  Serial.println(sgp.serialnumber[2], HEX);
}

int vocRead() {
    uint16_t sraw;
    int32_t voc_index;

    sraw = sgp.measureRaw(heat, hum);
    voc_index = sgp.measureVocIndex(heat, hum);
    return voc_index;

    delay(1000);
}
