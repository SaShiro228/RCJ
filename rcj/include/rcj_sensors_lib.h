#pragma once
#include <Arduino.h>
#include <Wire.h>
#include "const.h"
#include "MPU6050.h"

class IR_locator{
private:
  bool isIRBallFound = false;
  int direction = 0;
  byte intencity = 0;
  int getData(word *direction, byte *intencity);

  static byte readReg(byte reg_addr) {
    byte data = 0;

    Wire.beginTransmission(LOCATOR_ADDR);  
    Wire.write(reg_addr);                    // set register addr for reading
    Wire.endTransmission(false);             // false to not release the line
    Wire.requestFrom(LOCATOR_ADDR, 1);       // request 1 byte from mentioned previously register
	
    // read response from IR locator
    while (Wire.available()) {	      
	  	data = Wire.read();
	  }
   return data;
  }
public:

  bool IRLocatorInit() {
    byte firm_rev, man_code, id_code;

    firm_rev = readReg(FIRM_REV_REG);
    man_code = readReg(MAN_CODE_REG);
    id_code = readReg(ID_CODE_REG);

    if (id_code != 0x4C) {
      Serial.print("IR Locator cannot be initialized: expected ID 0x4C, received ID ");
      Serial.println(id_code, HEX);
      return false;
    }

    Serial.println("IR Locator is ready to use:");
    Serial.print("\tFirmware Revision: ");
    Serial.println(firm_rev, HEX);
    Serial.print("\tManufacturer Code: ");
    Serial.println(man_code, HEX);
    Serial.print("\tSensor ID Code: ");
    Serial.println(id_code, HEX);

    return true;
  }

  int get_Derection_Auto() { 
    intencity = readReg(INTENCITY_1200_REG);
    if (intencity > 100){
      direction = readReg(ANGLE_600_REG);
    } else{
      direction = readReg(ANGLE_1200_REG);
    }
    direction *= 5;
    return direction;
  }

  byte get_Intencity_1200(){
    intencity = readReg(INTENCITY_1200_REG);
    return intencity;
  }

  byte get_Intencity_600(){
    intencity = readReg(INTENCITY_600_REG);
    return intencity;
  }

  int get_Derection_1200(){
    intencity = readReg(ANGLE_1200_REG);
    return intencity;
  }

  int get_Derection_600(){
    intencity = readReg(ANGLE_1200_REG);
    return intencity;
  }

};

class line_sensors{
private:
  int controlPin[4] = {s0, s1, s2, s3};
  int muxChannell[LINE_channel][4] = {
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
public:
  int data[LINE_channel];
  int read_line_channel(int channel){
    //loop through the 4 sig
    for(int i = 0; i < 4; i ++){
      digitalWrite(controlPin[i], muxChannell[channel][i]);
    }
    //read the value at the SIG pin
    int val = analogRead(SIG_pin);
    return val;
  } 

  void readline(){
    for (int i = 0; i < LINE_channel; i++)
    {
      data[i] = read_line_channel(i);
    }    
  }
};

// class cam{
// public:

// };

class gyro{
private:
  MPU6050 mpu;
public:
  bool mpuInit(){
    mpu.initialize();
    // состояние соединения
    Serial.println(mpu.testConnection() ? "MPU6050 OK" : "MPU6050 FAIL");
    return true;
  }

};
