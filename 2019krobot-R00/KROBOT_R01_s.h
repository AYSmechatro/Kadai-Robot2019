//%%% Kadai robot 2019 %%%
//header file for software

//last update : 19/07/06
//version : 00
//author : s.masamune@AYS

#ifndef KROBOT_R01_s_h
#define KROBOT_R01_s_h

#include "KROBOT_R01_h.h"

//---include libraries
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <EEPROM.h>
#include <PS2X_lib.h>
#include <Wire.h>
#include <PCA9685.h>
#include <LiquidCrystal.h>
#include <KanaLiquidCrystal.h>
#include <Servo.h>

#include "timer.h"
#include "uidata.h"
#include "accellimit.h"

KanaLiquidCrystal lcd(PIN_LCD_RS, PIN_LCD_RW, PIN_LCD_EN, PIN_LCD_D4, PIN_LCD_D5, PIN_LCD_D6, PIN_LCD_D7);

Servo servo0;
Servo servo1;
Servo servo2;

Timer controllertimer;
Timer buttontimer;
Timer uitimer;
Timer batterytimer;

PS2X ps2x;

//---button id
const int ID_SW1 = 0x01;
const int ID_SW2 = 0x02;
const int ID_SW3 = 0x04;
const int ID_SW4 = 0x08;
const int ID_SW5 = 0x10;
const int ID_SW_ALL = 0x1F;

//motor value range
const int MPWM_MAX = 255; //arduino pwm
const int MPWM2_MAX = 4095; //PCA9685 pwm

//---motor number
const int MOTOR_FTR = 0; //foot R
const int MOTOR_FTL = 1; //foot L
const int MOTOR_FSSW = 2; //fireworks setter tabletennis/golf switcher
const int MOTOR_FSL = 3; //fireworks setter lift
const int MOTOR_FSSTI =  4; //fireworks setter stirring
const int MOTOR_BCFAN = 5; //ball collect fan
const int MOTOR_BCFD = 6;  //ball collect door
const int MOTOR_FWTIL = 7;  //fireworks tilt
const int MOTOR_FWL = 8;  //fireworks lift
//const int MOTOR_ = 9;  //fireworks
//const int MOTOR_A4L = 10; //
//const int MOTOR_A4R = 11; //rotate
//const int MOTOR_A4R = 11; //rotate

//sensor number
//const int SENS_ =   0; //

//---functions
//text process
#define TF(x) ((x)==false?'F':'T')
#define HL(x) ((x)==LOW?'L':'H')
//number process
#define constloop(amt,low,high) ((amt)<(low)?(high):((amt)>(high)?(low):(amt)))
#define sgn(x) ((x)<0?0:1)  //signature

//データ保存用構造体+初期値定義
//@構造体の構造を変えたらeepromタブのADDRES_OFFSET,ROM_SUMCODEを変えること
struct romdata {
  byte footspeed[3];
  byte motorrange[12];
  byte sensorthreshold[13];
  byte ctlsticknt;
  byte ctlstickbtn;
  byte fanaccellimit;
  int batterylow[3];
  bool batteryalarm;
} value = {
  {100,  66,  30},
  { 100, 100, 100, 100,
    100, 100, 100, 100,
    100, 100, 100, 100
  },
  { 127, 127, 127, 127, 127, 127, 127,
    127, 127, 127, 127, 127, 127
  },
  10, 110, 4,
  {70, 110, 110},
  true
};

#endif  //end of KROBOT_H30_s_h

