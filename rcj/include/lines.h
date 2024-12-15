
#include <Arduino.h>
#include "const.h"



unsigned long button1LastPressedTime = 0;
unsigned long button2LastPressedTime = 0;
int counter = 0;  // Счетчик нажатий


// void setup(){
//   pinMode(s0, OUTPUT); 
//   pinMode(s1, OUTPUT); 
//   pinMode(s2, OUTPUT); 
//   pinMode(s3, OUTPUT); 
//   pinMode(button1Pin, INPUT_PULLUP);
//   pinMode(button2Pin, INPUT_PULLUP);
//   Serial.begin(9600);
// }


// void loop(){

//   //Loop through and read all 16 values
// //  for(int i = 0; i < 16; i ++){
// //
// //    Serial.print(readMux(i));
// //    Serial.print(", ");
// //    if (i == 15){
// //       Serial.println();
// //    }
// //  }
//   Serial.print(readMux(button()));
//   Serial.print("    : ");
//   Serial.println(button());
// }


int readMux(int channel){
  int controlPin[] = {s0, s1, s2, s3};
  int muxChannell[8][4]={
   {0,0,0,0}, //channel 0 1
   {0,1,0,0}, //channel 2 1
   {0,0,1,0}, //channel 4 1
   {0,1,1,0}, //channel 6 1

   {1,0,0,0}, //channel 1 2
   {1,1,0,0}, //channel 3 2
   {1,0,1,0}, //channel 5 2
   {1,1,1,0}, //channel 7 2

  //  {0,0,0,1}, //channel 8 3
  //  {0,1,0,1}, //channel 10 3
  //  {0,0,1,1}, //channel 12 3
  //  {0,1,1,1}, //channel 14 3

  //  {1,0,0,1}, //channel 9 4
  //  {1,1,0,1}, //channel 11 4
  //  {1,0,1,1}, //channel 13 4
  //  {1,1,1,1}  //channel 15 4
  };

  //loop through the 4 sig
  for(int i = 0; i < 4; i ++){
    digitalWrite(controlPin[i], muxChannell[channel][i]);
  }

  //read the value at the SIG pin
  int val = analogRead(SIG_pin);

  //return the value
  return val;
  delay(1000);
}

int get_line(){
  delay(500);
}
