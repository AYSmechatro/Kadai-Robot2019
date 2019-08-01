//%%% Kadai robot 2019 %%%
//header file for hardware

//last update : 19/06/07
//version : 00
//author : s.masamune@AYS

#ifndef KROBOT_R01_h_h
#define KROBOT_R01_h_h

//LCD
const int PIN_LCD_RS = 48;
const int PIN_LCD_RW = 43;
const int PIN_LCD_EN = 42;
const int PIN_LCD_D4 = 41;
const int PIN_LCD_D5 = 40;
const int PIN_LCD_D6 = 39;
const int PIN_LCD_D7 = 38;

//controller(PS2)
const int PIN_CTL_CLK = 34;
const int PIN_CTL_CMD = 35;
const int PIN_CTL_ATT = 37;
const int PIN_CTL_DAT = 36;

//user switch
const int PIN_SW1 = 53;
const int PIN_SW2 = 52;
const int PIN_SW3 = 51;
const int PIN_SW4 = 50;
const int PIN_SW5 = 49;

//servo
const int PIN_SERVO0 = 44;
const int PIN_SERVO1 = 45;
const int PIN_SERVO2 = 46;

//battery sens pin
const int PIN_BAT_COM = A13;
const int PIN_BAT_M0 = A14;
const int PIN_BAT_M1 = A15;
const int PINS_BAT[3] = {PIN_BAT_COM, PIN_BAT_M0, PIN_BAT_M1};

//buzzer
const int PIN_BZ = 47;

//DC motor pins define
const byte PINS_MOTOR_DIR[12] = {
  22, 23, 24, 25,
  26, 27, 28, 29,
  30, 31, 32, 33
};
const byte PINS_MOTOR_PWM[12] = {
  2, 3, 4, 5,
  6, 7, 8, 9,
  10, 11, 12, 13
};

#endif  //end of KROBOT_R01_h_h
