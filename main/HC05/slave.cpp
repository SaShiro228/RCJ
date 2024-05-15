#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(25, 27); // хз какие на ардуине, это RX TX esp32 devkit

void setup() {
  Serial.begin(115200);
  mySerial.begin(115200);

//славе
  mySerial.println("AT+ROLE0");
}


void commune(uint8_t x = 0, uint8_t y = 0, uint8_t cheto_esche = 0, uint8_t &rx_x, uint8_t &rx_y, uint8_t &rx_cheto_esche) {

  mySerial.print("AT+WRx0=");
  mySerial.print(x, DEC);
  mySerial.print(",");
  mySerial.print(y, DEC);
  mySerial.print(",");
  mySerial.println(cheto_esche, DEC);

  mySerial.println("AT+Rrx0=");

  String data = mySerial.readStringUntil('\n');
  String values[3];
  int i = 0;
  for (int j = 0; j < data.length(); j++) {
    if (data.charAt(j) == ',') {
      values[i] = data.substring(0, j);
      i++;
      data.remove(0, j + 1);
    }
  }

  rx_x = values[0].toInt();
  rx_y = values[1].toInt();
  rx_cheto_esche = values[2].toInt();

}

void loop() {

}