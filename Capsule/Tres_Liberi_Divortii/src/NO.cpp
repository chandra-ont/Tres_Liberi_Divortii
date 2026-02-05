#include <Wire.h>


int pin = 21; 
int read(){
  int val = analogRead(pin);
  return val;
}