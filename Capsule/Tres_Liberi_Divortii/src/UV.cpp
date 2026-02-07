#include <Wire.h>


int UVpin = 0; 
int readUV(){
  int val = analogRead(UVpin);
  return val;
}