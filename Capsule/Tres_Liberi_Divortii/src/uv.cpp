#include "Adafruit_LTR390.h"

Adafruit_LTR390 UV = Adafruit_LTR390();

void U_setup() {
  Serial.begin(115200);
  Serial.println("Adafruit LTR-390 test");

  if ( ! UV.begin() ) {
    Serial.println("Couldn't find UV sensor!");
    while (1) delay(10);  
  }
  Serial.println("Found UV sensor!");

  UV.setMode(LTR390_MODE_UVS);
  if (UV.getMode() == LTR390_MODE_ALS) {
    Serial.println("In ALS mode");
  } else {
    Serial.println("In UVS mode");
  }

  UV.setGain(LTR390_GAIN_3);
  Serial.print("Gain : ");
  switch (UV.getGain()) {
    case LTR390_GAIN_1: Serial.println(1); break;
    case LTR390_GAIN_3: Serial.println(3); break;
    case LTR390_GAIN_6: Serial.println(6); break;
    case LTR390_GAIN_9: Serial.println(9); break;
    case LTR390_GAIN_18: Serial.println(18); break;
  }

  UV.setResolution(LTR390_RESOLUTION_16BIT);
  Serial.print("Resolution : ");
  switch (UV.getResolution()) {
    case LTR390_RESOLUTION_13BIT: Serial.println(13); break;
    case LTR390_RESOLUTION_16BIT: Serial.println(16); break;
    case LTR390_RESOLUTION_17BIT: Serial.println(17); break;
    case LTR390_RESOLUTION_18BIT: Serial.println(18); break;
    case LTR390_RESOLUTION_19BIT: Serial.println(19); break;
    case LTR390_RESOLUTION_20BIT: Serial.println(20); break;
  }

  UV.setThresholds(100, 1000);
  UV.configInterrupt(true, LTR390_MODE_UVS);
}

void U_loop() {
  if (UV.newDataAvailable()) {
      Serial.print("UV data: "); 
      Serial.print(UV.readUVS());
  }
}