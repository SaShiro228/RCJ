#include "SoftwareSerial.h"    
SoftwareSerial mySerial(2,3); 
//slave: 22:5:426E
//master:
void setup() {
  pinMode(2,INPUT);
  pinMode(3,OUTPUT);
  
  Serial.begin(9600);      
  mySerial.begin(38400);  
  
  Serial.println("start setting");
}

void loop() {
  Serial.println(2);
    if (mySerial.available()) {
        char c = mySerial.read();  
        Serial.print(c);                  
    }
    if (Serial.available()) {
        char c = Serial.read();     
        mySerial.write(c);            
    }
}
