#include "common.h"
#include "sensors.h"
#include "setup.h"
#include "motors.h"
#include "gui.h"
#include "tests.h"
#include "locator.h"
//#include "HTInfraredSeeker.h"
//#define GOALKEEPER
//#define TEST_DEVICES

void playForward();
void playGoalkeeper();
void driveFormLine();
void move2gate();
void turn2gate();
void captureBall();

int base_start_angle = 0;
PLAYER player = PLAYER::FORWARD;
void (*pFuncPlay)() =  playForward;

void setup() {
  Serial.begin(9600);
  Serial.println("RCJ-1");
  pinsSetup();

#ifdef TEST_DEVICES
  initPeripherals();

//  while (1) {
//    waitButton(BUTTONSET);
//    driveFormLine();
//    drive2ball();
//    captureBall();
//    //turn2gate();
//  }

  //readLineSensorsReal();
  //testLineSensorsSerial();
  //testGyroSerial();
  //keep_dir();
  //testMotors();
  //testLocatorSerial();
  //testIsBall();

#endif

  if (!initGui()) {
    // just alarm
    digitalWrite(LEDRED, HIGH);
  }
  if (!initPeripherals()) {
    // alarm and stop
    digitalWrite(LEDRED, HIGH);
    //alarm(LEDRED);
  }

  getSettingsEEPROM();
  pFuncPlay = (player == PLAYER::FORWARD) ? playForward : playGoalkeeper;

  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
  base_start_angle = euler.x();

  // Robot is ready to play
  digitalWrite(LEDBLUE, HIGH);
  delay(300);
  digitalWrite(LEDBLUE, LOW);
}

void loop() {
  uint8_t cmd = updateMenu();
  switch (cmd) {
    case PLAY :
      pFuncPlay();
      break;
    case PLAYER_ROLE :
      changePlayerRole();
      break;
    case SENSORS :
      readAllSensors();
      break;
    case TESTDRIVE:
      testDrive();
      break;
  }
}

void playForward() {
  showMessage("Forward ->", 1);
  while (1) {
    int code  = drive2ball();
    showObject(code);

    if (code & B1)driveFormLine();
    //if (readSensors(ALL))digitalWrite(LEDRED, 1);
    if (!(code & B0100))turn_start_angle();
    else {
      move2gate();
    }
  }
}

void playGoalkeeper() {
  showMessage("Goalkeeper ->", 1);
  while (1) {
    testMotors();

  }
}

void testDrive() {
  showMessage("TestDrive - >", 1);
  while (1) {

  }
}

void alarm(byte alarmPin) {
  while (1) {
    digitalWrite(alarmPin, !digitalRead(alarmPin));
    delay(200);
  }
}
void driveFormLine() {
  int angle = 0;
  byte count = 0;
  if (readSensors(FORWARD)) {
    count++;
  }
  if (readSensors(LEFT)) {
    angle += -90;
    count++;
  }
  if (readSensors(RIGHT)) {
    angle += 90;
    count++;
  }
  if (readSensors(BACK)) {
    angle += ((angle >= 0) ? 180 : -180);
    count++;
  }
  if (count) {
    drive((angle / count) - 180);
    delay(300);
    drive(0, 0, 0, 0);
  }
}
void move2gate() {
  // angle from cam
  turn2gate();
  float cam_angle = getCamAngle();
  delay(100);
  while (!readSensors(ALL))drive(0);
}
void turn2gate() {
  if (isBall()) {
    drive(180);
    delay(300);
    turn_start_angle();
    int angleGate = getCamAngle();
    int angleBall = getAngle();
    while (abs(angleBall - angleGate) > 7) {
      int speed_ = ((angleBall > angleGate) ? 50 : -50);
      drive(speed_, 0);
      angleGate = getCamAngle();
      angleBall = getAngle();
    }
    turn_angle(angleBall);
    while (!isBall())drive(0);
  }
  return;
}
void captureBall() {
  int  angle = getAngle();
  while (abs(angle) > 140) {
    int speed_ = (-angle / abs(angle)) * 70;
    drive(speed_, 0);
    angle = getAngle();
  }
  while (abs(getAngle()) >= 60)drive(0, -70);

  while ((abs(angle) > 5) && !readSensors(ALL)) {
    int speed_ = (angle > 0) ? 70 : -70;
    drive(speed_, 0);
    angle = getAngle();
  }

  drive(0);
  while (!isBall() && !readSensors(ALL));
  drive(0,0,0,0);
  return;
}
