#pragma once
#include <Wire.h>

/*
  Created by B. Blechschmidt, August 1, 2013.
  Released into the public domain.
*/

struct InfraredResult {
  byte Direction;
  byte Strength[6];
};

class InfraredSeeker {
  public:
  
    static void Initialize() {
      Wire.begin();
      Wire.beginTransmission(InfraredSeeker::Address);
      Wire.write(0x00);
      Wire.endTransmission();
      while (Wire.available() > 0) {
        int error  = Wire.read();
        Serial.println(error);
      } 
      Serial.println("Start IRSeeker ...");
    }

    static boolean Test() {
      Wire.beginTransmission(InfraredSeeker::Address);
      Wire.write(0x08);
      Wire.endTransmission();
      Wire.requestFrom(InfraredSeeker::Address, 16);
      char Manufacturer_Model[16];
      while (Wire.available() < 16);
      for (byte i = 0; i < 16; i++)  {
        Manufacturer_Model[i] = Wire.read();
      }
      while (Wire.available() > 0) {
        Wire.read();
      }
      return strncmp(Manufacturer_Model, "HiTechncNewIRDir", 16) == 0;
    }

    static void ReadACRaw(byte* buffer) {
      ReadValues(0x49, buffer);
    }

    static void ReadDCRaw(byte* buffer) {
      ReadValues(0x42, buffer);
    }

    static InfraredResult ReadAC() {
      byte buffer[6];
      ReadACRaw(buffer);
      return PopulateValues(buffer);
    }

    static InfraredResult ReadDC() {
      byte buffer[6];
      ReadDCRaw(buffer);
      return PopulateValues(buffer);
    }
    
    static int DirectionAngle(byte Direction) {
      return Direction * 30 - 150;
    }
    
  private:
    static InfraredResult PopulateValues(byte* buffer) {
      InfraredResult Data;
      Data.Direction = buffer[0];

      for (int i = 1; i <= 5; i++) {
        Data.Strength[i] = buffer[i];
      }
      return Data;
    }

    static void ReadValues(byte OffsetAddress, byte* buffer) {
      Wire.beginTransmission(InfraredSeeker::Address);
      Wire.write(OffsetAddress);
      Wire.endTransmission();
      Wire.requestFrom(InfraredSeeker::Address, 6);
      while (Wire.available() < 6);

      for (byte i = 0; i < 6; i++) {
        buffer[i] = Wire.read();
      }
      while (Wire.available() > 0) {
        Wire.read();
      }
    }

    static const int Address = 0x10 / 2; //Divide by two as 8bit-I2C address is provided
};
