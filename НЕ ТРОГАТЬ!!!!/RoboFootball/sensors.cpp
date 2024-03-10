#include "sensors.h"
#include "common.h"
#include "locator.h"
#include <Wire.h>

// Gyro
Adafruit_BNO055 bno = Adafruit_BNO055(-1, 0x29);

// uint16_t readSensors(byte dir);
// возращает 4 байта:
//1-ые 4 бита - передние датчики
//2-ые 4 бита - задние датчики
//3-ие 4 бита - правые датчики
//4-ые 4 бита - левые датчики

uint16_t readSensors(byte dir) {
  uint16_t dat = 0;
  for (int j = 0; j < 4; j++) {
    if ((dir >> j) & B00000001) {
      for (int i = 0; i < (Datnum / 4); i++) {
        PORTF &= B11110000;//логическим 'и' обнуляем все на пинах A0, A1, A2, A3
        PORTF |= (i + (4 * j)); // на пины мутиплексера посылаем номер считываемого датчика
        dat |= (((analogRead(PinDat) > Threshold) ? 0 : 1) << (4 * j + i));
      }
    }
  }
  return dat;
}

int getAngle() {
  int dir = 360 - (5 * IRLocator360::ReadHeading() );
  if (dir > 180)dir = dir - 360;
  dir = constrain(dir, -180, 180);
  return dir;
}

bool isBall() {
  return digitalRead(BallDat);
}

int getCamAngle() {
  static int const CHAR_BUF = 10;
  int angle = 0;
  int32_t temp = 0;
  char buff[CHAR_BUF] = {0};

  Wire.requestFrom(0x12, 2);
  if (Wire.available() == 2) { // got length?
    temp = Wire.read() | (Wire.read() << 8);
    delay(1); // Give some setup time...
    Wire.requestFrom(0x12, temp);
    if (Wire.available() == temp) { // got full message?
      temp = 0;
      while (Wire.available()) buff[temp++] = Wire.read();

    } else {
      while (Wire.available()) Wire.read(); // Toss garbage bytes.
    }
  } else {
    while (Wire.available()) Wire.read(); // Toss garbage bytes.
  }
  angle = atoi(buff);
  return angle;
}
