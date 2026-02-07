#include "LittleFS.h"


#include <Arduino.h>


#include "M_SD.h"
#include "SGP40.h"
#include "esp_timer.h"
#include "bmp280.h"

#include "Ozone.h"
#include "NO.h"
#include "UV.h"
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
    String toString() const {
        return String(time) + "," +
               String(temp) + "," +
               String(pressure) + "," +
               String(tf) + "," +
               String(voc_index) + "," +
               String(NO) + "," +
               String(UV) + "," +
               
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

void appendToFlash(const SensorData &d) {
    File f = LittleFS.open("/log.csv", FILE_APPEND);
    if (!f) {
        Serial.println("Failed to open file");
        return;
    }

    String line = d.toString();
    f.println(line);

    f.close();
}
void ensureCSVHeader() {
    if (!LittleFS.exists("/log.csv")) {
        File f = LittleFS.open("/log.csv", FILE_WRITE);
        if (!f) {
            Serial.println("Failed to create log file");
            return;
        }

        f.println("time,temp,pressure,tf,voc_index,NO,UV,sraw");
        f.close();

        Serial.println("CSV header written");
    }
}


void setup()
{
    Serial.begin(9600);
    ensureCSVHeader();
    //UART FOR GPS NOT USED IN KVAL
    // Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);



    //SPI CONFIG
    spi.begin(PIN_SCK, PIN_MISO, PIN_MOSI);

    pinMode(CS_SD, OUTPUT);
    
    digitalWrite(CS_SD, LOW);
    
    // Pass SPI instance to SD module
    spi_instance = &spi;

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
    
    
    SensorData data = readSensors();
    
    if (UnitNames[0].status == "OK") {
        SD_log(data.time, data.tf, data.voc_index, data.sraw, data.temp, data.pressure, data.NO, data.UV);
    }
    else {
        appendToFlash(data);    
    }
    delay(5000);  // DO NOT log every loop
}


void Logg(){
    

    SensorData d = readSensors();
    if (UnitNames[0].status == "OK") {
    SD_log(d.time, d.tf, d.voc_index, d.sraw, d.temp, d.pressure, d.NO, d.UV);
    }

};



void test(){ 
    String data = readSensors().toString();
    String info = getinfo();
    String combined = info + "\n" + data;
    Serial.println(combined);
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
    d.time = esp_timer_get_time();
    if (UnitNames[4].status == "OK") {
    d.temp = readTemperature();
    d.pressure = readPressure();
    }
    else {d.temp, d.pressure = 0, 0;}
    d.NO = readNO();
    d.UV = readUV();

    d.tf = static_cast<float>(d.temp);
    d.voc_index = SGP_loop(d.tf);
    d.sraw = Get_raw(d.tf);

    return d;
}