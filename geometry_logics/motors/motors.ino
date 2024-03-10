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
int k = 1;

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
  Serial.print(Button());
  Serial.print(" // ");
  Serial.println(Vector_go(Button()));
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

void right(){
  digitalWrite(AIN1, 1);
  digitalWrite(CIN1, 1);
  digitalWrite(DIN1, 1);
  digitalWrite(BIN1, 1);
  analogWrite(PWMA, speed_x);
  analogWrite(PWMB, speed_x);
  analogWrite(PWMC, speed_x);
  analogWrite(PWMD, speed_x);
}

void left(){
  digitalWrite(AIN2, 1);
  digitalWrite(CIN2, 1);
  digitalWrite(DIN2, 1);
  digitalWrite(BIN2, 1);
  analogWrite(PWMA, speed_x);
  analogWrite(PWMB, speed_x);
  analogWrite(PWMC, speed_x);
  analogWrite(PWMD, speed_x);
}
