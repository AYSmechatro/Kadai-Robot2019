//2019課題ロボット リモコン型ロボット用プログラム

//team name : AYS(仮)
//robot name : ひかりまい(仮)

//version : sample
//date    : 2019/07/20
//author  : 佐藤　正宗
//        : (他に編集者がいればここに書く)

//board type : Arduino Mega
//CPU type : ATmega2560

//information
//pwm9,10はtone関数と被る
//pwm4,13はduty高めになる
//pwm13はLED_BUILTINと同じなので起動時動作する恐れあり

#define DEBUG_ROM   //eeprom
#define DEBUG_LOOP   //main loop 監視
//#define DEBUG_SW3   //
//#define DEBUG_SW4   //auto
//#define DEBUG_SW5   //fixme

#include "KROBOT_R01_h.h"
#include "KROBOT_R01_s.h"

byte contError = 255;
//bool contPressure = true;
bool contVib1 = false;
byte contVib2 = 0;
unsigned int ctlerrcount = 0;

//robot status
bool status_lock = true;

int motorpower[12];

void setup() {
  delay(100);

  //入出力設定
  pinMode(PIN_SW1, INPUT_PULLUP);
  pinMode(PIN_SW2, INPUT_PULLUP);
  pinMode(PIN_SW3, INPUT_PULLUP);
  pinMode(PIN_SW4, INPUT_PULLUP);
  pinMode(PIN_SW5, INPUT_PULLUP);
  for (int i = 0; i <= 11; i++) {
    pinMode(PINS_MOTOR_DIR[i], OUTPUT);
    pinMode(PINS_MOTOR_PWM[i], OUTPUT);
  }
  pinMode(PIN_BZ, OUTPUT);

  //serial port
  Serial.begin(115200); //[bps]

  //LCD
  lcd.begin(16, 2);
  lcd.kanaOn(); //カタカナ有効化
  uicharset();

  //PCA9685モジュールPWM
  //  pwm.begin();
  //  pwm.setPWMFreq(300);  //[Hz]

  //controller
  contError = ps2x.config_gamepad(PIN_CTL_CLK, PIN_CTL_CMD, PIN_CTL_ATT, PIN_CTL_DAT, true, true);

  //
  Serial.println("ｶﾀﾞｲﾛﾎﾞｯﾄ AYS");
  Serial.println("Program start.");
  tone(PIN_BZ, 1000, 100);

  //config data process
  checkRom();

  controllertimer.set(16);
  buttontimer.set(16);
  uitimer.set(500);
}

void loop() {
  if (buttontimer.check()) {
    buttonFunc();
    if (uitimer.check() || buttonRead_rep(ID_SW_ALL)) {
      uirefresh();
    }
  }

  if (controllertimer.check()) {
    ps2x.read_gamepad(contVib1, contVib2);
    //  ctlanalogok = ps2x.read_gamepad(contVib1, contVib2);
    //  if (!ctlanalogok) ctlerrcount++;
    contVib1 = false; contVib2 = 0;
    //モーター出力値初期化
    for (int i = 0; i < 12; i++) {
      motorpower[i] = 0;
    }
    robot();
    motorWrite();
  }


}
