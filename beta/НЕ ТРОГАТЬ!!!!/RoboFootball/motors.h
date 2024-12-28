#pragma once
#include <Arduino.h>
//#include <Wire.h>

extern int baseSpeed;

void drive(int left1,int right1,int left2, int right2);
void drive(float angle);
void drive(int vx, int vy);
void turn_angle(float angle);
void turn_start_angle();
byte drive2ball();
