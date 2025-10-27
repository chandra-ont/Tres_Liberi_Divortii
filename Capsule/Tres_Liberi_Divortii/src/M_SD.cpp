#include <SPI.h>
#include <SD.h>
#include <SdFat.h>

File root;
void printDirectory(File dir, int numTabs) {


  while (true) {

    File entry =  dir.openNextFile();

    if (! entry) {

      // no more files

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
void SD_setup(int SPI_p){
    

    Serial.println("Initializing SD card...");
    while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
    }
    if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
    }
    Serial.println("/n initialization done.");

    root = SD.open("/");

    printDirectory(root, 0);

    Serial.println("done!");
}



