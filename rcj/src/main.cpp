#pragma once
#include <Arduino.h>
#include <Wire.h>
#include "rcj_motors_lib.h"
#include "rcj_sensors_lib.h"
#include "Setup.h"



IR_locator locator;
line_sensors line;
rcj_motors_lib motors;
gyro mp;

void setup(){
  Setup();
  
  //Serial setup
  Serial.begin(9600);
  // while (!locator.IRLocatorInit());
  // while(!mp.mpuInit());
}
void loop(){ 
  motors.motor_drive_on_vector(100, 0);
}

