#include "Adafruit_LTR390.h"

Adafruit_LTR390 ltr = Adafruit_LTR390();

struct UVConfig {
  bool found;
  uint8_t mode;
  uint8_t gain;
  uint8_t resolution;
  uint16_t threshold_low;
  uint16_t threshold_high;
};

UVConfig UV_S() {
  UVConfig cfg{};
  if (!ltr.begin()) {
    cfg.found = false;
    return cfg;
  }
  cfg.found = true;
  ltr.setMode(LTR390_MODE_UVS);
  cfg.mode = ltr.getMode();
  ltr.setGain(LTR390_GAIN_3);
  cfg.gain = ltr.getGain();
  ltr.setResolution(LTR390_RESOLUTION_16BIT);
  cfg.resolution = ltr.getResolution();
  cfg.threshold_low = 100;
  cfg.threshold_high = 1000;
  ltr.setThresholds(cfg.threshold_low, cfg.threshold_high);
  ltr.configInterrupt(true, LTR390_MODE_UVS);
  return cfg;
}

void UV_D() {
  if (ltr.newDataAvailable()) {
      Serial.print("UV data: "); 
      Serial.print(ltr.readUVS());
  }
  
  delay(100);
}
