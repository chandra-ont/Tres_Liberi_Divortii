#include <Arduino.h>
#include <SPI.h>

#include "M_SD.h"
#include "SGP40.h"
#include "esp_timer.h"
#include "bmp280.h"
#include "WS.h"
#include "Ozone.h"
#include "NO.h"
#include "UV.h"
#include "gyro.h"

#include <Wire.h>
#include <SPI.h>
#include <vector>

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

struct SensorData {
    int64_t time;
    float tf;
    int32_t voc_index;
    uint16_t sraw;
    int temp;
    int pressure;
    int NO;
    int UV;
    float gyrox;
    float gyroy;
    float gyroz;
    String toString() const {
        return String(time) + "," +
               String(temp) + "," +
               String(pressure) + "," +
               String(tf) + "," +
               String(voc_index) + "," +
               String(NO) + "," +
               String(UV) + "," +
               String(gyrox) + "," +
               String(gyroy) + "," +
               String(gyroz) + "," +
               String(sraw);
    }
};

struct SensorInfo {
    String sensorName;
    String status;
    
};



int temp = 0;
int pressure = 0;

SensorInfo UnitNames[8] = {
    {"SD_card", "OK"},
    {"Lora", "OK"},
    {"Ozone", "OK"},
    {"VOC", "OK"},
    {"BMP280", "OK"},
    {"NO", "OK"},
    {"UV", "OK"},
    {"Gyro", "OK"}
};

void Logg();
void startup();
String Test();
SensorData readSensors();
String getinfo();
void test();

void setup()
{
    Serial.begin(9200);
    //UART FOR GPS NOT USED IN KVAL
    // Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);



    //SPI CONFIG
    spi.begin(PIN_SCK, PIN_MISO, PIN_MOSI);

    pinMode(CS_SD, OUTPUT);
    

    digitalWrite(CS_SD, HIGH);
    

    //I²C SETUP
    Wire.begin(SDA_PIN, SCL_PIN);




    // SETUP sensors
    if (!SD_setup("Time", "Voc_idx", "Sraw_SGP", "Temp", "pressure", "NO", "UV", "ozone", "gyro")) {
        UnitNames[0].status = "Failed to write SD";
    }
    if (!SGP_setup()){
        UnitNames[3].status = "SGP40 not found";
    }
    if (!Osetup()){
        UnitNames[2].status = "Ozone sensor not found";
    }
    if (!B_setup()){
        UnitNames[4].status = "BMP280 not found";
    }
    
    UnitNames[4].status = B_setup();
    test();
}

void loop()
{        
    startup();
    
    
    
    printCSVFile("file.csv");
}


void Logg(){
    

    SensorData d = readSensors();
    SD_log(d.time, d.voc_index, d.sraw, d.temp, d.pressure);
    
    Serial.println("Logged data");
};



void test(){ 
    String data = readSensors().toString();
    String info = getinfo();
    String combined = info + "\n" + data;
    WsetupAndSend(combined.c_str());
}

String getinfo() {
    String info = "";
    for (int i = 0; i < 8; i++) {
        info += UnitNames[i].sensorName + ": " + UnitNames[i].status + "," +"\n";
    }
    
    return info;
}

SensorData readSensors() {
    SensorData d;
    d.gyrox, d.gyroy, d.gyroz = GetGyroData();
    d.time = esp_timer_get_time();
    d.temp = readTemperature();
    d.pressure = readPressure();
    d.NO = readNO();
    d.UV = readUV();
    d.tf = static_cast<float>(d.temp);
    d.voc_index = SGP_loop(d.tf);
    d.sraw = Get_raw(d.tf);

    return d;
}