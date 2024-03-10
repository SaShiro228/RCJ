#include <Wire.h>

#define LOCATOR_ADDR 0x0E

#define FIRM_REV_REG        0x00    // 0x11
#define MAN_CODE_REG        0x01    // 0x4D
#define ID_CODE_REG         0x02    // 0x4C
#define NOT_USED_REG        0x03
#define ANGLE_1200_REG      0x04    // 0xFF if no IR data have been detected, otherwise a value between 0 and 355
#define INTENCITY_1200_REG  0x05    // 0x00 if no IR data have been detected, otherwise a value between 0 and 255
#define ANGLE_600_REG       0x06
#define INTENCITY_600_REG   0x07

#define AIN1 11
#define AIN2 9
#define BIN1 29
#define BIN2 31
#define CIN1 13
#define CIN2 5
#define DIN1 27
#define DIN2 25
#define PWMA 6
#define PWMB 44
#define PWMC 7
#define PWMD 46

int sped = 30;
int k = 2;

bool IRLocatorInit();
bool getData(word *direction, byte *intencity);

void setup() {
  Serial.begin(9600);
  Wire.begin();
  while (!IRLocatorInit());
  pinMode(AIN1 ,OUTPUT);
  pinMode(AIN2 ,OUTPUT);
  pinMode(BIN1 ,OUTPUT);
  pinMode(BIN2  ,OUTPUT);
  pinMode(CIN1 ,OUTPUT);
  pinMode(CIN2 ,OUTPUT);
  pinMode(DIN1 ,OUTPUT);
  pinMode(DIN2 ,OUTPUT);
  pinMode(PWMA ,OUTPUT);
  pinMode(PWMB ,OUTPUT);
  pinMode(PWMC ,OUTPUT);
  pinMode(PWMD ,OUTPUT);
  pinMode(30, OUTPUT);
}

void loop(){
//  motor_ball();
  digitalWrite(30, 1);
  go(1);
}
void motor_ball() {
  bool isIRBallFound = false;
  word direction = 0;
  byte intencity = 0;

  isIRBallFound = getData(&direction, &intencity);
  if (intencity >= 70){
    if (direction <= 290 && direction >= 180){      
      left(1);
    }else if (direction >= 70 && direction <= 180){      
      right(1);
    }else{
      go(2);
    }
  }else{
    if (direction <= 130 && direction >= 0){   
      right(2);
    }else if (direction >= 200 && direction <= 360){
      left(2);
    }else{
      go(3);
    }
  }
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

void go(int k){
  digitalWrite(AIN2, 1);
  digitalWrite(CIN2, 1);
  digitalWrite(DIN1, 1);
  digitalWrite(BIN1, 1);
  analogWrite(PWMA, sped * k);
  analogWrite(PWMB, sped * k);
  analogWrite(PWMC, sped * k);
  analogWrite(PWMD, sped * k);
  digitalWrite(AIN1, 0);
  digitalWrite(CIN1, 0);
  digitalWrite(DIN2, 0);
  digitalWrite(BIN2, 0);
}

void right(int k){
  digitalWrite(AIN1, 1);
  digitalWrite(CIN1, 1);
  digitalWrite(DIN1, 1);
  digitalWrite(BIN1, 1);
  analogWrite(PWMA, sped * k);
  analogWrite(PWMB, sped * k);
  analogWrite(PWMC, sped * k);
  analogWrite(PWMD, sped * k);
  digitalWrite(AIN2, 0);
  digitalWrite(CIN2, 0);
  digitalWrite(DIN2, 0);
  digitalWrite(BIN2, 0);
}

void left(int k){
  digitalWrite(AIN2, 1);
  digitalWrite(CIN2, 1);
  digitalWrite(DIN2, 1);
  digitalWrite(BIN2, 1);
  analogWrite(PWMA, sped * k);
  analogWrite(PWMB, sped * k);
  analogWrite(PWMC, sped * k);
  analogWrite(PWMD, sped * k);
  digitalWrite(AIN1, 0);
  digitalWrite(CIN1, 0);
  digitalWrite(DIN1, 0);
  digitalWrite(BIN1, 0);
}
