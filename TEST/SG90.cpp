#include <iostream>
#include <cmath>
#include "SG90.h"

using namespace std;

void TurnServo(int sensor[8]) {
    int highestValue[2] = {0, 0};
    int secondHValue[2] = {0, 0};
    int turnDegree = 0;

    for (int i = 0; i < 8; i++) {
        if (sensor[i] > highestValue[0]) {
            if (highestValue[0] > secondHValue[0]) {
                secondHValue[0] = highestValue[0];
                secondHValue[1] = highestValue[1];
            }
            highestValue[0] = sensor[i];
            highestValue[1] = i;
        }
    }
    if (!highestValue[1]==1){
        turnDegree = 0;
        if (highestValue[1] > secondHValue[1]) {
            turnDegree -= 22.5;
        } else if (highestValue[1] < secondHValue[1]) {
            turnDegree += 22.5;
        }
    } else {
    turnDegree = (highestValue[1]+1) * 45;
    if (!(highestValue[0] - secondHValue[0] < 50)) {
        
        if (highestValue[1] > secondHValue[1]) {
            turnDegree -= 22.5;
        } else if (highestValue[1] < secondHValue[1]) {
            turnDegree += 22.5;
        }
    }
    }
    turnDegree = std::floor(turnDegree / 2.0);
    cout << turnDegree << endl;w
}
