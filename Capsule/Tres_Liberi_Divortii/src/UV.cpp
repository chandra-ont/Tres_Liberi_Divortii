#include <Wire.h>


int UVpin = 2; 
int readUV(){
  int val = analogRead(UVpin);
  return val;
}