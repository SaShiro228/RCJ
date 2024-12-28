#include <Wire.h>
#include "locator.h"

#define LOCATOR_ADDR 0x0E

#define FIRM_REV_REG        0x00    // 0x11
#define MAN_CODE_REG        0x01    // 0x4D
#define ID_CODE_REG         0x02    // 0x4C
#define NOT_USED_REG        0x03
#define ANGLE_1200_REG      0x04    // 0xFF if no IR data have been detected, otherwise a value between 0 and 355
#define INTENCITY_1200_REG  0x05    // 0x00 if no IR data have been detected, otherwise a value between 0 and 255
#define ANGLE_600_REG       0x06
#define INTENCITY_600_REG   0x07

bool IRLocatorInit();
bool isIRBallFound = false;
word direction = 0;
byte intencity = 0;
bool getData(word *direction, byte *intencity);

void setup() {
  Serial.begin(9600);
  Wire.begin();
  while (!IRLocatorInit());
}

void loop(){
  isIRBallFound = getData(&direction, &intencity);
  Serial.print(direction);
  Serial.print(" // ");
  Serial.println(intencity);
}

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
  *direction = readReg(ANGLE_1200_REG);
  if (*direction != 0xFF) {
    *intencity = readReg(INTENCITY_1200_REG);
  } else {
    // Try to read from another channel
    *direction = readReg(ANGLE_600_REG);
    if (*direction == 0xFF) {
      return false;
    }    
    
    *intencity = readReg(INTENCITY_600_REG);
  }

  *direction *= 5;
  return true;
}