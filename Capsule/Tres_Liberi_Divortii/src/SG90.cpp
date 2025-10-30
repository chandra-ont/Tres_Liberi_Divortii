#include <ESP32Servo.h>


int pos = 0;   
int servoPin = 18;

Servo myservo; 
void SerSetup() {
    
    ESP32PWM::allocateTimer(0);
	myservo.setPeriodHertz(50);    // standard 50 hz servo
	myservo.attach(servoPin, 1000, 2000);

}

int TurnServo(int sensor[8]) {
    int highestValue[2] = {0, 0} ;
    int secoundHValue[2] = {0, 0};
    int turnDegree = 0;
    for (int i = 0; i < 8; i++) {
        if (sensor[i]>highestValue[0]) {
            if (highestValue[0]>secoundHValue[0]) {
                secoundHValue[0] = highestValue[0];
                secoundHValue[1] = highestValue[1];
            }
            highestValue[0] = sensor[i];
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
    turnDegree = std::floor(turnDegree/2);
    myservo.write(turnDegree);  
}