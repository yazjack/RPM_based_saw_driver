void mainMenuLayout() {
  ucg.setFont(ucg_font_7x14B_mf); // Menu label:
  ucg.setPrintPos(2, 14);
  ucg.print("MAIN MENU");
  ucg.setFont(ucg_font_7x14_mf); //Normal font
  ucg.setPrintPos(10, 28); //Stock type
  ucg.print("Choose stock type");
  ucg.setPrintPos(10, 42); //Stock size
  ucg.print("Choose stock size");
  ucg.setPrintPos(10, 56); //Multi-cut
  ucg.print("Stock ammount");
  ucg.setPrintPos(10, 70); // Open/close valve:
  ucg.print("Valve o/c");
  ucg.setPrintPos(10, 84); // Start cut procedure:
  ucg.print("Start cutting");
}

void goMain() {
  encoderPos = 1;
  buttonPressed = 0;
  subMenu1 = 0;
  subMenu2 = 0;
  Menu = 0;
  ucg.clearScreen();
  mainMenuLayout();
}

void goMenu2() {
  encoderPos = lastSub;
  buttonPressed = 0;
  subMenu1 = 0;
  Menu = 2;
}

void goMenu3() {
  encoderPos = lastSub;
  buttonPressed = 0;
  subMenu2 = 0;
  Menu = 3;
}

void menuRotaryRange(int menuMin, int menuMax) {
  if (encoderPos > (menuMax + 10)) encoderPos = menuMax;
  else if (encoderPos > menuMax) encoderPos = menuMin;
}

void menuLimitRange(int menuMin, int menuMax) {
  if (encoderPos > menuMax && encoderPos < 239) encoderPos = menuMax;
  else if (encoderPos > 240) encoderPos = menuMin;
}

void bottomDim() {
  ucg.setColor(0, 0, 204, 0);
  ucg.drawVLine(10, 87, 7);
  ucg.drawVLine(69, 87, 7);
  ucg.drawHLine(10, 90, 59);
  ucg.setPrintPos(36, 105);
}

void sideDim() {
  ucg.setColor(0, 0, 204, 0);
  ucg.drawVLine(75, 25, 29);
  ucg.drawHLine(72, 25, 7);
  ucg.drawHLine(72, 54, 7);
  ucg.setPrintPos(80, 45);
}

void thicknessDim() {
  ucg.setColor(0, 0, 204, 0);
  ucg.drawVLine(40, 20, 26);
  ucg.drawTriangle(37, 20,  40, 24,  44, 20);
  ucg.drawTriangle(37, 34,  40, 30,  44, 34);
  ucg.setPrintPos(45, 45);
}

void pointerPos(int mPos, int point_x, int point_y) {
  if (encoderPos == mPos) {
    ucg.setPrintPos(point_x, point_y);
    ucg.print(">");
  } else {
    ucg.setPrintPos(point_x, point_y);
    ucg.print(" ");
  }
}

void mainMenuPointers() {
  ucg.setColor(0, 255, 0, 0);  // Set color (0,R,G,B)
  pointerPos(1, 2, 28);
  pointerPos(2, 2, 42);
  pointerPos(3, 2, 56);
  pointerPos(4, 2, 70);
  pointerPos(5, 2, 84);
}

void menu1Pointers() {
  ucg.setColor(0, 255, 0, 0);  // Set color (0,R,G,B)
  pointerPos(0, 5, 45);
  pointerPos(1, 50, 45);
  pointerPos(2, 95, 45);
  pointerPos(3, 5, 95);
  pointerPos(4, 50, 95);
  pointerPos(5, 95, 95);
}

void menu2Pointers() {
  ucg.setColor(0, 255, 0, 0);
  if (stockType_sett == 0 || stockType_sett == 1) {
    pointerPos(1, 105, 28);
    pointerPos(2, 105, 42);
    pointerPos(3, 105, 56);
  }
  if (stockType_sett == 2) {
    pointerPos(1, 105, 28);
    pointerPos(2, 105, 42);
    pointerPos(3, 105, 56);
    pointerPos(4, 105, 70);
  }
  if (stockType_sett == 3 || stockType_sett == 4) {
    pointerPos(1, 105, 28);
    pointerPos(2, 105, 42);
  }
  if (stockType_sett == 5) {
    pointerPos(1, 105, 28);
    pointerPos(2, 105, 42);
    pointerPos(3, 105, 56);
  }
}

void menu3Pointers() {
  ucg.setColor(0, 255, 0, 0);
  pointerPos(1, 105-63, 28);
  pointerPos(2, 105-49, 42);
  pointerPos(3, 105-56, 56);
  pointerPos(4, 105, 70);
}

void Menu1Layout() {
  ucg.clearScreen();
  ucg.setFont(ucg_font_7x14B_mf);
  ucg.setColor(0, 255, 255, 255);
  ucg.setPrintPos(2, 14);
  ucg.print("STOCK TYPE");
  ucg.drawCircle(30, 40, 15, UCG_DRAW_ALL);  //circle empty
  ucg.drawCircle(30, 40, 12, UCG_DRAW_ALL);
  ucg.drawFrame(60, 25, 30, 30);  //square empty
  ucg.drawFrame(63, 28, 24, 24);
  ucg.drawFrame(105, 30, 30, 20);  //rectangle empty
  ucg.drawFrame(108, 33, 24, 14);
  ucg.drawDisc(30, 90, 15, UCG_DRAW_ALL); //circle full
  ucg.drawBox(60, 75, 30, 30);  //square full
  ucg.drawBox(105, 80, 30, 20);  //rectangle full
}

void Menu2Layout() {
  ucg.clearScreen();
  ucg.setFont(ucg_font_7x14B_mf);
  ucg.setColor(0, 255, 255, 255);
  ucg.setPrintPos(2, 14);
  ucg.print("STOCK SIZE");
  ucg.setFont(ucg_font_7x14_mf);
  if (stockType_sett == 6) {
    ucg.setColor(0, 255, 255, 255);
    ucg.setPrintPos(10, 28);
    ucg.print("Pick the stock");
    ucg.setPrintPos(10, 42);
    ucg.print("type first!");
    delay(1000);
    goMain();
  }
  if (stockType_sett == 0) {  //empty circle
    ucg.setColor(0, 255, 255, 255);

    ucg.setPrintPos(M2FontsXPos, 28);
    ucg.print("a:");
    ucg.setPrintPos(M2FontsXPos, 42);
    ucg.print("t:");
    ucg.setPrintPos(M2FontsXPos, 56);
    ucg.print("exit");

    ucg.setPrintPos(M2SettingsXPos, 28);
    ucg.print(width_sett);
    ucg.setPrintPos(M2SettingsXPos, 42);
    ucg.print(thick_sett, 1);

    //ucg.setColor(0, 255, 255, 255);
    ucg.drawCircle(40, 55, 30, UCG_DRAW_ALL);
    ucg.drawCircle(40, 55, 26, UCG_DRAW_ALL);

    bottomDim();
    ucg.print("a");

    thicknessDim();
    ucg.print("t");
  }
  if (stockType_sett == 1) { //empty square
    ucg.setColor(0, 255, 255, 255);
    //ucg.setColor(1, 0, 0, 0);
    ucg.setPrintPos(M2FontsXPos, 28);
    ucg.print("a:");
    ucg.setPrintPos(M2FontsXPos, 42);
    ucg.print("t:");
    ucg.setPrintPos(M2FontsXPos, 56);
    ucg.print("exit");

    ucg.setPrintPos(M2SettingsXPos, 28);
    ucg.print(width_sett);
    ucg.setPrintPos(M2SettingsXPos, 42);
    ucg.print(thick_sett, 1);

    //ucg.setColor(0, 255, 255, 255);
    ucg.drawFrame(10, 25, 60, 60);
    ucg.drawFrame(14, 29, 52, 52);

    bottomDim();
    ucg.print("a");
    thicknessDim();
    ucg.print("t");
  }
  if (stockType_sett == 2) { //empty rectangle
    ucg.setColor(0, 255, 255, 255);
    //ucg.setColor(1, 0, 0, 0);

    ucg.setPrintPos(M2FontsXPos, 28);
    ucg.print("a:");
    ucg.setPrintPos(M2FontsXPos, 42);
    ucg.print("b:");
    ucg.setPrintPos(M2FontsXPos, 56);
    ucg.print("t:");
    ucg.setPrintPos(M2FontsXPos, 70);
    ucg.print("exit");

    ucg.drawFrame(10, 25, 60, 30);
    ucg.drawFrame(14, 29, 52, 22);

    ucg.setPrintPos(M2SettingsXPos, 28);
    ucg.print(width_sett);
    ucg.setPrintPos(M2SettingsXPos, 42);
    ucg.print(height_sett);
    ucg.setPrintPos(M2SettingsXPos, 56);
    ucg.print(thick_sett, 1);

    bottomDim();
    ucg.print("a");

    sideDim();
    ucg.print("b");

    thicknessDim();
    ucg.print("t");
  }
  if (stockType_sett == 3) { //full circle
    ucg.setColor(0, 255, 255, 255);
    //ucg.setColor(1, 0, 0, 0);

    ucg.setPrintPos(M2FontsXPos, 28);
    ucg.print("a:");
    ucg.setPrintPos(M2FontsXPos, 42);
    ucg.print("exit");

    ucg.drawDisc(40, 55, 30, UCG_DRAW_ALL);

    ucg.setPrintPos(M2SettingsXPos, 28);
    ucg.print(width_sett);

    bottomDim();
    ucg.print("a");
  }
  if (stockType_sett == 4) { //full square
    ucg.setColor(0, 255, 255, 255);
    //ucg.setColor(1, 0, 0, 0);
    ucg.setPrintPos(M2FontsXPos, 28);
    ucg.print("a:");
    ucg.setPrintPos(M2FontsXPos, 42);
    ucg.print("exit");

    ucg.drawBox(10, 25, 60, 60);

    ucg.setPrintPos(M2SettingsXPos, 28);
    ucg.print(width_sett);

    bottomDim();
    ucg.print("a");
  }
  if (stockType_sett == 5) { //full rectangle
    ucg.setColor(0, 255, 255, 255);
    //ucg.setColor(1, 0, 0, 0);

    ucg.setPrintPos(M2FontsXPos, 28);
    ucg.print("a:");
    ucg.setPrintPos(M2FontsXPos, 42);
    ucg.print("b:");
    ucg.setPrintPos(M2FontsXPos, 56);
    ucg.print("exit");

    ucg.drawBox(10, 25, 60, 30);
    ucg.setColor(0, 0, 204, 0);

    ucg.setPrintPos(M2SettingsXPos, 28);
    ucg.print(width_sett);
    ucg.setPrintPos(M2SettingsXPos, 42);
    ucg.print(height_sett);

    bottomDim();
    ucg.print("a");

    sideDim();
    ucg.print("b");
  }
}

void Menu3Layout() {
  ucg.clearScreen();
  if (stockType_sett == 6) {
    ucg.setColor(0, 255, 255, 255);
    ucg.setPrintPos(10, 28);
    ucg.print("Pick the stock");
    ucg.setPrintPos(10, 42);
    ucg.print("type first!");
    delay(1000);
    goMain();
  } else {
    ucg.setFont(ucg_font_7x14B_mf);
    ucg.setColor(0, 255, 255, 255);
    ucg.setPrintPos(2, 14);
    ucg.print("STOCK AMMOUNT");
    ucg.setFont(ucg_font_7x14_mf);
    ucg.setPrintPos(M2FontsXPos-63, 28);
    ucg.print("horizontal:");
    ucg.setPrintPos(M2FontsXPos-49, 42);
    ucg.print("vertical:");
    ucg.setPrintPos(M2FontsXPos-56, 56);
    ucg.print("cut angle:");
    ucg.setPrintPos(M2FontsXPos, 70);
    ucg.print("exit");
    ucg.setPrintPos(M2SettingsXPos, 28);
    ucg.print(hor_sett);
    ucg.setPrintPos(M2SettingsXPos, 42);
    ucg.print(vert_sett);
    ucg.setPrintPos(M2SettingsXPos, 56);
    ucg.print(angle_sett);
  }
}

void Menu4Layout() {
  ucg.clearScreen();
  ucg.setFont(ucg_font_7x14B_mf);
  ucg.setColor(0, 255, 255, 255);
  //ucg.setColor(1, 0, 0, 0);
  ucg.setPrintPos(2, 14);
  ucg.print("OPEN/CLOSE VALVE");
  ucg.setFont(ucg_font_7x14_mf);
  //ucg.setColor(0, 255, 255, 255);
  //ucg.setColor(1, 0, 0, 0);
  ucg.setPrintPos(80, 40);
  ucg.print(stepperPos);
}
