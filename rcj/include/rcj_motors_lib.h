#pragma once
#include <Arduino.h>
#include "const.h"

class rcj_motors_lib{
private:
  void Vector_x(float power){
  if (power > 0)
  {
    digitalWrite(AIN2, 1);
    digitalWrite(DIN1, 1);
    digitalWrite(AIN1, 0);
    digitalWrite(DIN2, 0);
  }
  else if (power < 0)
  {
    digitalWrite(AIN1, 1);
    digitalWrite(DIN2, 1);
    digitalWrite(AIN2, 0);
    digitalWrite(DIN1, 0);
    power *= -1;
  }
  else
  {
    digitalWrite(AIN1, 0);
    digitalWrite(DIN2, 0);
    digitalWrite(AIN2, 0);
    digitalWrite(DIN1, 0);
  }
  analogWrite(PWMA, power);
  analogWrite(PWMD, power);
  }

  void Vector_y(float power){
  if (power > 0)
  {
    digitalWrite(CIN2, 1);
    digitalWrite(BIN1, 1);
    digitalWrite(CIN1, 0);
    digitalWrite(BIN2, 0);
  }
  else if (power < 0)
  {
    digitalWrite(CIN1, 1);
    digitalWrite(BIN2, 1);
    digitalWrite(CIN2, 0);
    digitalWrite(BIN1, 0);
    power *= -1;
  }
  else
  {
    digitalWrite(CIN1, 0);
    digitalWrite(BIN2, 0);
    digitalWrite(CIN2, 0);
    digitalWrite(BIN1, 0);
  }
  analogWrite(PWMB, power);
  analogWrite(PWMC, power);
  }
public:
  void motor_drive_on_vector(int power, int angle){
    angle += 45;
    if (angle > 360){
      angle = angle - 360;
    }
    Vector_x(power * cos(angle * 3.14 / 180));
    Vector_y(power * sin(angle * 3.14 / 180));
  }
};

