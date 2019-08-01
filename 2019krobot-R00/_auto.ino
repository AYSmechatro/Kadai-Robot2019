////auto process
//
////自動動作
////description: 開始時は線を無視し、未検出を挟んでから検出する。
//// state変数とswitch文を使い状態遷移機械(ステートマシン)を形成している。
//
////自立動作開始時(と手動時)にtrue,reset用
//boolean flag_autoreset = false;
//
///*******************************************************/
//
//void robotSemiAuto_A1L() {
//  static int state = 0;
//
//  if (flag_autoreset) {
//    state = 0;
//    motorWrite(MOTOR_A1L, 0);
//  }
//
//  switch (state) {
//    case 0: //stop
//      if (!ps2x.Button(PSB_L1) && !ps2x.Button(PSB_L2)) {
//        if (stickButton(PSS_RY) == -1) {
//          motorWrite(MOTOR_A1L, -MPWM_MAX);
//          state++;
//        }
//        if (stickButton(PSS_RY) == 1) {
//          motorWrite(MOTOR_A1L, MPWM_MAX);
//          state++;
//        }
//      }
//      break;
//
//    case 1:
//      if (!sensorRead(SENS_A1L)) state++;
//      break;
//
//    case 2:
//      if (sensorRead(SENS_A1L)) {
//        motorWrite(MOTOR_A1L, 0);
//        state = 0;  //return stop
//      }
//      break;
//  }
//}
//
//void robotSemiAuto_A2L() {
//  static int state = 0;
//
//  if (flag_autoreset) {
//    state = 0;
//    motorWrite(MOTOR_A2L, 0);
//  }
//
//  switch (state) {
//    case 0: //stop
//      if (ps2x.Button(PSB_L1)) {
//        if (stickButton(PSS_RY) == -1) {
//          motorWrite(MOTOR_A2L, -MPWM_MAX);
//          state++;
//        }
//        if (stickButton(PSS_RY) == 1) {
//          motorWrite(MOTOR_A2L, MPWM_MAX);
//          state++;
//        }
//      }
//      break;
//
//    case 1:
//      if (!sensorRead(SENS_A2L)) state++;
//      break;
//
//    case 2:
//      if (sensorRead(SENS_A2L)) {
//        motorWrite(MOTOR_A2L, 0);
//        state = 0;  //return stop
//      }
//      break;
//  }
//}
//
//void robotSemiAuto_A2LD() {
//  static int state = 0;
//  static int direct = 0;  //移動中は目的位置、移動後は現在位置を示す 1:格納 -1:展開 0:other
//  static unsigned long timectlstart;
//
//  if (flag_autoreset) {
//    state = 0;
//    direct = 0;
//    motorWrite(MOTOR_A2LD, 0);
//  }
//
//  switch (state) {
//    case 0: //stop
//      if (ps2x.ButtonPressed(PSB_GREEN) && direct != 1) {
//        motorWrite(MOTOR_A2LD, -MPWM_MAX);
//        direct = 1;
//        state++;
//      }
//      if (ps2x.ButtonPressed(PSB_RED) && direct != -1) {
//        motorWrite(MOTOR_A2LD, MPWM_MAX);
//        direct = -1;
//        state++;
//      }
//      break;
//
//    case 1:
//      if (!sensorRead(SENS_A2LD)) state++;
//      break;
//
//    case 2:
//      if (sensorRead(SENS_A2LD)) {
//        if (direct == -1) {
//          //増し締め
//          motorWrite(MOTOR_A2LD, MPWM_MAX / 2);
//          timectlstart = millis();
//          state++;
//        } else {
//          motorWrite(MOTOR_A2LD, 0);
//          state = 0;  //return stop
//        }
//      }
//      break;
//
//    case 3: //wait 400ms
//      if (millis() - timectlstart >= 400) {
//        motorWrite(MOTOR_A2LD, -MPWM_MAX / 2);
//        timectlstart = millis();
//        state++;  //return stop
//      }
//      break;
//
//    case 4: //増締め解除 350ms
//      if (millis() - timectlstart >= 350) {
//        motorWrite(MOTOR_A2LD, 0);
//        state++;  //return stop
//      }
//  }
//}
//
//void robotSemiAuto_A2LP() {
//  static int state = 0;
//  static int direct = 0;  //移動中は目的位置、移動後は現在位置を示す 1:press -1:release 0:other
//
//  if (flag_autoreset) {
//    state = 0;
//    direct = 0;
//    motorWrite(MOTOR_A2LP, 0);
//  }
//
//  switch (state) {
//    case 0: //stop
//      if (ps2x.ButtonPressed(PSB_PAD_RIGHT) && direct != -1) {
//        //move to initial position
//        motorWrite(MOTOR_A2LP, -MPWM_MAX);
//        direct = -1;
//        state++;
//      }
//      if (ps2x.ButtonPressed(PSB_PAD_LEFT)) { //&&direct==1を付け加えるべきか?それだったらcaseで初期位置に移動を独立させるか
//        //press -> release
//        motorWrite(MOTOR_A2LP, MPWM_MAX);
//        direct = 1;
//        state++;
//      }
//      break;
//
//    case 1:
//      if (!sensorRead(SENS_A2LP)) state++;
//      break;
//
//    case 2:
//      if (sensorRead(SENS_A2LP)) {
//        if (direct == 1) {
//          //return to initial position
//          motorWrite(MOTOR_A2LP, -MPWM_MAX);
//          direct = -1;
//          state = 1;
//        } else {
//          motorWrite(MOTOR_A2LP, 0);
//          state = 0;  //return stop
//        }
//      }
//      break;
//  }
//}
//
//void robotSemiAuto_A2FP() {
//  static int state = 0;
//
//  if (flag_autoreset || ps2x.Button(PSB_PAD_UP)) {
//    state = 0;
//    motorWrite(MOTOR_A2FP, 0);
//  }
//
//  switch (state) {
//    case 0: //stop
//      if (ps2x.ButtonPressed(PSB_PAD_DOWN)) {
//        motorWrite(MOTOR_A2FP, MPWM_MAX);
//        state++;
//      }
//      break;
//
//    case 1:
//      if (!sensorRead(SENS_A2FP)) state++;
//      break;
//
//    case 2:
//      if (sensorRead(SENS_A2FP)) {
//        motorWrite(MOTOR_A2FP, 0);
//        state = 0;  //return stop
//      }
//      break;
//  }
//}
//
//void robotSemiAuto_A3L() {
//  static int state = 0;
//
//  if (flag_autoreset) {
//    state = 0;
//    motorWrite(MOTOR_A3L, 0);
//  }
//
//  switch (state) {
//    case 0: //stop
//      if (ps2x.Button(PSB_L2)) {
//        if (stickButton(PSS_RY) == -1) {
//          motorWrite(MOTOR_A3L, -MPWM_MAX);
//          state++;
//        }
//        if (stickButton(PSS_RY) == 1) {
//          motorWrite(MOTOR_A3L, MPWM_MAX);
//          state++;
//        }
//      }
//      break;
//
//    case 1:
//      if (!sensorRead(SENS_A3L)) state++;
//      break;
//
//    case 2:
//      if (sensorRead(SENS_A3L)) {
//        motorWrite(MOTOR_A3L, 0);
//        state = 0;  //return stop
//      }
//      break;
//  }
//}
//
///*******************************************************/
//
////全自動五重の塔建築
//// 高さ調整→階押出→高さ調整→屋根押出　のループ
//// 高さを調整+インクリーザ押し出しながらペッツを戻す
//// 自動建築後A2L下げる
//// A3Lを建築途中にあげる
//void robotAutoBuild() {
//  static int state = 0;
//  static int state2 = 0;
//  static int state_a3l = 0;
//  static int count = 0; //count done floor(s)
//  const int COUNT_MAX = 5;  //max floors
//  static unsigned long timectlstart;
//
//  if (flag_autoreset) {
//    state = 0;
//    state2 = 0;
//    state_a3l = 0;
//  }
//
//#ifdef DEBUG_SW4
//  Serial.print(loopcount);
//  Serial.print("\t");
//  Serial.print(state);
//  Serial.print("\t");
//  Serial.print(state2);
//  Serial.print("\t");
//  Serial.println(count);
//#endif
//
//  switch (state) {
//    case 0: //stop
//      if (ps2x.ButtonPressed(PSB_PINK)) {
//        count = 0;
//        state2 = 0;
//        state_a3l = 1;
//        state++;
//      }
//      break;
//
//    case 1: //lift up start ~
//      motorWrite(MOTOR_A2L, -MPWM_MAX);
//      if (!sensorRead(SENS_A2L)) state++;
//      break;
//
//    case 2: // -> end & floor press start
//      if (sensorRead(SENS_A2L)) {
//        motorWrite(MOTOR_A2L , 0);
//        state++;
//      }
//      break;
//
//    case 3: //floor press ~
//      motorWrite(MOTOR_A2FP, MPWM_MAX);
//      if (!sensorRead(SENS_A2FP)) state++;
//      break;
//
//    case 4: // -> end & lift up start
//      if (sensorRead(SENS_A2FP)) {
//        motorWrite(MOTOR_A2FP, 0);
//        state++;
//      }
//      break;
//
//    case 5: //lift up ~
//      motorWrite(MOTOR_A2L , -MPWM_MAX);
//      if (!sensorRead(SENS_A2L)) state++;
//      break;
//
//    case 6: // -> end
//      if (sensorRead(SENS_A2L)) {
//        motorWrite(MOTOR_A2L , 0);
//        state++;
//      }
//      break;
//
//    case 7:
//      if (state2 == 0) {
//        state2 = 1; //loof press start
//        state++;
//      }
//      break;
//
//    case 8: //end or continue
//      count++;
//      state++;
//
//    case 9:
//      if (count < COUNT_MAX) {
//        //continue
//        if (state2 == 0) {
//          state2 = 2; //loof release start
//          state = 1;
//        }
//      } else {
//        //all done -> move forward
//        if (state2 == 0) {
//          timectlstart = millis();
//          state++;
//        }
//      }
//      break;
//
//    case 10:
//      motorWrite(MOTOR_FL1, MPWM_MAX / 2);
//      motorWrite(MOTOR_FR1, -MPWM_MAX / 2);
//      motorWrite(MOTOR_FL2, MPWM_MAX / 2);
//      motorWrite(MOTOR_FR2, -MPWM_MAX / 2);
//      if (millis() - timectlstart >= 300) {
//        state2 = 3; //loof store start
//      }
//      if (millis() - timectlstart >= 700) {
//        motorWrite(MOTOR_FL1, 0);
//        motorWrite(MOTOR_FR1, 0);
//        motorWrite(MOTOR_FL2, 0);
//        motorWrite(MOTOR_FR2, 0);
//        timectlstart = millis();
//        state++;
//      }
//      break;
//
//    case 11:
//      motorWrite(MOTOR_A2L , MPWM_MAX);
//      if (millis() - timectlstart >= 1500) {
//        motorWrite(MOTOR_A2L , 0);
//        state = 0;  //return stop
//      }
//      break;
//  }
//
//  switch (state2) {
//    case 0: //stop
//      break;
//
//    case 1: //press
//      motorWrite(MOTOR_A2LP, MPWM_MAX);
//      state2 = 10;
//      break;
//
//    case 2: //release
//      motorWrite(MOTOR_A2LP, -MPWM_MAX);
//      state2 = 10;
//      break;
//
//    case 3: //store
//      motorWrite(MOTOR_A2LP, MPWM_MAX / 2);
//      state2 = 10;
//      break;
//
//    case 10:
//      if (!sensorRead(SENS_A2LP)) state2++;
//      break;
//
//    case 11:
//      if (sensorRead(SENS_A2LP)) {
//        motorWrite(MOTOR_A2LP, 0);
//        state2 = 0;
//      }
//      break;
//  }
//
//  switch (state_a3l) {
//    case 0: //stop
//      break;
//
//    case 1: //up start
//      motorWrite(MOTOR_A3L, -MPWM_MAX / 2);
//      state_a3l = 10;
//      break;
//
//    case 10:
//      if (!sensorRead(SENS_A3L)) state_a3l++;
//      break;
//
//    case 11:
//      if (sensorRead(SENS_A3L)) {
//        motorWrite(MOTOR_A3L, 0);
//        state_a3l = 0;  //return stop
//      }
//      break;
//  }
//}

