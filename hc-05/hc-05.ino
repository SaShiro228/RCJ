#include "SoftwareSerial.h"    
SoftwareSerial mySerial(2,3); 
//RCJ_Slave PSWD-2214 Addr-0022:05:426E VERSION:3.0-20170601
//RCJ_Master PSWD-2214 VERSION:3.0-20170601
int k =0;
void setup() {
  pinMode(2,INPUT);
  pinMode(3,OUTPUT);
  
  Serial.begin(9600);      
  mySerial.begin(38400);  
  
  Serial.println("start setting");
}

void loop() { 
      Serial.println(mySerial.read());           
}
