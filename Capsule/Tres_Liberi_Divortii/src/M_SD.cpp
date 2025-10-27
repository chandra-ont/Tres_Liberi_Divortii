#include <SPI.h>
#include <SD.h>
#include <SdFat.h>
// #include <string>
// using std::string>

File root;
File dataFile;
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
void SD_setup(int spiPin, String h1, String h2, String h3, String h4, String h5){
    

    Serial.println("Initializing SD card...");
    while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
    }
    if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
    }
    Serial.println("\n initialization done.");

    root = SD.open("/");
    printDirectory(root, 0);
    root.close();

    String header = h1 + "," + h2 + "," + h3 + "," + h4 + "," + h5;
    Serial.print("Starting up file.csv \n headers: ");
    Serial.println(header);

    dataFile = SD.open("file.csv", FILE_WRITE);
    if (dataFile) {
    Serial.print("Writing to file.csv...");
    dataFile.println(header); 
    } else {
    Serial.println("error opening file.csv");
    }
    dataFile.close();
}
void SD_log(String data){
    dataFile = SD.open("file.csv", FILE_WRITE);
    if (dataFile) {
    dataFile.println(data+"\n"); 
    dataFile.close();
    Serial.println("Wrote new line to file.csv");
    } else {
    Serial.println("error opening file.csv");
    }
}


