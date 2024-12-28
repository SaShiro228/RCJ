#include <Wire.h>
#include "motor.h"
#include "locator.h"
//#include "lines.h"
//#include "cam.h"

bool isIRBallFound = false;
word direction = 0;
byte intencity = 0;
bool getData(word *direction, byte *intencity);

void setup(){
  // pinMode(s0, OUTPUT); 
  // pinMode(s1, OUTPUT); 
  // pinMode(s2, OUTPUT); 
  // pinMode(s3, OUTPUT); 
  // pinMode(button1Pin, INPUT_PULLUP);
  // pinMode(button2Pin, INPUT_PULLUP);
    
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
  isIRBallFound = _getData(&direction, &intencity);
  // Serial.print(intencity);
  // Serial.print(" ");
  // Serial.println(direction);
  motor_drive_on_vector(100, direction);
   //Vector_x(150);
   //Vector_y(150);
}

