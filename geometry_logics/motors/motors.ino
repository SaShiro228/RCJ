#include <Wire.h>
#include "motor.h"
#include "locator.h"

bool isIRBallFound = false;
word direction = 0;
int y, x = 100;
byte intencity = 0;
bool getData(word *direction, byte *intencity);

void setup(){
  pinMode(AIN1 ,OUTPUT); // Vector1 AD
  pinMode(AIN2 ,OUTPUT);

  pinMode(BIN1 ,OUTPUT); // Vector2 CB
  pinMode(BIN2 ,OUTPUT);

  pinMode(CIN1 ,OUTPUT);
  pinMode(CIN2 ,OUTPUT);

  pinMode(DIN1 ,OUTPUT);
  pinMode(DIN2 ,OUTPUT);

  pinMode(PWMA ,OUTPUT);
  pinMode(PWMB ,OUTPUT);
  pinMode(PWMC ,OUTPUT);
  pinMode(PWMD ,OUTPUT);
  pinMode(30 ,OUTPUT);
  digitalWrite(30, 1);
  
  Serial.begin(9600);

  Wire.begin();
  while (!IRLocatorInit());
}
void loop(){ 
  isIRBallFound = getData(&direction, &intencity);
  direction = 0;
  Serial.println(motor_drive_on_vector(direction));
  motor_drive_on_vector(direction);
}

int motor_drive_on_vector(int angle){
  angle += 45;
  if (angle > 360){
    angle = angle - 360;
  }
  y = tan(angle * 3.14 / 180) * x;
  if (angle > 180){
    x = -x;
    y = tan(angle * 3.14 / 180) * x;
  }
  Vector_x(x);
  Vector_y(y);
  return y;
}