//time parameter
//T1:start T2:freq [flame]
const int KEYREP_T1 = 25;
const int KEYREP_T2 = 4;

byte btnstate = B00000;
byte btnstate_p = B00000;
byte btnstate_prep = B00000;

unsigned long btnprstime[5];

int uimenu_top = 0;
int uimenu_topcursor = 0;
int uimenu_sub = 0;
int uimenu_nowlayer = 0;

//**************************************************

void uicharset() {
  byte lcdcharlock[8] = {
    B00000,
    B00000,
    B01110,
    B01010,
    B11111,
    B11011,
    B11111,
    B00000
  };
  byte lcdcharbattery[8] = {
    B00000,
    B00000,
    B01110,
    B11111,
    B10001,
    B10001,
    B11111,
    B00000
  };
  lcd.createChar(1, lcdcharlock);
  lcd.createChar(2, lcdcharbattery);
}

void uirefresh() {
  if (uimenu_nowlayer == 0) {
    if (buttonRead_rep(ID_SW3) && strcmp(UIMENUTOP[uimenu_top + 1], "END")) {
      uimenu_top++;
      if (uimenu_topcursor < 1)uimenu_topcursor++;
    }
    if (buttonRead_rep(ID_SW2) && uimenu_top > 0) {
      uimenu_top--;
      if (uimenu_topcursor > 0)uimenu_topcursor--;
    }
    if (buttonRead_p(ID_SW1)) {
      uimenu_nowlayer = 1;
      uimenu_sub = 0;
    }
  } else {
    if (buttonRead_rep(ID_SW3) && strcmp(UIMENUINDEX[uimenu_top][uimenu_sub + 1], "END")) {
      uimenu_sub++;
    }
    if (buttonRead_rep(ID_SW2) && uimenu_sub > 0) {
      uimenu_sub--;
    }
    if (buttonRead_p(ID_SW1)) {
      writeRom();
      uimenu_nowlayer = 0;
    }
  }

  lcd.clear();

  if (uimenu_nowlayer == 0) {
    lcd.setCursor(1, 0); lcd.print(UIMENUTOP[uimenu_top - uimenu_topcursor]);
    lcd.setCursor(1, 1); lcd.print(UIMENUTOP[uimenu_top - uimenu_topcursor + 1]);
    lcd.setCursor(0, uimenu_topcursor); lcd.print(">");
  } else {
    lcd.setCursor(0, 0); lcd.print(UIMENUINDEX[uimenu_top][uimenu_sub]);
    uisubmenu();
  }

  if (status_lock == true) {
    lcd.setCursor(14, 0); lcd.write((byte)1);
  }
  if (batteryLowCheck() == true) {
    lcd.setCursor(15, 0); lcd.write((byte)2);
  }
}

void uisubmenu() {
  char out[32]; //tempolary

  switch (uimenu_top) {
    case 0:
      if (buttonRead_p(ID_SW4)) {
        status_lock = true;
      }
      if (buttonRead_p(ID_SW5)) {
        status_lock = false;
      }
      lcd.setCursor(1, 1);
      if (status_lock) {
        lcd.print("   ﾛｯｸ  >");
      } else {
        lcd.print("< ｱﾝﾛｯｸ  ");
      }
      break;

    case 1:
      switch (uimenu_sub) {
        case 0:
        case 1:
        case 2:
          if (buttonRead_rep(ID_SW4)) {
            value.batterylow[uimenu_sub]++;
          }
          if (buttonRead_rep(ID_SW5)) {
            value.batterylow[uimenu_sub]--;
          }
          value.batterylow[uimenu_sub] = constrain(value.batterylow[uimenu_sub], 50, 250);
          lcd.setCursor(1, 1);
          dtostrf(batteryRead(uimenu_sub), 4, 1, out);
          lcd.print(out); lcd.print("V");
          lcd.setCursor(6, 1);
          dtostrf((float)value.batterylow[uimenu_sub] / 10.0, 4, 1, out);
          lcd.print("["); lcd.print(out); lcd.print("V]");
          break;

        case 3:
          if (buttonRead_p(ID_SW5)) {
            value.batteryalarm = true;
          }
          if (buttonRead_p(ID_SW4)) {
            value.batteryalarm = false;
          }
          lcd.setCursor(1, 1);
          if (value.batteryalarm) {
            lcd.print("< ON   ");
          } else {
            lcd.print("  OFF >");
          }
          break;
      }
      break;

    case 2:
      switch (uimenu_sub) {
        case 0:
          lcd.setCursor(1, 1);
          //sprintf(out, "E:%2x T:%2x P:%c", contError, ps2x.readType(), TF(contPressure));
          sprintf(out, "E:%2x T:%2x", contError, ps2x.readType());
          //sprintf(out, "E:%2x e:%2d T:%2x", contError, ctlerrcount, ps2x.readType());
          lcd.print(out);
          break;

        case 1:
          lcdPrintButton();
          break;

        case 2:
          lcd.setCursor(1, 1);
          sprintf(out, "%3d,%3d,%3d,%3d", ps2x.Analog(PSS_LX), ps2x.Analog(PSS_LY), ps2x.Analog(PSS_RX), ps2x.Analog(PSS_RY));
          lcd.print(out);
          break;

        case 3:
          buttonToValue(&value.ctlsticknt, 0, 127);
          lcd.setCursor(1, 1);
          sprintf(out, "%3d", value.ctlsticknt);
          lcd.print(out);
          break;

        case 4:
          buttonToValue(&value.ctlstickbtn, 0, 127);
          lcd.setCursor(1, 1);
          sprintf(out, "%3d", value.ctlstickbtn);
          lcd.print(out);
          break;

        case 5:
          break;
      }
      break;

    case 3: //UIMENUSENS
      buttonToValue(&value.sensorthreshold[uimenu_sub], 0, 255);
      lcd.setCursor(1, 1);
      sprintf(out, "%3d (%3d:%c)", value.sensorthreshold[uimenu_sub], sensorAnRead(uimenu_sub), TF(sensorRead(uimenu_sub)));
      lcd.print(out);
      break;

    case 4: //UIMENUPARAM
      buttonToValue(&value.footspeed[uimenu_sub], 0, 100);
      lcd.setCursor(1, 1);
      sprintf(out, "%3d%c", value.footspeed[uimenu_sub], '%');
      lcd.print(out);
      break;

    case 5: //UIMENUMOTOR
      buttonToValue(&value.motorrange[uimenu_sub], 0, 100);
      lcd.setCursor(1, 1);
      sprintf(out, "%3d%c", value.motorrange[uimenu_sub], '%');
      lcd.print(out);
      break;
  }
}

void buttonToValue(byte *val, byte vmin, byte vmax) {
  if (buttonRead_rep(ID_SW4)) {
    if (*val >= vmax) {
      //      *val = vmin;
      *val = vmax;
    } else {
      (*val)++;
    }
  }
  if (buttonRead_rep(ID_SW5)) {
    if (*val <= vmin) {
      //      *val = vmax;
      *val = vmin;
    } else {
      (*val)--;
    }
  }
}

void lcdPrintButton() {
  lcd.kanaOff();
  lcd.setCursor(0, 1); if (ps2x.Button(PSB_PAD_UP)) lcd.write(0x5E);
  lcd.setCursor(1, 1); if (ps2x.Button(PSB_PAD_DOWN)) lcd.write(0x76);
  lcd.setCursor(2, 1); if (ps2x.Button(PSB_PAD_LEFT)) lcd.write(0x7F);
  lcd.setCursor(3, 1); if (ps2x.Button(PSB_PAD_RIGHT)) lcd.write(0x7E);
  lcd.setCursor(4, 1); if (ps2x.Button(PSB_RED)) lcd.write('o');
  lcd.setCursor(5, 1); if (ps2x.Button(PSB_BLUE)) lcd.write('x');
  lcd.setCursor(6, 1); if (ps2x.Button(PSB_GREEN)) lcd.write('/');
  lcd.setCursor(7, 1); if (ps2x.Button(PSB_PINK)) lcd.write(0xDB);
  lcd.setCursor(8, 1); if (ps2x.Button(PSB_L1)) lcd.write('l');
  lcd.setCursor(9, 1); if (ps2x.Button(PSB_R1)) lcd.write('r');
  lcd.setCursor(10, 1); if (ps2x.Button(PSB_L2)) lcd.write('L');
  lcd.setCursor(11, 1); if (ps2x.Button(PSB_R2)) lcd.write('R');
  lcd.setCursor(12, 1); if (ps2x.Button(PSB_L3)) lcd.write('(');
  lcd.setCursor(13, 1); if (ps2x.Button(PSB_R3)) lcd.write(')');
  lcd.setCursor(14, 1); if (ps2x.Button(PSB_START)) lcd.write('>');
  lcd.setCursor(15, 1); if (ps2x.Button(PSB_SELECT)) lcd.write('#');
  lcd.kanaOn();
}

//*************************************************

//*call at 1 loop
void buttonFunc() {
  static unsigned long loopcount = 0;
  static byte oldbtnstate = B00000;
  byte btnstate_rep = B00000;

  static byte oldstate = B11111;  //*negative
  static byte state = B11111;   //*negative

  loopcount++;

  oldstate = state;
  state = digitalRead(PIN_SW1)
          | digitalRead(PIN_SW2) << 1
          | digitalRead(PIN_SW3) << 2
          | digitalRead(PIN_SW4) << 3
          | digitalRead(PIN_SW5) << 4;

  oldbtnstate = btnstate;

  btnstate |= ~(oldstate | state);  //->on
  btnstate &= ~(oldstate & state);  //->off

  btnstate_p = btnstate & ~oldbtnstate;

  //key repeat
  for (int i = 0; i <= 4; i++) {
    if (bitRead(btnstate_p, i)) btnprstime[i] = loopcount;  //start keyrep
    if (!bitRead(btnstate, i)) continue;   //end keyrep
    if (loopcount - btnprstime[i] < KEYREP_T1)  continue;  //skip till KEYREP_T1
    int x = (loopcount - btnprstime[i] - KEYREP_T1) % KEYREP_T2;
    btnstate_rep = bitWrite(btnstate_rep, i, (x == 0));
  }
  btnstate_prep = btnstate_p | btnstate_rep;
}

//press
bool buttonRead(byte btnid) {
  return !!(btnstate & btnid);
}
//press one shot
bool buttonRead_p(byte btnid) {
  return !!(btnstate_p & btnid);
}
//press + key repeat
bool buttonRead_rep(byte btnid) {
  return !!(btnstate_prep & btnid);
}
