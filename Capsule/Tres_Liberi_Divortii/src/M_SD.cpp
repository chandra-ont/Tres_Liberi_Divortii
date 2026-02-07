#include <SPI.h>
#include <SD.h>
#include <SdFat.h>
#include "M_SD.h"

SPIClass* spi_instance = nullptr;

File root;
File datFile;
void printDirectory(File dir, int numTabs) {


  while (true) {

    File entry =  dir.openNextFile();

    if (! entry) {

      

      break;

    }

    for (uint8_t i = 0; i < numTabs; i++) {

      Serial.print('\t');

    }

    Serial.print(entry.name());

    if (entry.isDirectory()) {

      Serial.println("/");

      printDirectory(entry, numTabs + 1);

    } else {

      // files have sizes, directories do not

      Serial.print("\t\t");

      Serial.println(entry.size(), DEC);

    }

    entry.close();

  }
}
int SD_setup(int csPin,
              const char* h1,
              const char* h2,
              const char* h3,
              const char* h4,
              const char* h5,
              const char* h6,
              const char* h7,
              const char* h8,
              const char* h9
              ) {
    

    Serial.println("Initializing SD card...");
    Serial.print("SPI instance: ");
    Serial.println((uint32_t)spi_instance, HEX);
    Serial.print("SD CS pin: ");
    Serial.println(csPin);
    
    int result = false;
    
    if (spi_instance != nullptr) {
      Serial.println("Using external SPI instance...");
      result = SD.begin(csPin, *spi_instance);
    } else {
      Serial.println("Using default SPI...");
      result = SD.begin(csPin);
    }
    
    if (!result) {
      Serial.println("initialization failed!");
      return false;
    }
    Serial.println("\n initialization done.");

    uint8_t cardType = SD.cardType();
    Serial.print("Card Type: ");
    Serial.println(cardType);

    uint64_t cardSize = SD.cardSize();
    Serial.print("Card Size (MB): ");
    Serial.println(cardSize / (1024 * 1024));

    root = SD.open("/");
    if (!root) {
      Serial.println("Failed to open root directory after init");
      return false;
    }
    printDirectory(root, 0);
    root.close();
    String header = String(h1) + "," + String(h2) + "," + String(h3) + "," + String(h4) + "," + String(h5);
    Serial.print("Starting up file.csv \n headers: ");
    Serial.println(header);

    datFile = SD.open("file.csv", FILE_WRITE);
    if (datFile) {

    datFile.println(header); 
    datFile.close();
    return true;
    } else {
    return false;
    }
    datFile.close();
}
int SD_log(int64_t time,
    float tf,
    int32_t voc_index,
    uint16_t sraw,
    int temp,
    int pressure,
    int NO,
    int UV) {
    File datFile = SD.open("file.csv", FILE_WRITE);
    if (datFile) {
        datFile.printf("%lld,%f,%d,%u,%d,%d,%d,%d\n",
                        time, tf, voc_index, sraw, temp, pressure, NO, UV);
        datFile.close();
        Serial.println("Wrote new line to file.csv");
        return true;
    } else {
        Serial.println("error opening file.csv");
        return false;
    }
}

void printCSVFile(const char* filename) {
  // Open the file for reading
  File dataFile = SD.open(filename, FILE_READ);
  
  if (!dataFile) {
    Serial.print("Error opening file: ");
    Serial.println(filename);
    return;
  }
  
  Serial.print("Reading file: ");
  Serial.println(filename);
  Serial.println("----------------------------------------");
  
  int lineNumber = 1;
  
  // Read and print all lines one by one
  while (dataFile.available()) {
    String line = dataFile.readStringUntil('\n');
    line.trim(); // Remove whitespace and carriage returns
    
    if (line.length() > 0) {
      Serial.print("Line ");
      Serial.print(lineNumber);
      Serial.print(": ");
      Serial.println(line);
      lineNumber++;
    }
  }
  
  Serial.println("----------------------------------------");
  Serial.print("Total lines: ");
  Serial.println(lineNumber - 1);
}

