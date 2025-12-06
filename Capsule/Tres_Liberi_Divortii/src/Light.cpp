#include <Wire.h>
#include <iostream>

using namespace std;

int analogPins[8] = {36, 39, 34, 35, 32, 33, 25, 26};
int adcValues[8];

void lightSetup() {
    
    analogReadResolution(12);        
    analogSetAttenuation(ADC_11db); 
}
int calSunPos() {
     
    for (int i = 0; i < 8; i++) {
    cin >> adcValues[i] ;       //analogRead(analogPins[i]);
    }

    
    return adcValues[8];

}
