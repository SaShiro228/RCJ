#pragma once

#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#define BNO055_SAMPLERATE_DELAY_MS (100)


extern Adafruit_BNO055 bno;

uint16_t readSensors(byte dir);
int getAngle(); 
bool isBall();
int getCamAngle();
