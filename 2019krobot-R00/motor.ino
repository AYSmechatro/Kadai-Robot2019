//motor process

/*************************************************/

//モーターに出力
void motorWrite() {
  for (int i = 0; i < 12; i++) {
    int power = constrain(map(motorpower[i], 0, MPWM_MAX, 0, map(value.motorrange[i], 0, 100, 0, MPWM_MAX)), -MPWM_MAX, MPWM_MAX);
    digitalWrite(PINS_MOTOR_DIR[i], !sgn(motorpower[i]));
    analogWrite(PINS_MOTOR_PWM[i], abs(motorpower[i]));
  }
  //    pwm.setPWM(PINS_MOTOR_PWM[mnum], 0, constrain(abs(power), 0, MPWM_MAX));
}

/******************************************************************/

//servo attach(on)
void servoAttach() {
  //if (servo0.attached()) return;
  servo0.attach(PIN_SERVO0);
  servo1.attach(PIN_SERVO1);
  servo2.attach(PIN_SERVO2);
}

//servo detach(off)
void servoDetach() {
  //if (!servo0.attached()) return;
  servo0.detach();
  servo1.detach();
  servo2.detach();
}
