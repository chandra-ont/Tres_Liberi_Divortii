#include <Wire.h>


int pin = 2 ; 
int readNO(){
  int val = analogRead(pin);
  return val;
}