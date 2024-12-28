#include <Arduino.h>
#include <EEPROM.h>
#include "setup.h"
#include "common.h"
//#include "HTInfraredSeeker.h"
#include "locator.h"
#include "sensors.h"
#include "gui.h"

void pinsSetup() {
  //объявление пинов
  for (byte pin : DatLine) {
    pinMode(pin, OUTPUT);
  }
  pinMode(BUZZ, OUTPUT);
  pinMode(LEDRED, OUTPUT);
  pinMode(LEDBLUE, OUTPUT);
  pinMode(LEDYELLOW, OUTPUT);
  pinMode(Voltage, INPUT);
  pinMode(BallDat, INPUT);

  pinMode(BUTTONMINUS, INPUT_PULLUP);
  pinMode(BUTTONSET, INPUT_PULLUP);
  pinMode(BUTTONPLUS, INPUT_PULLUP);

  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);

  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);

  pinMode(CIN1, OUTPUT);
  pinMode(CIN2, OUTPUT);

  pinMode(DIN1, OUTPUT);
  pinMode(DIN2, OUTPUT);

  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(PWMC, OUTPUT);
  pinMode(PWMD, OUTPUT);

  pinMode(MotorsSTBY, OUTPUT);
  digitalWrite(MotorsSTBY, true);//включение драйверов
}

void setupADC() {

}

void setupTimers() {

}

// init differente devices
bool initPeripherals() {
  bool isSuccess = true;
  
  // speed up the ADC
  setupADC();
  // increase the frequency of the motors
  setupTimers();

  // Init IRSeeker
  //InfraredSeeker::Initialize();
  
  // Init Bluetooth
  // BT.begin(9600);

  // Init IRLocator 360
  if (!IRLocator360::Initialize()) {
    Serial.println(F("IR Locator 360 is not found"));
    showMessage("IR error!");
    isSuccess = false;
    return isSuccess;
  }
  
  // Init gyro
  if (!bno.begin())  {
    Serial.println(F("Gyro error!"));
    showMessage("Gyro error!");
    delay(1000);
    isSuccess = false;
  }


  // Init Camera(openMV)
  delay(1000);
  Wire.beginTransmission(CAMERA_ADDRESS);
  int error = Wire.endTransmission();
  if (error != 0) {
    Serial.println(F("Camera error!"));
    showMessage("Cam error!");
    delay(1000);
  }
 
  //delay(1000);
  return isSuccess;
}

void getSettingsEEPROM() {
  PLAYER temp;
  // get player role : FORWARD or GOALKEEPER
  EEPROM.get(ADDRESS_PLAYER, temp);
  if (temp != PLAYER::FORWARD && temp != PLAYER::GOALKEEPER) { // check wrong value
    player = PLAYER::FORWARD;
    EEPROM.put(ADDRESS_PLAYER, player);
  } else {
    player = temp;
  }
}
