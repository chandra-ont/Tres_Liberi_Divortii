#include <Wire.h>
#include <iostream>

using namespace std;

int analogPins[8] = {34,35,25,26,27,14,12,13};
int adcValues[8];

void lightSetup() {
    
    analogReadResolution(12);        
    analogSetAttenuation(ADC_11db); 
}
int calSunPos() {
     
    for (int i = 0; i < 8; i++) {
        adcValues[i] = analogRead(analogPins[i]);
    }
    int highestValue[2] = {0, 0} ;
    int secoundHValue[2] = {0, 0};
    int turnDegree = 0;  
    for (int i = 0; i < 8; i++) {
        if ( adcValues[i]>highestValue[0]) {
            if (highestValue[0]>secoundHValue[0]) {
                secoundHValue[0] = highestValue[0];
                secoundHValue[1] = highestValue[1];
            }
            highestValue[0] =  adcValues[i];
            highestValue[1] = i;
        }
    }
    if (highestValue[0]-secoundHValue[0]<50) {
        turnDegree = highestValue[1] * 45;
    }
    else {
        turnDegree = highestValue[1] * 45;
        if (highestValue[1]>secoundHValue[1]) {
            turnDegree -= 22.5;
        }
        else if (highestValue[1]<secoundHValue[1]) {
            turnDegree += 22.5;
        }
         
    }

    return turnDegree;

}
