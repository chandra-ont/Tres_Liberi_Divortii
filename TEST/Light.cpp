#include <iostream>
#include "Light.h"
using namespace std;

void calSunPos(int adcValues[8]) {
    for (int i = 0; i < 8; i++) {
        cout << "Enter value " << i << ": ";
        cin >> adcValues[i];
    }
}