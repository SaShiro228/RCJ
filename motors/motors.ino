const int button1Pin = 14;
const int button2Pin = 15;
const unsigned long debounceDelay = 200;
unsigned long button1LastPressedTime = 0;
unsigned long button2LastPressedTime = 0;
int counter = 0;  // Счетчик нажатий


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

float speed_x = 50;
float speed_y = 50; 
float speed = 0;
int k = 1;
float angel = 90;
float angel_mv = 0;
float angel_rad = 0;

void setup(){
  pinMode(AIN1 ,OUTPUT); // Vector1 AD
  pinMode(AIN2 ,OUTPUT);
  pinMode(BIN1 ,OUTPUT); // Vector2 CB
  pinMode(BIN2 ,OUTPUT);
  pinMode(CIN1 ,OUTPUT);
  pinMode(CIN2 ,OUTPUT);
  pinMode(DIN1 ,OUTPUT);
  pinMode(DIN2 ,OUTPUT);
  pinMode(PWMA ,OUTPUT);
  pinMode(PWMB ,OUTPUT);
  pinMode(PWMC ,OUTPUT);
  pinMode(PWMD ,OUTPUT);
  pinMode(30 ,OUTPUT);
  digitalWrite(30, 1);
  
  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);
  Serial.begin(9600);
}
void loop(){ 
  motor_go(50);
}
void motor_go(int speed_x){
  angel_mv = angel + 45;
  if(angel_mv > 360){
    angel_mv = angel_mv - 360;
  }
  angel_rad = angel * 3.14 /180;
  if ((angel_mv <= 90) or (angel_mv >= 270)){
    speed_y = tan(angel_rad) * speed_x;
    motorY(speed_y);
    if(angel_mv < 90){
      motorX(speed_x);
    }else if(angel_mv > 270){
      motorX(speed_x);
    }
  }else{
    //speed_x = speed_x * -1;
    speed_y = tan(angel_rad) * speed_x;
    motorY(speed_y);
    if(angel_mv <= 1180){
      motorX(speed_x);
    }else if(angel_mv >= 180){
      motorX(speed_x);
    }
    
  }
}
void motorY(float speed){
  if (speed > 0){
    analogWrite(PWMB, speed);
    analogWrite(PWMC, speed);
    digitalWrite(BIN2, 1);
    digitalWrite(CIN1, 1);
    digitalWrite(BIN1, 0);
    digitalWrite(CIN2, 0);
  }else if(speed < 0){
    speed = speed * -1;
    analogWrite(PWMB, speed);
    analogWrite(PWMC, speed);
    digitalWrite(BIN1, 1);
    digitalWrite(CIN2, 1);
    digitalWrite(BIN2, 0);
    digitalWrite(CIN1, 0);
  }
}
void motorX(float speed){
  if (speed > 0){
    analogWrite(PWMA, speed);
    analogWrite(PWMD, speed);
    digitalWrite(AIN1, 1);
    digitalWrite(DIN1, 1);
    digitalWrite(AIN2, 0);
    digitalWrite(DIN2, 0);
  }else if(speed < 0){
    speed = speed * -1;
    analogWrite(PWMA, speed);
    analogWrite(PWMD, speed);
    digitalWrite(AIN2, 1);
    digitalWrite(DIN2, 1);
    digitalWrite(AIN1, 0);
    digitalWrite(DIN1, 0);
  }
}

void go(){
  digitalWrite(AIN2, 1);
  digitalWrite(CIN2, 1);
  digitalWrite(DIN1, 1);
  digitalWrite(BIN1, 1);
  analogWrite(PWMA, speed_x * k);
  analogWrite(PWMB, speed_x * k);
  analogWrite(PWMC, speed_x * k);
  analogWrite(PWMD, speed_x * k);
}


