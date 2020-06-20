#include "menu_procedures.h"

void rotaryMenu() {
  if (oldEncPos != encoderPos) {
    oldEncPos = encoderPos;
  }
  byte buttonState = digitalRead (buttonPin);
  if (buttonState != oldButtonState) {
    if (millis () - buttonPressTime >= debounceTime) {
      buttonPressTime = millis ();
      oldButtonState =  buttonState;
      if (buttonState == LOW) {
        buttonPressed = 1;
      }
      else {
        buttonPressed = 0;
      }
    }
  }
  /* ____________________________________________________________________________________
    |                                                                                      |
    |  Menu selection and first click                                                      |
    |______________________________________________________________________________________|*/
  if (Menu == 0) {
    mainMenuPointers();
    menuRotaryRange(1, 5);
    if (encoderPos == 5) {
      digitalWrite(laser, HIGH);
    } else {
      digitalWrite(laser, LOW);
    }

    if (buttonPressed) {
      Menu = encoderPos;
      buttonPressed = 0;
      if (Menu == 1) {
        stockType_sett = 0;
        Menu1Layout();
        encoderPos = stockType_sett;
      }
      if (Menu == 2) {
        Menu2Layout();
        if (buttonPressed) {
          subMenu1 = encoderPos;
          buttonPressed = 0;
        }
      }
      if (Menu == 3) {
        if (height_sett == 0) {
          ucg.clearScreen();
          ucg.setColor(0, 255, 255, 255);
          ucg.setPrintPos(10, 28);
          ucg.print("Stock size must be");
          ucg.setPrintPos(10, 42);
          ucg.print("grater than 0!");
          delay(1000);
          goMain();
        } else {
          encoderPos = 1;
          Menu3Layout();
          if (buttonPressed) {
            subMenu2 = encoderPos;
            buttonPressed = 0;
          }
        }
      }
      if (Menu == 4) {
        Menu4Layout();
        encoderPos = stepperPos;
      }
      if (Menu == 5) {
        if (hor_sett == 0 || vert_sett == 0) {
          ucg.clearScreen();
          ucg.setColor(0, 255, 255, 255);
          ucg.setPrintPos(10, 28);
          ucg.print("Pick the ammount");
          ucg.setPrintPos(10, 42);
          ucg.print("of stock first!");
          delay(1000);
          goMain();
        } else {
          calculateAngle(height_sett, thick_sett, vert_sett);
          angleAmmount = vert_sett;
          cutFlag = true;
          dropFlag = true;
          digitalWrite(relay, LOW);
          ucg.setColor(0, 255, 0, 0);
          ucg.setPrintPos(10, 84);
          ucg.print("CUTTING...             ");
          ucg.setColor(0, 255, 255, 255);
        }
      }
    }
  }
  /* ____________________________________________________________________________________
    |                                                                                      |
    |  Menu second action and sub menus                                                    |
    |______________________________________________________________________________________|*/

  if (Menu == 2 && subMenu1 == 0) {
    if (stockType_sett == 0 || stockType_sett == 1) {
      menuLimitRange(1, 3);
    }
    if (stockType_sett == 2) {
      menuLimitRange(1, 4);
    }
    if (stockType_sett == 3 || stockType_sett == 4) {
      menuLimitRange(1, 2);
    }
    if (stockType_sett == 5) {
      menuLimitRange(1, 3);
    }
    menu2Pointers();
    if (buttonPressed) {
      lastSub = encoderPos;
      subMenu1 = encoderPos;
      buttonPressed = 0;
      if (stockType_sett == 0 || stockType_sett == 1) {
        if (subMenu1 == 1) encoderPos = width_sett;
        if (subMenu1 == 2) encoderPos = thick_sett * 2;//0.5;
        if (subMenu1 == 3) {
          if (hor_sett == 0 || vert_sett == 0) {
            buttonPressed = 0;
            subMenu1 = 0;
            encoderPos = 1;
            subMenu2 = 0;
            Menu = 3;
            ucg.clearScreen();
            Menu3Layout();
          } else {
            goMain();
          }
        }
      }
      if (stockType_sett == 2) {
        if (subMenu1 == 1) encoderPos = width_sett;
        if (subMenu1 == 2) encoderPos = height_sett;
        if (subMenu1 == 3) encoderPos = thick_sett * 2;//0.5;
        if (subMenu1 == 4) {
          if (hor_sett == 0 || vert_sett == 0) {
            buttonPressed = 0;
            subMenu1 = 0;
            encoderPos = 1;
            subMenu2 = 0;
            Menu = 3;
            ucg.clearScreen();
            Menu3Layout();
          } else {
            goMain();
          }
        }
      }
      if (stockType_sett == 3 || stockType_sett == 4) {
        if (subMenu1 == 1) encoderPos = width_sett;
        if (subMenu1 == 2) {
          if (hor_sett == 0 || vert_sett == 0) {
            buttonPressed = 0;
            subMenu1 = 0;
            encoderPos = 1;
            subMenu2 = 0;
            Menu = 3;
            ucg.clearScreen();
            Menu3Layout();
          } else {
            goMain();
          }
        }
      }
      if (stockType_sett == 5) {
        if (subMenu1 == 1) encoderPos = width_sett;
        if (subMenu1 == 2) encoderPos = height_sett;
        if (subMenu1 == 3) {
          if (hor_sett == 0 || vert_sett == 0) {
            buttonPressed = 0;
            subMenu1 = 0;
            encoderPos = 1;
            subMenu2 = 0;
            Menu = 3;
            ucg.clearScreen();
            Menu3Layout();
          } else {
            goMain();
          }
        }
      }
    }
  }

  if (Menu == 3 && subMenu2 == 0) {
    menuLimitRange(1, 4);
    menu3Pointers();
    if (buttonPressed) {
      lastSub = encoderPos;
      subMenu2 = encoderPos;
      buttonPressed = 0;
      if (subMenu2 == 1) encoderPos = hor_sett;
      if (subMenu2 == 2) encoderPos = vert_sett;
      if (subMenu2 == 3) encoderPos = angle_sett;
      if (subMenu2 == 4) goMain();
    }
  }

  if (Menu == 5) {
    displayRPM();
    displayAngle();
    displayDPM();
    displayPos();
    digitalWrite(relay, HIGH);
    digitalWrite(laser, LOW);
  }

  /* ____________________________________________________________________________________
    |                                                                                      |
    |  Dynamically updated values and range locks after first click                        |
    |______________________________________________________________________________________|*/
  if (Menu == 1) {
    menuLimitRange(0, 5);
    menu1Pointers();
  }
  if (Menu == 2 && subMenu1 == 1) {
    menuLimitRange(1, 200);
    ucg.setColor(0, 255, 0, 0);
    ucg.setPrintPos(M2SettingsXPos, 28);
    ucg.print(String(encoderPos) + "  ");
  }
  if (Menu == 2 && subMenu1 == 2) {
    menuLimitRange(1, 200);
    ucg.setColor(0, 255, 0, 0);
    ucg.setPrintPos(M2SettingsXPos, 42);
    if (stockType_sett == 0 || stockType_sett == 1) {
      ucg.print(String(encoderPos * 0.5, 1) + "  ");
    } else {
      ucg.print(String(encoderPos) + "  ");
    }
  }
  if (Menu == 2 && subMenu1 == 3) {
    menuLimitRange(1, 10);
    ucg.setColor(0, 255, 0, 0);
    ucg.setPrintPos(M2SettingsXPos, 56);
    if (stockType_sett == 2) {
      ucg.print(String(encoderPos * 0.5, 1) + "  ");
    } else {
      ucg.print(String(encoderPos) + "  ");
    }
  }

  if (Menu == 3 && subMenu2 == 1) {
    menuLimitRange(1, maxH0 / width_sett);
    ucg.setColor(0, 255, 0, 0);
    ucg.setPrintPos(M2SettingsXPos, 28);
    ucg.print(String(encoderPos) + "  ");
  }
  if (Menu == 3 && subMenu2 == 2) {
    menuLimitRange(1, maxV0 / height_sett);
    ucg.setColor(0, 255, 0, 0);
    ucg.setPrintPos(M2SettingsXPos, 42);
    ucg.print(String(encoderPos) + "  ");
  }
  if (Menu == 3 && subMenu2 == 3) {
    menuLimitRange(0, 45);
    ucg.setColor(0, 255, 0, 0);
    ucg.setPrintPos(M2SettingsXPos, 56);
    ucg.print(String(encoderPos) + "  ");
  }

  if (Menu == 4) {
    menuLimitRange(0, maxPos);
    goTo(encoderPos);
    ucg.setPrintPos(70, 40);
    ucg.print(String(encoderPos) + "  ");
  }
  /* ____________________________________________________________________________________
    |                                                                                      |
    |  Second click behaviour                                                              |
    |______________________________________________________________________________________|*/
  if (Menu == 1 && buttonPressed) {
    stockType_sett = encoderPos;
    encoderPos = 1;
    buttonPressed = 0;
    subMenu1 = 0;
    Menu = 2;
    ucg.clearScreen();
    Menu2Layout();
  }

  if (subMenu1 == 1 && buttonPressed) {
    ucg.setColor(0, 255, 255, 255);
    height_sett = encoderPos;
    width_sett = encoderPos;
    ucg.setPrintPos(M2SettingsXPos, 28);
    ucg.print(width_sett);
    goMenu2();
  }

  if (subMenu1 == 2 && buttonPressed) {
    ucg.setColor(0, 255, 255, 255);
    if (stockType_sett == 0 || stockType_sett == 1) {
      thick_sett = encoderPos * 0.5;
      ucg.setPrintPos(M2SettingsXPos, 42);
      ucg.print(thick_sett, 1);
      goMenu2();
    }
    if (stockType_sett == 2 || stockType_sett == 5) {
      height_sett = encoderPos;
      ucg.setPrintPos(M2SettingsXPos, 42);
      ucg.print(height_sett);
      goMenu2();
    }
    if (stockType_sett == 3 || stockType_sett == 4) {
      goMain();
    }
  }
  if (subMenu1 == 3 && buttonPressed) {
    ucg.setColor(0, 255, 255, 255);
    if (stockType_sett == 0 || stockType_sett == 1 || stockType_sett == 5) {
      goMain();
    }
    if (stockType_sett == 2) {
      thick_sett = encoderPos * 0.5;
      ucg.setPrintPos(M2SettingsXPos, 56);
      ucg.print(thick_sett);
      goMenu2();
    }
  }

  if (subMenu2 == 1 && buttonPressed) {
    ucg.setColor(0, 255, 255, 255);
    hor_sett = encoderPos;
    ucg.setPrintPos(M2SettingsXPos, 28);
    ucg.print(hor_sett);
    goMenu3();
  }
  if (subMenu2 == 2 && buttonPressed) {
    ucg.setColor(0, 255, 255, 255);
    vert_sett = encoderPos;
    ucg.setPrintPos(M2SettingsXPos, 42);
    ucg.print(vert_sett);
    goMenu3();
  }
  if (subMenu2 == 3 && buttonPressed) {
    ucg.setColor(0, 255, 255, 255);
    angle_sett = encoderPos;
    ucg.setPrintPos(M2SettingsXPos, 56);
    ucg.print(angle_sett);
    goMenu3();
  }

  if (Menu == 4 && buttonPressed) {
    goMain();
  }
  if (Menu == 5 && buttonPressed) {
    //exit cut procedure
    digitalWrite(relay, LOW);
    dropFlag = false;
    cutFlag = false;
    goTo(0);
    ucg.setColor(0, 0, 0, 0);
    ucg.drawBox(10, 90, 160, 110);
    encoderPos = 1;
    buttonPressed = 0;
    subMenu1 = 0;
    subMenu2 = 0;
    Menu = 0;
    ucg.setColor(0, 255, 255, 255);
    ucg.setPrintPos(10, 84); // Start cut procedure:
    ucg.print("Start cutting");
  }
}
