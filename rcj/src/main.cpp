#include <Arduino.h>
#include <Wire.h>

#include "rcj_motors_lib.h"
#include "rcj_sensors_lib.h"
#include "const.h"



IR_locator locator;
line_sensors line;
rcj_motors_lib motors;
gyro mp;

void setup(){
  //sensors setup
  pinMode(s0, OUTPUT); 
  pinMode(s1, OUTPUT); 
  pinMode(s2, OUTPUT); 
  pinMode(s3, OUTPUT); 
  pinMode(Button1Pin, INPUT_PULLUP);
  pinMode(Button2Pin, INPUT_PULLUP);
  //motors setup
  pinMode(AIN1 ,OUTPUT); // Vector1 AD
  pinMode(AIN2 ,OUTPUT);
  pinMode(BIN1 ,OUTPUT); // Vector2 CBbool isIRBallFound = false;

  pinMode(BIN2 ,OUTPUT);
  pinMode(CIN1 ,OUTPUT);
  pinMode(CIN2 ,OUTPUT);
  pinMode(DIN1 ,OUTPUT);
  pinMode(DIN2 ,OUTPUT);
  pinMode(PWMA ,OUTPUT);
  pinMode(PWMB ,OUTPUT);
  pinMode(PWMC ,OUTPUT);
  pinMode(PWMD ,OUTPUT);
  pinMode(STB ,OUTPUT);
  digitalWrite(30, 1);
  
  //Serial setup
  Serial.begin(9600);
  while (!locator.IRLocatorInit());
  while(!mp.mpuInit());
}
void loop(){ 
  motors.motor_drive_on_vector(100, locator.get_Derection_Auto());
  line.readline();
  Serial.println(line.data[1]);
}

