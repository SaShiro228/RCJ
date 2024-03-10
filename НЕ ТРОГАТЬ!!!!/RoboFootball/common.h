#pragma once

#include <Arduino.h>

#define BT Serial1  

enum direction : int {
  FORWARD = 1,
  LEFT = 8,
  RIGHT = 4,
  BACK = 2,
  ALL = 15
};
 
enum class PLAYER : byte {FORWARD, GOALKEEPER};
extern void (*pFuncPlay)();
void playForward();
void playGoalkeeper();
extern PLAYER player;

const uint8_t CAMERA_ADDRESS = 0x12;

const int ADDRESS_PLAYER = 200;

//pins
const byte BUZZ = 47;

const byte BUTTONMINUS = 15;  // button minus
const byte BUTTONSET = 12;    // button set
const byte BUTTONPLUS = 14;   // button plus

const byte BallDat = 42;
const byte Voltage = A15;

const byte LEDRED = 34;
const byte LEDBLUE = 36;
const byte LEDYELLOW = 38;

const byte AIN1 = 9; //1 мотор
const byte AIN2 = 11;
const byte BIN1 = 29; //2 мотор
const byte BIN2 = 31;

const byte CIN1 = 13; //3 мотор
const byte CIN2 = 5;

const byte DIN1 = 25; //4 мотор
const byte DIN2 = 27;

const byte PWMA = 6;
const byte PWMB = 44;
const byte PWMC = 7;
const byte PWMD = 46;

const byte MotorsSTBY = 30;

const byte Datnum = 16;
const byte DatLine[4] = {A0, A1, A2, A3};

const uint8_t PinDat = A12;
const int  Threshold = 40;  //0-1023

const float k_VIN = 0.015;              

extern int base_start_angle;
