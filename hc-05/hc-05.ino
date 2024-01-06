#include "SoftwareSerial.h"    
SoftwareSerial mySerial(2,3); 
//<<<<<<< HEAD
//slave: 22:5:426E
//master:
//=======
//RCJ_Slave PSWD-2214 Addr-0022:05:426E VERSION:3.0-20170601
//RCJ_Master PSWD-2214 VERSION:3.0-20170601
//>>>>>>> dd20c43a5ead8d96e895b8d9d5e7f591783027ac
void setup() {
  pinMode(2,INPUT);
  pinMode(3,OUTPUT);
  
  Serial.begin(9600);      
  mySerial.begin(9600);  
  
  Serial.println("start setting");
}
long i = 0;
void loop() { 
  mySerial.write(i); 
  //i = mySerial.read(); 
  Serial.println(i);  
  i++;     
}
