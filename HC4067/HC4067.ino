//Mux control pins
#define s0 A2
#define s1 A0
#define s2 A1
#define s3 A3

//Mux in "SIG" pin
#define SIG_pin A12

const int button1Pin = 14;
const int button2Pin = 15;
const unsigned long debounceDelay = 200;
unsigned long button1LastPressedTime = 0;
unsigned long button2LastPressedTime = 0;
int counter = 0;  // Счетчик нажатий

void setup(){
  pinMode(s0, OUTPUT); 
  pinMode(s1, OUTPUT); 
  pinMode(s2, OUTPUT); 
  pinMode(s3, OUTPUT); 
  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);
  Serial.begin(9600);
}


void loop(){

  //Loop through and read all 16 values
//  for(int i = 0; i < 16; i ++){
//
//    Serial.print(readMux(i));
//    Serial.print(", ");
//    if (i == 15){
//       Serial.println();
//    }
//  }
  Serial.print(readMux(button()));
  Serial.print("    : ");
  Serial.println(button());
}

int button(){
  unsigned long currentTime = millis();
  int button1State = digitalRead(button1Pin); 
  int button2State = digitalRead(button2Pin);
  if (button1State == LOW && currentTime - button1LastPressedTime > debounceDelay) {
    button1LastPressedTime = currentTime;
    counter++;
  }

  if (button2State == LOW && currentTime - button2LastPressedTime > debounceDelay) {
    button2LastPressedTime = currentTime;
    counter--;
  }
  return(counter);
}

int readMux(int channel){
  int controlPin[] = {s0, s1, s2, s3};

//  int muxChannel[16][4]={
//    {0,0,0,0}, //channel 0 1
//    {1,0,0,0}, //channel 1 2
//    {0,1,0,0}, //channel 2 1
//    {1,1,0,0}, //channel 3 2
//    
//    {0,0,1,0}, //channel 4 1
//    {1,0,1,0}, //channel 5 2
//    {0,1,1,0}, //channel 6 1
//    {1,1,1,0}, //channel 7 2
//    
//    {0,0,0,1}, //channel 8 3
//    {1,0,0,1}, //channel 9 4
//    {0,1,0,1}, //channel 10 3
//    {1,1,0,1}, //channel 11 4
//    
//    {0,0,1,1}, //channel 12 3
//    {1,0,1,1}, //channel 13 4
//    {0,1,1,1}, //channel 14 3
//    {1,1,1,1}  //channel 15 4
//  };

  int muxChannell[16][4]={
   {0,0,0,0}, //channel 0 1
   {0,1,0,0}, //channel 2 1
   {0,0,1,0}, //channel 4 1
   {0,1,1,0}, //channel 6 1

   {1,0,0,0}, //channel 1 2
   {1,1,0,0}, //channel 3 2
   {1,0,1,0}, //channel 5 2
   {1,1,1,0}, //channel 7 2

   {0,0,0,1}, //channel 8 3
   {0,1,0,1}, //channel 10 3
   {0,0,1,1}, //channel 12 3
   {0,1,1,1}, //channel 14 3

   {1,0,0,1}, //channel 9 4
   {1,1,0,1}, //channel 11 4
   {1,0,1,1}, //channel 13 4
   {1,1,1,1}  //channel 15 4
  };

  //loop through the 4 sig
  for(int i = 0; i < 4; i ++){
    digitalWrite(controlPin[i], muxChannell[channel][i]);
  }

  //read the value at the SIG pin
  int val = analogRead(SIG_pin);

  //return the value
  return val;
  delay(1000);
}
