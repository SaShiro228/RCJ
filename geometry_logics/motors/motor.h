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


void Vector_x(int power){
  if (power > 0)
  {
    digitalWrite(AIN2, 1);
    digitalWrite(DIN1, 1);
    digitalWrite(AIN1, 0);
    digitalWrite(DIN2, 0);
  }
  else if (power < 0)
  {
    digitalWrite(AIN1, 1);
    digitalWrite(DIN2, 1);
    digitalWrite(AIN2, 0);
    digitalWrite(DIN1, 0);
    power *= -1;
  }
  else
  {
    digitalWrite(AIN1, 0);
    digitalWrite(DIN2, 0);
    digitalWrite(AIN2, 0);
    digitalWrite(DIN1, 0);
  }
  analogWrite(PWMA, power);
  analogWrite(PWMD, power);
}
void Vector_y(int power){
  if (power > 0)
  {
    digitalWrite(CIN2, 1);
    digitalWrite(BIN1, 1);
    digitalWrite(CIN1, 0);
    digitalWrite(BIN2, 0);
  }
  else if (power < 0)
  {
    digitalWrite(CIN1, 1);
    digitalWrite(BIN2, 1);
    digitalWrite(CIN2, 0);
    digitalWrite(BIN1, 0);
    power *= -1;
  }
  else
  {
    digitalWrite(CIN1, 0);
    digitalWrite(BIN2, 0);
    digitalWrite(CIN2, 0);
    digitalWrite(BIN1, 0);
  }
  analogWrite(PWMB, power);
  analogWrite(PWMC, power);
}