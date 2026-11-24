int readKnob2() {
  int readings[10];
  for (int i = 0; i < 10; i++) {
    readings[i] = analogRead(32);
    delay(2);
  }

  // Sort readings
  for (int i = 0; i < 9; i++)
    for (int j = i + 1; j < 10; j++)
      if (readings[j] < readings[i]) {
        int tmp = readings[i];
        readings[i] = readings[j];
        readings[j] = tmp;
      }

  // Average middle 6, discard 2 lowest and 2 highest
  int sum = 0;
  for (int i = 2; i < 8; i++) sum += readings[i];
  return sum / 6;
}

void SelectMenu() {
  motorStop();
  lcdSetTextSize(1);
  tft.fillScreen(ST77XX_BLACK);
  while (1) {
    lcdPrintText(0, 20, "A SelectPlace              ", 0xffff);
    lcdPrintText(0, 40, "B Menu                   ", 0xffff);
    delay(100);
    if (switchRead(A) == 1) {
      SelectPlace();
      break;
    } else if (switchRead(B) == 1) {
      MenuTEST();
      break;
    }
  }
  lcdClear();
  beep(100);
  delay(200);
}
void MenuTEST() {
  while (1) {
    motorStop();
    lcdSetTextSize(2);
    tft.fillScreen(ST77XX_BLACK);
    setAngleOffset();
    current_degree = 0;
    lift(0);
    setupServo();
    X=-1;
    while (1) {
      int raw = readKnob2();
      raw = constrain(raw, 1230, 2650);
      int newX = map(raw, 1230, 2590, 0, 20);

      // Only update X if it didn't jump more than 1 step suddenly
      if (abs(newX - X) <= 1 || X == -1) {
        X = newX;
      }
      lcdPrintText(0, 0, String(X), 0xffff);
      ReadMenu();
      delay(100);
      if (switchRead(A) == 1 || switchRead(B) == 1) {
        DoMenu();
        Serial.print("You Press!!");
        break;
      }
    }
    beep(100);
    delay(200);
    lcdPrintText(0, 60, "SW_A || SW_B again", 0xffff);
    lcdPrintText(0, 70, "You Press " + String(X), 0xffff);
    STOP();
  }
}

void ReadMenu() {
  if (X == 0) {
    lcdPrintText(0, 20, "A Not Use              ", 0xffff);
    lcdPrintText(0, 40, "B Not Use                   ", 0xffff);
  } else if (X == 1) {
    lcdPrintText(0, 20, "A CalibColor               ", 0xffff);
    lcdPrintText(0, 40, "B readColor                         ", 0xffff);
  } else if (X == 2) {
    lcdPrintText(0, 20, "A Value_SS                    ", 0xffff);
    lcdPrintText(0, 40, "B SonarLCD                    ", 0xffff);
  } else if (X == 3) {
    lcdPrintText(0, 20, "A FullMap                    ", 0xffff);
    lcdPrintText(0, 40, "B ReTryT2                    ", 0xffff);
  } else if (X == 4) {
    lcdPrintText(0, 20, "A ReTryT3                     ", 0xffff);
    lcdPrintText(0, 40, "B BackFinish                    ", 0xffff);
  } else if (X == 5) {
    lcdPrintText(0, 20, "A CheckColGrip                    ", 0xffff);
    lcdPrintText(0, 40, "B Line_Serial                    ", 0xffff);
  } else if (X == 6) {
    lcdPrintText(0, 20, "A Block1                    ", 0xffff);
    lcdPrintText(0, 40, "B Block2                    ", 0xffff);
  } else if (X == 7) {
    lcdPrintText(0, 20, "A Block3                    ", 0xffff);
    lcdPrintText(0, 40, "B BlockFinish                    ", 0xffff);
  } else if (X == 8) {
    lcdPrintText(0, 20, "A Yellow                    ", 0xffff);
    lcdPrintText(0, 40, "B Green                    ", 0xffff);
  } else if (X == 9) {
    lcdPrintText(0, 20, "A Red                 ", 0xffff);
    lcdPrintText(0, 40, "B TestEnc            ", 0xffff);
  } else if (X == 10) {
    lcdPrintText(0, 20, "A MB1                 ", 0xffff);
    lcdPrintText(0, 40, "B SetWall                 ", 0xffff);
  } else if (X == 11) {
    lcdPrintText(0, 20, "A Left          ", 0xffff);
    lcdPrintText(0, 40, "B Right             ", 0xffff);
  } else if (X == 12) {
    lcdPrintText(0, 20, "A Pick & SL              ", 0xffff);
    lcdPrintText(0, 40, "B Pick & SR         ", 0xffff);
  } else if (X == 13) {
    lcdPrintText(0, 20, "A Cal IMU       ", 0xffff);
    lcdPrintText(0, 40, "B MB1-80          ", 0xffff);
  } else if (X == 14) {
    lcdPrintText(0, 20, "A TL-F             ", 0xffff);
    lcdPrintText(0, 40, "B TR-F             ", 0xffff);
  } else if (X == 15) {
    lcdPrintText(0, 20, "A TL-B             ", 0xffff);
    lcdPrintText(0, 40, "B TR-B             ", 0xffff);
  } else if (X == 16) {
    lcdPrintText(0, 20, "A                  ", 0xffff);
    lcdPrintText(0, 40, "B                  ", 0xffff);
  }
}