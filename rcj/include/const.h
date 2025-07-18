#pragma once

//IR_locator control pins
#define LOCATOR_ADDR 0x0E
#define FIRM_REV_REG        0x00    // 0x11
#define MAN_CODE_REG        0x01    // 0x4D
#define ID_CODE_REG         0x02    // 0x4C
#define NOT_USED_REG        0x03
#define ANGLE_1200_REG      0x04    // 0xFF if no IR data have been detected, otherwise a value between 0 and 355
#define INTENCITY_1200_REG  0x05    // 0x00 if no IR data have been detected, otherwise a value between 0 and 255
#define ANGLE_600_REG       0x06
#define INTENCITY_600_REG   0x07


// Black board
// //motors control pins
// #define AIN1 11
// #define AIN2 9
// #define BIN1 29
// #define BIN2 31
// #define CIN1 13
// #define CIN2 5
// #define DIN1 27
// #define DIN2 25
// #define PWMA 6
// #define PWMB 44
// #define PWMC 7
// #define PWMD 46
// #define STB 30 //надо

// //lines control pins
// #define s0 A2
// #define s1 A0
// #define s2 A1
// #define s3 A3
// #define SIG_pin A12

// //Buttons control pins
// #define Button1Pin 14
// #define Button2Pin 15

// #define LINE_channel 8

// Green board
// motor pins
#define AIN1 16
#define AIN2 14
#define BIN1 33
#define BIN2 35
#define CIN1 12
#define CIN2 10
#define DIN1 37
#define DIN2 39
#define PWMA 2  //A
#define PWMB 8  //D
#define PWMC 6  //C
#define PWMD 4  //B
#define STB 30
#define Dribler 45

//lines control pins
#define s1 A2
#define s2 A4
#define s3 A6
#define SIG_pin A0

#define LINE_channel 8

//Buttons control pins
#define Button1Pin A1
#define Button2Pin A3
#define LED 32