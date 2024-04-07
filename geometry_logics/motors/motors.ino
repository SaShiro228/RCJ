#include <Wire.h>
#include "motor.h"
#include "locator.h"

bool isIRBallFound = false;
word direction = 0;
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
  direction = ;
  Serial.println(motor_drive_on_vector(direction));
}
int motor_drive_on_vector(int angle){
  angle = angle + 45;
  if(angle > 360){
    angle = angle - 360;
  }
  return angle;
  //Vector_x(200);
  //Vector_y(200);
}

