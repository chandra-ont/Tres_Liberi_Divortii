#include "Light.h"
#include "SG90.h"

int main() {
    int adcValues[8];          // array to hold 8 values
    calSunPos(adcValues);      // fill array with readings
    TurnServo(adcValues);      // use those readings
    return 0;
}
