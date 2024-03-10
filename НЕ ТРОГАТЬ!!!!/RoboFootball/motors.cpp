#include "common.h"
#include "sensors.h"
#include "motors.h"
#include "locator.h"

int baseSpeed = 100;

//const float MotorsAngle = 90;
//const float MotorsAngleSIN = sin(MotorsAngle*0.017453);//для произвольного угла


void drive(int left1, int right1, int left2, int right2) {
  //ограничиваем скорости
  left1 = constrain(left1, -255, 255);
  right1 = constrain(right1, -255, 255);
  left2 = constrain(left2, -255, 255);
  right2 = constrain(right2, -255, 255);
  //устанавливаем направления вращения моторов
  if (left1 >= 0) {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
  } else {
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
  }

  if (right1 >= 0) {
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
  } else {
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
  }

  if (left2 >= 0) {
    digitalWrite(CIN1, LOW);
    digitalWrite(CIN2, HIGH);
  } else {
    digitalWrite(CIN1, HIGH);
    digitalWrite(CIN2, LOW);
  }

  if (right2 >= 0) {
    digitalWrite(DIN1, LOW);
    digitalWrite(DIN2, HIGH);
  } else {
    digitalWrite(DIN1, HIGH);
    digitalWrite(DIN2, LOW);
  }
  // посылаем шим-сигнал
  analogWrite(PWMA, abs(left1));
  analogWrite(PWMB, abs(right1));
  analogWrite(PWMC, abs(left2));
  analogWrite(PWMD, abs(right2));

}

void drive(float angle) {
  float k1 = sin((45 - angle) * 0.017453);
  float k2 = sin((45 + angle) * 0.017453);
  //  float k1 = sin(((MotorsAngle/2)-angle)*0.017453)/MotorsAngleSIN;
  //  float k2 = sin(((MotorsAngle/2)+angle)*0.017453)/MotorsAngleSIN;
  drive(baseSpeed * k2, baseSpeed * k1, baseSpeed * k1, baseSpeed * k2);
}

void drive(int vx, int vy) {
  float v = sqrt(vx * vx + vy * vy);
  float k1 = ((vy - vx) / (v * 1.4142136));
  float k2 = ((vy + vx) / (v * 1.4142136));
  drive(v * k2, v * k1, v * k1, v * k2);
}

void turn_angle(float angle) {
  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
  float start_angle = euler.x();
  float target = (int(start_angle + angle) + 360) % 360;
  int speed_ = (angle > 0) ? 50 : -50;
  drive(speed_, -speed_, speed_, -speed_);
  while (1) {
    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
    drive(speed_, -speed_, speed_, -speed_);
    float angle = euler.x();
    int now_angle = int(-target + angle + 360) % 360;
    if (now_angle > 180)now_angle = now_angle - 360;
    if ((speed_ > 0) && (now_angle > 0) || ((speed_ < 0) && (now_angle < 0)))speed_ *= -1;
    if (abs(now_angle) <= 6) {
      drive(0, 0, 0, 0);
      return;
    }
  }
}

void turn_start_angle() {
  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
  float start_angle = euler.x();
  float delta_angle = ((int(base_start_angle - start_angle) + 360) % 360);
  if (delta_angle > 180)delta_angle = delta_angle - 360;
  if (abs(delta_angle) > 5)turn_angle(delta_angle);
  return;
}

byte drive2ball() {
  byte st = IRLocator360::ReadStrenght();
  int angle = getAngle();
  long dat = 0;
  byte code = 0;
  while (st && !isBall() && (st < 140) && !dat) {
    dat = 0;
    // while (st && (st<140)){
    float delta = (angle / abs(angle)) * st * 0.1;
    drive(angle + delta);
    //drive(angle);
    angle = getAngle();
    st = IRLocator360::ReadStrenght();
    //dat = readSensors(ALL);
  }
  drive(0, 0, 0, 0);
  code = (bool(st) << 3) | (!isBall() << 2) | (bool(st < 120) << 1) | (!(bool(dat)));
  code = ~code & B00001111;
  return code;
}
