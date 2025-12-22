#include <Arduino.h>
#include "M_SD.h"
#include "SGP40.h"
#include "esp_timer.h"
#include "bmp280.h"
using namespace std;

int temp = 0;
int pressure = 0;

void setup()
{
    Serial.begin(9600);
    SD_setup(4, "Time", "Voc_idx", "Sraw_SGP", "Temp", "pressure");
    SGP_setup();
    B_setup();
}

void loop()
{
    for (int i = 0; i < 10; i++) {
        
    float tf = static_cast<float>(temp);   
    int32_t voc_index = SGP_loop(tf);
    uint16_t sraw = Get_raw(tf);
    int64_t time = esp_timer_get_time();
    int temp = readTemperature();
    int pressure = readPressure();

    SD_log(time, voc_index, sraw, temp, pressure);
    delay(2000);
    Serial.println("Logged data");
    }
    Serial.println("Finished logging 10 entries");
    printCSVFile("file.csv");
}