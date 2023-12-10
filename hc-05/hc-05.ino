#include "SoftwareSerial.h"    // подключаем библиотеку
SoftwareSerial mySerial(2,3);  // указываем пины tx и rx

void setup() {
  pinMode(2,INPUT);
  pinMode(3,OUTPUT);
  
  Serial.begin(9600);         // включаем hardware-порт
  mySerial.begin(38400);  // включаем software-порт
  
  Serial.println("start setting");
}

void loop() {
    if (mySerial.available()) {
        char c = mySerial.read();  // читаем из software-порта
        Serial.print(c);                   // пишем в hardware-порт
    }
    if (Serial.available()) {
        char c = Serial.read();      // читаем из hardware-порта
        mySerial.write(c);            // пишем в software-порт
    }
}
