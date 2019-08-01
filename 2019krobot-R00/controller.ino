//controller process

//stick -> button
//引数  :PSS系ID
//戻り値:-1,0,1
int stickButton(byte id) {
  int val = ps2x.Analog(id) - 128;
  if (abs(val) > value.ctlstickbtn) {
    return sgn(val) * 2 - 1;
  }
  return 0;
}

//---スティックの前処理
//　引数 : ps2x.Analog()と同じ (ex:PSS_LX)
//　返り値 : -256~254
int stickModVal(byte pssid) {
  int val = ps2x.Analog(pssid) - 128;
  if (abs(val) >= value.ctlsticknt) return val * 2;
  return 0;
}

//---十字キーをスティックのように扱う
//　返り値 : -255~255
int padStick_x() {
  if (ps2x.Button(PSB_PAD_RIGHT) || ps2x.Button(PSB_PAD_LEFT)) {
    return (ps2x.Analog(PSAB_PAD_RIGHT) - ps2x.Analog(PSAB_PAD_LEFT));
  } else {
    return 0;
  }
}
int padStick_y() {
  if (ps2x.Button(PSB_PAD_UP) || ps2x.Button(PSB_PAD_DOWN)) {
    return (ps2x.Analog(PSAB_PAD_UP) - ps2x.Analog(PSAB_PAD_DOWN));
  } else {
    return 0;
  }
}

int padStick_a() {
  if (ps2x.Button(PSB_GREEN) || ps2x.Button(PSB_RED)) {
    return (ps2x.Analog(PSAB_GREEN) - ps2x.Analog(PSAB_RED));
  } else {
    return 0;
  }
}

int padStick_b() {
  if (ps2x.Button(PSB_PINK) || ps2x.Button(PSB_BLUE)) {
    return (ps2x.Analog(PSAB_PINK) - ps2x.Analog(PSAB_BLUE));
  } else {
    return 0;
  }
}

int padStick_L() {
  if (ps2x.Button(PSB_L1) || ps2x.Button(PSB_L2)) {
    return (ps2x.Analog(PSAB_L1) - ps2x.Analog(PSAB_L2));
  } else {
    return 0;
  }
}

//ニュートラル検出
// false -> neutral
//MEMO: 未使用
/*
  bool stickNtL() {
  int stkLX = ps2x.Analog(PSS_LX) - 128;
  int stkLY = ps2x.Analog(PSS_LY) - 128;
  if (abs(stkLX) >= value.ctlsticknt) return true;
  if (abs(stkLY) >= value.ctlsticknt) return true;
  return false;
  }
  bool stickNtR() {
  int stkRX = ps2x.Analog(PSS_RX) - 128;
  int stkRY = ps2x.Analog(PSS_RY) - 128;
  if (abs(stkRX) >= value.ctlsticknt) return true;
  if (abs(stkRY) >= value.ctlsticknt) return true;
  return false;
  }
*/

