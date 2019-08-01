//robot process

/*********************************************/

void robot() {
  //lock / unlock (start)
  if (ps2x.ButtonPressed(PSB_START)) status_lock = !status_lock;
  if (ps2x.Button(PSB_SELECT)) status_lock = true;

  if (!status_lock) {
    servoAttach();
    //foot function
    robotFoot();
    //arm function
    //    if (ps2x.Button(PSB_R2)) {
    //auto on

    //
    motorpower[2] = padStick_L();
    motorpower[3] = padStick_a();
    motorpower[4] = padStick_x();
    motorpower[5] = padStick_y();
    //motorpower[6]=fan1.accellimit(button*256);
    motorpower[6] = padStick_L();
    motorpower[7] = padStick_a();
    motorpower[8] = padStick_x();
    motorpower[9] = padStick_y();
    motorpower[10] = padStick_b();

    servo0.write(ps2x.Analog(PSS_LX));
    servo1.write(ps2x.Analog(PSS_LX));
    servo2.write(ps2x.Analog(PSS_LY));
  } else {
    servoDetach();
  }

  //exclusive commands -> SELECT + a

  //  //battery low alarm on/off (select + blue)
  //  if (ps2x.Button(PSB_SELECT) && ps2x.ButtonPressed(PSB_BLUE)) {
  //    value.batteryalarm = !value.batteryalarm;
  //  }

  //battery low alarm
  if (value.batteryalarm) {
    if (batteryLowCheck()) {
      contVib2 = 255;
    }
  }
}

/************************************************************/

void robotFoot() {
  int spdval;
  //---モーターの出力値に変換
  //---Park convert
  int motorval_l, motorval_r;
  const float MROT = M_PI_4;  // PI/4[rad]
  motorval_l = -stickModVal(PSS_LY) + stickModVal(PSS_LX);
  motorval_r = -stickModVal(PSS_LY) - stickModVal(PSS_LX);

  //簡易ガンマ補正(2次関数)
  //  motorval_l = constrain(motorval_l, -256, 255);
  //  motorval_l = ((long)motorval_l * (long)abs(motorval_l)) >> 8;
  //  motorval_r = constrain(motorval_r, -256, 255);
  //  motorval_r = ((long)motorval_r * (long)abs(motorval_r)) >> 8;

  //expand full scale
  //  motorval_l *= M_SQRT2;
  //  motorval_r *= M_SQRT2;

  //speed change(R2 -> turbo)(X -> middle)
  if (ps2x.Button(PSB_R2)) {
    //turbo
    spdval = map(value.footspeed[1], 0, 100, 0, MPWM_MAX);
  } else if (ps2x.Button(PSB_CROSS)) {
    //middle
    spdval = map(value.footspeed[0], 0, 100, 0, MPWM_MAX);
  } else {
    //low
    spdval = map(value.footspeed[2], 0, 100, 0, MPWM_MAX);
  }

  motorval_l = map(motorval_l, 0, 255, 0, spdval);
  motorval_r = map(motorval_r, 0, 255, 0, spdval);

  //---各モーターへ出力
  //右モーターが+-反転する
  motorpower[MOTOR_FTL] = motorval_l;
  motorpower[MOTOR_FTR] = -motorval_r;
}

