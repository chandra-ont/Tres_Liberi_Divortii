#include <ESP32Servo.h>
#include <iostream>

using namespace std;

int pos = 0;   
int servoPin = 18;

Servo myservo; 
void SerSetup() {
    
    ESP32PWM::allocateTimer(0);
	myservo.setPeriodHertz(50);    //50 hz servo
	myservo.attach(servoPin, 1000, 2000);

}

void TurnServo(int turnDegree) {

    int turnDegree = turnDegree/2;
    myservo.write(turnDegree);
}