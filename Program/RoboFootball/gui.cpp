// using Adafruit_SSD1306 library for OLED

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <EEPROM.h>
#include "gui.h"
#include "common.h"
#include "sensors.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET  -1
#define SCREEN_ADDRESS 0x3C // See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

uint8_t startMenuX = 0;
uint8_t startMenuY = 25;
uint8_t activeItem = 0;
const uint8_t menuSize = 4;

const String Menu[] {
  "Play",
  "Player_R",
  "Sensors",
  "Test Drive"
};

const char *LOGO = "RCJ-1";

void runningLeds();
float getLevelVoltage();

void showLogo() {
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(25, 25);
  display.print(LOGO);
  display.display();
  //for (int i = 0; i < 3; ++i) {
  //  runningLeds();
  //}
}

bool initGui() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    return false;
  }
  showLogo();
  return true;
}


void drawItem(uint8_t item) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(5, 0);
  display.print(getLevelVoltage());
  display.print('V');

  display.setCursor(65, 0);
  display.print(player == PLAYER::FORWARD ? "FORWARD" : "GOALKEEPER");
  display.setCursor((SCREEN_WIDTH - Menu[item].length() * 12) / 2, startMenuY);
  display.setTextSize(1);
  display.println(Menu[item]);
  display.display();
}


uint8_t updateMenu() {
  byte cur = activeItem;
  bool isSelected = false;
  drawItem(activeItem);
  while (!isSelected) {
    if (!digitalRead(BUTTONPLUS)) {
      activeItem = (activeItem < menuSize - 1) ? activeItem + 1 : 0;
      drawItem(activeItem);
      delay(200);
    } else if (!digitalRead(BUTTONMINUS)) {
      activeItem = (activeItem > 0) ? activeItem - 1 : menuSize - 1;
      drawItem(activeItem);
      delay(200);
    } else if (!digitalRead(BUTTONSET)) {
      delay(200);
      isSelected = true;
    }
  }
  return activeItem;
}

void runningLeds() {
  static uint8_t LEDS[] {LEDRED, LEDBLUE, LEDYELLOW};
  for (auto led : LEDS) {
    digitalWrite(led, HIGH);
    delay(300);
    digitalWrite(led, LOW);
  }
}

void showObject(int object, uint8_t sizeText) {
  display.clearDisplay();
  display.setTextSize(sizeText);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(40, 25);
  display.println(object);
  display.display();
}

void showMessage(const String& msg, uint8_t sizeText) {
  display.clearDisplay();
  display.setTextSize(sizeText);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 25);
  display.println(msg);
  display.display();
}

void changePlayerRole() {
  uint8_t active = static_cast<uint8_t> (player);

  auto setColorItem = [&active](uint8_t item) {
    if (item == active) {
      display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
    } else {
      display.setTextColor(SSD1306_WHITE);
    }
  };

  auto drawMenu = [&setColorItem]() {
    display.clearDisplay();
    display.setTextSize(2);
    setColorItem(0);
    display.setCursor(5, 10);
    display.print("Forward");
    setColorItem(1);
    display.setCursor(5, 35);
    display.print("Goalkeeper");
    display.display();
  };

  drawMenu();
  bool isSelected = false;
  while (!isSelected) {
    if (!digitalRead(BUTTONPLUS)) {
      active = (active == 0) ? 1 : 0;
      drawMenu();
      delay(200);
    } else if (!digitalRead(BUTTONMINUS)) {
      active = (active == 0) ? 1 : 0;
      drawMenu();
      delay(200);
    } else if (!digitalRead(BUTTONSET)) {
      delay(300);
      isSelected = true;
    }
  }

  player = static_cast<PLAYER>(active);
  pFuncPlay = (player == PLAYER::FORWARD) ? playForward : playGoalkeeper;
  EEPROM.put(ADDRESS_PLAYER, player);
}



void readAllSensors() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  while (digitalRead(BUTTONSET)) {
    uint16_t sens = readSensors(ALL);
    display.clearDisplay();
    uint16_t MASK = 0x0001;
    for (int i = 0; i < 4; ++i) {
      // FORWARD sensors
      if (sens & MASK) {
        display.fillCircle(64, 4 + i * 7, 3, SSD1306_WHITE);
      } else {
        display.drawCircle(64, 4 + i * 7, 3, SSD1306_WHITE);
      }
      MASK <<= 1;
    }

    for (int i = 0; i < 4; ++i) {
      // BACK sensors
      if (sens & MASK) {
        display.fillCircle(64, 59 - i * 7, 3, SSD1306_WHITE);
      } else {
        display.drawCircle(64, 59 - i * 7, 3, SSD1306_WHITE);
      }
      MASK <<= 1;
    }
    
    for (int i = 0; i < 4; ++i) {
      // RIGHT sensors
      if (sens & MASK) {
        display.fillCircle(110 - i * 10, 32, 3, SSD1306_WHITE);
      } else {
        display.drawCircle(110 - i * 10, 32, 3, SSD1306_WHITE);
      }
      MASK <<= 1;
    }

    for (int i = 0; i < 4; ++i) {
      // LEFT sensors
      if (sens & MASK) {
        display.fillCircle(20 + i * 10, 32, 3, SSD1306_WHITE);
      } else {
        display.drawCircle(20 + i * 10, 32, 3, SSD1306_WHITE);
      }
      MASK <<= 1;
    }
   

    display.display();
    
    delay(10);
  }
  delay(500);
}



float getLevelVoltage() {
  int V = analogRead(Voltage);
  return  k_VIN * V;
}
