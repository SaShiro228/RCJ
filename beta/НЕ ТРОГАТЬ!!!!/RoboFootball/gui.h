#pragma once

#include <Arduino.h>

enum menuAction : uint8_t {PLAY, PLAYER_ROLE, SENSORS, TESTDRIVE};

void showLogo(); 
bool initGui();
uint8_t updateMenu();
void showObject(int object, uint8_t sizeText = 3);
void showMessage(const String& msg, uint8_t sizeText = 2);
void changePlayerRole() ;
void readAllSensors();
