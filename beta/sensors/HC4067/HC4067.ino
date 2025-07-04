//Mux control pins
#define s1 A2
#define s2 A4
#define s3 A6
#define s4 A8

//Mux in "SIG" pin
#define SIG_pin A0

void setup(){
  pinMode(s1, OUTPUT); 
  pinMode(s2, OUTPUT); 
  pinMode(s3, OUTPUT); 
  pinMode(s4, OUTPUT); 
  Serial.begin(9600);
}


void loop(){

  //Loop through and read all 16 values
  for(int i = 0; i < 8; i ++){

    Serial.print(readMux(i));
    Serial.print(", ");
    if (i == 7){
       Serial.println();
    }
  }
  //Serial.println(readMux(15));
}

int readMux(byte channel){
  int controlPin[4] = {s1, s2, s3, s4};
//  int muxChannell[16][4]={
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

  int muxChannell[8][4]={
    {0,0,0,0}, //channel 0 1
    //{1,0,0,0}, //channel 1 2
    //{0,1,0,0}, //channel 2 1
    {1,1,0,0}, //channel 3 2
    
    {0,0,1,0}, //channel 4 1
    //{1,0,1,0}, //channel 5 2
    //{0,1,1,0}, //channel 6 1
    {1,1,1,0}, //channel 7 2
    
    {0,0,0,1}, //channel 8 3
    //{1,0,0,1}, //channel 9 4
    //{0,1,0,1}, //channel 10 3
    {1,1,0,1}, //channel 11 4
    
    {0,0,1,1}, //channel 12 3
    //{1,0,1,1}, //channel 13 4
    //{0,1,1,1}, //channel 14 3
    {1,1,1,1}  //channel 15 4
  };

  for(int i = 0; i < 4; i ++){
    digitalWrite(controlPin[i], muxChannell[channel][i]);
  }
  int val = analogRead(SIG_pin);
  return val;
}
