#include <SPI.h>
#include <SD.h>
#include <SdFat.h>
// #include <string>
// using std::string>

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
int SD_setup(
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
    
    if (!SD.begin(2)) {
    Serial.println("initialization failed!");
    return false;
    }
    Serial.println("\n initialization done.");

    root = SD.open("/");
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
int SD_log(int64_t time, int32_t voc, uint16_t sraw, float temp, float pressure) {
    File datFile = SD.open("file.csv", FILE_WRITE);
    if (datFile) {
        datFile.printf("%lld,%d,%u,%f,%f\n",
                        (long long)time, voc, sraw, temp, pressure);
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
  
  dataFile.close();
}

