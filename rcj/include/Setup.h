#include <Arduino.h>
#include "const.h"

void Setup(){
    //sensors setup
  pinMode(s1, OUTPUT); 
  pinMode(s2, OUTPUT); 
  pinMode(s3, OUTPUT); 
  //motors setup
  pinMode(AIN1, OUTPUT); // Vector1 AD
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT); // Vector2 BC
  pinMode(BIN2, OUTPUT);
  pinMode(CIN1, OUTPUT);
  pinMode(CIN2, OUTPUT);
  pinMode(DIN1, OUTPUT);
  pinMode(DIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(PWMC, OUTPUT);
  pinMode(PWMD, OUTPUT);
  pinMode(STB, OUTPUT);

  pinMode(Dribler, OUTPUT);
  
  pinMode(LED, OUTPUT);
  pinMode(Button1Pin, INPUT_PULLUP);
  pinMode(Button2Pin, INPUT_PULLUP);
  digitalWrite(STB, 1);
}