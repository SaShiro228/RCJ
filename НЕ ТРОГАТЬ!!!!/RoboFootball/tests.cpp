// Tests should be placed here

#include "gui.h"
#include "common.h"
#include "motors.h"
#include "sensors.h"
#include "HTInfraredSeeker.h"
#include "locator.h"



void waitButton(int Button) {
  while (digitalRead(Button));
}

void testRandomDrive() {
  waitButton(BUTTONSET);
  while (true) {
    randomSeed(analogRead(A4));
    int randAngle = random(360);
    showObject(randAngle);
    while (true) {
      if (!digitalRead(BUTTONSET)) {
        delay(200);
        return;
      } else {
        if (!digitalRead(BUTTONPLUS)) {
          delay(200);
          break;
        }
      }
    } // while

    // movement!!!!!!
    delay(1000);
  } // while
}


void testLineSensors(int xspeed, int yspeed) {
  waitButton(BUTTONSET);
  int vy = xspeed;
  int vx = yspeed;
  byte dirx = ((vx > 0) ? RIGHT : LEFT);
  byte diry = ((vy > 0) ? FORWARD : BACK);
  uint16_t sens = 0;
  while (1) {
    sens = readSensors(dirx + diry);
    //    Serial.print(dirx + diry);
    //    Serial.print("  ");
    //    Serial.println(sens);
    if (sens & B11111111) {
      vy = -vy;
      diry = ((diry == BACK) ? FORWARD : BACK);
    }
    if (sens >> 8) {
      vx = -vx;
      dirx = ((dirx == RIGHT) ? LEFT : RIGHT);
    }
    drive(vx, vy);
    //delay(300);
  }
}

void testLineSensors() {
  waitButton(BUTTONSET);
  randomSeed(analogRead(A4));
  int vy = random(200) - 100;
  int vx = random(200) - 100;
  byte dirx = ((vx > 0) ? RIGHT : LEFT);
  byte diry = ((vy > 0) ? FORWARD : BACK);
  uint16_t sens = 0;
  while (1) {
    sens = readSensors(dirx + diry);
    if (sens & B11111111) {
      vy = -vy;
      diry = ((diry == BACK) ? FORWARD : BACK);
    }
    if (sens >> 8) {
      vx = -vx;
      dirx = ((dirx == RIGHT) ? LEFT : RIGHT);
    }
    drive(vx, vy);
  }
}

void testDriveBall() {
  waitButton(BUTTONSET);
  while (1) {
    int dir = 5 * IRLocator360::ReadHeading();
    byte st = IRLocator360::ReadStrenght();
    InfraredResult InfraredBall = InfraredSeeker::ReadAC();
    int sensors = InfraredBall.Direction;
    while ((dir > 30 && st) || !st) {
      digitalWrite(LEDRED, 1);
      digitalWrite(LEDBLUE, 0);
      drive(50, -50, 50, -50);
      int dir = 5 * IRLocator360::ReadHeading();
      byte st = IRLocator360::ReadStrenght();
    }
    digitalWrite(LEDRED, 0);
    digitalWrite(LEDBLUE, 1);
    drive(dir);
  }
}



void testReadIRSeekerSerial() {
  while (digitalRead(BUTTONSET)) {
    InfraredResult InfraredBall = InfraredSeeker::ReadAC();
    Serial.print(InfraredBall.Direction);
    Serial.print('\t');
    Serial.print(InfraredSeeker::DirectionAngle(InfraredBall.Direction));
    for ( int i = 1; i <= 5; ++i) {
      Serial.print('\t');
      Serial.print( InfraredBall.Strength[i]);
    }
    Serial.println();
    delay(300);
  }
}


void testDippingLineSensors(int xspeed, int yspeed) {
  waitButton(BUTTONSET);
  int vy = xspeed;
  int vx = yspeed;
  byte dirx = ((vx > 0) ? RIGHT : LEFT);
  byte diry = ((vy > 0) ? FORWARD : BACK);
  uint16_t sens = 0;
  bool flagx = 0;
  bool flagy = 0;
  while (1) {
    sens = readSensors(dirx + diry);
    if (sens & B11111111) {
      //vy = -vy;
      diry = ((diry == BACK) ? FORWARD : BACK);
      flagy = 1;
    }
    if (sens >> 8) {
      //vx = -vx;
      dirx = ((dirx == RIGHT) ? LEFT : RIGHT);
      flagx = 1;
    }
    if (flagx || flagy) {
      digitalWrite(LEDRED, 1);
      digitalWrite(LEDBLUE, 0);
      while (!readSensors(dirx + diry))drive(vx, vy);
      vx = ((flagx > 0) ? -vx : vx);
      vy = ((flagy > 0) ? -vy : vy);
      while (readSensors(ALL))drive(vx, vy);
      flagx = 0;
      flagy = 0;
      digitalWrite(LEDRED, 0);
      digitalWrite(LEDBLUE, 1);
    }
    drive(vx, vy);
  }
}

void keep_dir() {
  waitButton(BUTTONSET);
  while (1) {
    turn_start_angle();
  }
  delay(500);
}

void testLocatorSerial() {
  while (1) {
    int dir = IRLocator360::ReadHeading();
    byte st = IRLocator360::ReadStrenght();
    Serial.print("pos:  ");
    Serial.print(dir);
    Serial.print("  *  ");
    Serial.print("angle:  ");
    Serial.print(getAngle());
    Serial.print("  *  ");
    Serial.print("strength:  ");
    Serial.println(st);
    delay(500);
  }
}

void testLineSensorsSerial() {
  while (1) {
    uint16_t dat = readSensors(B1111);
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        Serial.print((dat >> (4 * i + j)) & 1);
        Serial.print('\t');
      }
      Serial.print('\n');
    }
    Serial.println(dat);
    Serial.print("***************************\n");
    delay(400);
  }
}

void testIsBall() {
  while (1) {
    Serial.print("Is Ball? : ");
    Serial.print((isBall() ? ("yes  ") : ("no  ")));
    Serial.print(digitalRead(BallDat));
    Serial.print('\n');
  }
}

void testGyroSerial() {
  while (1) {
    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
    float angle = euler.x();
    Serial.print("angle: ");
    Serial.print(angle);
    Serial.print('\n');
  }
}

void testMotors() {
  digitalWrite(LEDBLUE, 1);
  waitButton(BUTTONSET);
  while (1) {
    drive(80, 80, 80, 80);
    delay(3000);
    drive(-80, -80, -80, -80);
    delay(3000);
  }
}
void readLineSensorsReal(){
    Serial.print('\n');
  while (1) {
    for (int j = 0; j < 4; j++) {
      for (int i = 0; i < (Datnum / 4); i++) {
        PORTF &= B11110000;
        PORTF |= (i + (4 * j));
        Serial.print(analogRead(PinDat));
        Serial.print('\t');
      }
      Serial.print('\n');
    }
    Serial.print("****************************\n");
    delay(200);
  }
}
