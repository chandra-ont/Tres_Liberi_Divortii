#include <Arduino.h>
#include <SPI.h>

#include "M_SD.h"
#include "SGP40.h"
#include "esp_timer.h"
#include "bmp280.h"
#include <Wire.h>
#include <SPI.h>

#define PIN_MISO 19
#define PIN_MOSI 23
#define PIN_SCK  18
#define CS_LORA  1
#define CS_SD    2

#define SDA_PIN 4   
#define SCL_PIN 21

#define RXD2 16
#define TXD2 17


SPIClass spi(VSPI);


using namespace std;



int temp = 0;
int pressure = 0;

void setup()
{
    Serial.begin(115200);
    //UART FOR GPS NOT USED IN KVAL
    // Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);



    //SPI CONFIG
    spi.begin(PIN_SCK, PIN_MISO, PIN_MOSI);

    pinMode(CS_SD, OUTPUT);
    pinMode(CS_LORA, OUTPUT);

    digitalWrite(CS_SD, HIGH);
    digitalWrite(CS_LORA, HIGH);

    //I²C SETUP
    Wire.begin(SDA_PIN, SCL_PIN);




    // SETUP sensors
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