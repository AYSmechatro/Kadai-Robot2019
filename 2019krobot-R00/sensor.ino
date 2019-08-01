//sensor process

//---get battery voltage[V(float)]
float batteryRead(byte num) {
  float volt = (float)analogRead(PINS_BAT[num]) / 1023.0 * 21.5;
  //if (pin == PIN_BAT_COM) volt += 0.7;  //MEMO: 入力ダイオード死亡
  return volt;
}

//---電圧低下検出
//どれか1つでも基準値を下回ったらtrue
bool batteryLowCheck() {
  for (int i = 0; i < 3; i++) {
    if (batteryRead(i) <= value.batterylow[i]) {
      return true;
    }
  }
  return false;
}

//---センサ読み込み
//検出時true
bool sensorRead(byte num) {
  bool state;
  state = (sensorAnRead(num) < value.sensorthreshold[num]);
  //  if (num == SENS_A2LP) state = !state;
  return state;
}

int sensorAnRead(byte num) {
  return analogRead(num) / 4;
}

