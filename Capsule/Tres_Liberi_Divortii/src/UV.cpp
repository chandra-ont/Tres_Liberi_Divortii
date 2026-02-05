#include <Wire.h>


int pin = 2; 
int readUV(){
  int val = analogRead(pin);
  return val;
}