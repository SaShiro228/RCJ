#pragma once
#include <Arduino.h>
#include <Wire.h>
#include "const.h"

class IR_locator{
public:

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

bool getData(word *direction, byte *intencity) { 
  *intencity = readReg(INTENCITY_1200_REG);
  if (*intencity > 100){
     *direction = readReg(ANGLE_600_REG);
  } else{
    *direction = readReg(ANGLE_1200_REG);
  }
  *direction *= 5;
  return true;
}

};
// bool IRLocatorInit();
// bool isIRBallFound = false;
// word direction = 0;
// byte intencity = 0;
