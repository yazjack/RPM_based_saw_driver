//external libraries
#include "Ucglib.h"
Ucglib_ST7735_18x128x160_HWSPI ucg(8, 10, 9);
#include "math.h"

// internal library
#include "variables.h"
#include "stepper.h"
#include "interrupts.h"
#include "procedures.h"
#include "menu.h"

void setup() {
  Serial.begin(9600);
  ucg.begin(UCG_FONT_MODE_SOLID);
  ucg.setFont(ucg_font_7x14_mf);
  ucg.clearScreen();
  ucg.setRotate270();
  pinMode(angleEndStop, INPUT);
  pinMode(stepperEndStop, INPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  pinMode(relay, OUTPUT);
  pinMode(laser, OUTPUT);
  pinMode(encPinA, INPUT_PULLUP);
  pinMode(encPinB, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encPinA), PinA, RISING);
  attachInterrupt(digitalPinToInterrupt(encPinB), PinB, RISING);
  pinMode (buttonPin, INPUT_PULLUP);
  pinMode(hallPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(hallPin), doCount, RISING);
  pinMode(anglePinA, INPUT_PULLUP);
  pinMode(anglePinB, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(anglePinA), angleA, RISING);
  attachInterrupt(digitalPinToInterrupt(anglePinB), angleB, RISING);
  initSetup();
  mainMenuLayout();
  cntTime = millis();
}

void loop() {
  readRPM();
  readAngle();
  rotaryMenu();
  if (cutFlag == true) {
    regulatedCut();
  }
}
