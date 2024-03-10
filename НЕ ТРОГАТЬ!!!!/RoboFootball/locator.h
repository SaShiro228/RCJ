#pragma once

#include <Wire.h>

class IRLocator360 {
  public:

    static bool Initialize() {
      Wire.begin();
      Wire.beginTransmission(IRLocator360::Address);
      Wire.write(0x00);
      int error = Wire.endTransmission();
      return (error == 0) ? true : false;
    }

    static byte ReadHeading() {
      Wire.beginTransmission(IRLocator360::Address);
      Wire.write(0x04);
      Wire.endTransmission();
      Wire.requestFrom(IRLocator360::Address, 1);
      byte heading = Wire.read();
      return heading;
    }

    static byte ReadStrenght() {
      Wire.beginTransmission(IRLocator360::Address);
      Wire.write(0x05);
      Wire.endTransmission();
      Wire.requestFrom(IRLocator360::Address, 1);
      byte strenght = Wire.read();
      return strenght;
    }

    static const int Address = 0x0E;
    
};
