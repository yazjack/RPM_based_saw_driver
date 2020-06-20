float angleCalculation(float inputLengh) {
  B_cut = (90 - angle_sett) * 3.1415 / 180;
  a_cut = b_cut * sin(A) / sin(B_cut);
  //inputLengh = inputLengh + 1;
  a = sqrt(sq(inputLengh) + sq(c + a_cut) - 2 * inputLengh * (c + a_cut) * cos(A));
  B = asin(sin(A) * inputLengh / a) * 180 / 3.1415;
  B = B + 0.6;
  return B;
}

void calculateAngle(float height, float thick, byte vertStack) {
  int arrSize = vertStack + 1;
  float prevHeight = 0;
  float heights[10];

  for (int i = 0; i < arrSize; i++) {
    if (i == 0) {
      heights[i] = thick;
    } else if (i == arrSize - 1) {
      heights[i] = height * vertStack;
    } else {
      heights[i] = height + thick + prevHeight;
      prevHeight = heights[i] - thick;
    }
    Serial.println(heights[i]);
  }
  Serial.println();
  /*if (vertStack == 1) {
    angles[1] = angleCalculation(height);
    angles[0] = angleCalculation(thick);
    }
    if (vertStack > 1) {*/
  for (int i = 0; i < arrSize; i++) {
    angles[i] = angleCalculation(heights[i]);
    Serial.println(angles[i]);
  }
  //}
}

void readAngle() {
  angle = angleCnt * 360 / 600 / 12;
  if (timingFlag == true && anglePrevCnt != angleCnt) {
    elapsed = millis() - start;
    dpm = (double)mmTic / (elapsed / 60000.0);
    timingFlag = false;
  }
  if (timingFlag == false && anglePrevCnt != angleCnt) {
    start = millis();
    timingFlag = true;
  }
  anglePrevCnt = angleCnt;
}

void readRPM() {
  curTime = millis();
  if (curTime - cntTime > resetTime) { // reset when less than dt>resetTime
    cnt = measureCnt = 0;
    rpm = 0;
  }
  if (cnt == 1) startTime = cntTime;
  if (cnt - measureCnt >= minRotNum) {
    rpm = 60000L / 6 * (cnt - measureCnt) / (cntTime - measureTime);
    measureCnt = cnt;
    measureTime = cntTime;
  }
  rotTime = (cntTime - startTime) / 1000;
  prevRpm = rpm;
}

void displayRPM() {
  if (rpm > 28) {
    ucg.setColor(0, 0, 0, 255);
  } else if (rpm == 28) {
    ucg.setColor(0, 0, 255, 0);
  } else if (rpm == 27) {
    ucg.setColor(0, 255, 153, 0);
  } else {
    ucg.setColor(0, 255, 0, 0);
  }
  ucg.setPrintPos(60, 110);
  ucg.print(String(rpm) + " RPM" + "  ");
  ucg.setColor(0, 255, 0, 0);
}

void displayAngle() {
  ucg.setColor(0, 255, 153, 0);
  ucg.setPrintPos(10, 110);
  ucg.print(String(angle) + char(176) + "  ");
}

void displayDPM() {
  ucg.setColor(0, 255, 153, 0);
  ucg.setPrintPos(10, 125);
  ucg.print(String(dpm, 2) + " mm/min ");
}

void displayPos() {
  ucg.setPrintPos(110, 110);
  ucg.print(String(stepperPos) + " VP" + "  ");
}

void initSetup() {
  ucg.setFont(ucg_font_7x14B_mf); //Normal font
  ucg.setPrintPos(10, 10);
  ucg.print("Initializing setup");
  ucg.setFont(ucg_font_7x14_mf); //Normal font
  int stopChk, angleChk;
  bool stopFlag = 0, angleFlag = 0;
  digitalWrite(enablePin, LOW);
  delay(delayValue);
  digitalWrite(dirPin, HIGH);
  stepperPos = 0;
  ucg.setColor(0, 255, 255, 255);
  ucg.drawFrame(10, 20, 10, 10);
  ucg.setPrintPos(30, 30);
  ucg.print("Valve control");
  ucg.drawFrame(10, 40, 10, 10);
  ucg.setPrintPos(30, 50);
  ucg.print("Angle control");
  ucg.setColor(0, 0, 255, 0);
  goTo(20);
  while (stopFlag == 0 || angleFlag == 0) {
    stopChk = digitalRead(stepperEndStop);
    angleChk = digitalRead(angleEndStop);
    if (stopChk == 1) {
      stepperPos = 0;
      ucg.drawBox(12, 22, 6, 6);
      stopFlag = 1;
    } else {
      stepperPos = 1;
      stepBackward();
    }
    if (angleChk == 1) {
      ucg.drawBox(12, 42, 6, 6);
      angleFlag = 1;
    }
    if (stopFlag == 1 && angleFlag == 1) {
      break;
    }
  }
  stepperPos = 0;
  angle = 0;
  delay(delayValue);
  digitalWrite(enablePin, HIGH);
  delay(1000);
  ucg.clearScreen();
}

void exitCut() {
  dropFlag = false;
  cutFlag = false;
  goTo(60);
  delay(2000);
  goTo(0);
  ucg.setColor(0, 0, 0, 0);
  ucg.drawBox(10, 90, 160, 110);
  encoderPos = 1;
  buttonPressed = 0;
  subMenu1 = 0;
  subMenu2 = 0;
  Menu = 0;
  digitalWrite(relay, LOW);
  ucg.setColor(0, 255, 255, 255);
  ucg.setPrintPos(10, 84); // Start cut procedure:
  ucg.print("Start cutting");
}

void regulatedCut() {
  if (angle > angles[angleAmmount] + 2 && dropFlag == true) goTo(maxPos);
  if (angle <= angles[angleAmmount] + 2 && angle >= angles[angleAmmount] + 0.2 && dropFlag == true) goTo(20);
  if (angle <= angles[angleAmmount] + 0.2 && angle >= angles[angleAmmount] && dropFlag == true) goTo(5);
  if (angle <= angles[angleAmmount] && dropFlag == true && rpm < 29) {
    dropFlag = false;
    cutCounter = 0;
  }
  if (dropFlag == false) {
    if (angle <= angles[angleAmmount - cutCounter] && rpm < 29) {
      cutCounter++;
      Serial.println(angles[angleAmmount - cutCounter]);
      Serial.println(cutCounter);
    }
    if (angle >= angles[angleAmmount - cutCounter] || angle <= angles[0]) {
      if (rpm > 28) {
        stepForward();
      }
      if (rpm == 27) {
        stepBackward();
      }
      if (rpm < 27) {
        goTo(0);
      }
    }
    if (angle <= (angles[angleAmmount - cutCounter] + 0.2)) goTo(5);
  }
  if (rpm < 20) {
    digitalWrite(relay, LOW);
    goTo(0);
  }
  if (angle < 0.5 && rpm > 28) {
    exitCut(); //exit cut procedure and go back to menu
  }
}
