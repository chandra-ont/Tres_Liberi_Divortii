#include <Wire.h>


int pin = 21; 
int readNO(){
  int val = analogRead(pin);
  return val;
}