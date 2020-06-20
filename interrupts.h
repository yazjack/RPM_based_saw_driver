void PinA() {
  //cli(); //stop interrupts happening before we read pin values
  reading = PINE & 0x30; // read all eight pin values then strip away all but pinA and pinB's values
  if (reading == B110000 && aFlag) { //check that we have both pins at detent (HIGH) and that we are expecting detent on this pin's rising edge
    encoderPos ++; //decrement the encoder's position count
    bFlag = 0; //reset flags for the next turn
    aFlag = 0; //reset flags for the next turn
  }
  else if (reading == B010000) bFlag = 1; //signal that we're expecting pinB to signal the transition to detent from free rotation
  //sei(); //restart interrupts
}

void PinB() {
  //cli();
  reading = PINE & 0x30;
  if (reading == B110000 && bFlag) {
    encoderPos --;
    bFlag = 0;
    aFlag = 0;
  }
  else if (reading == B100000) aFlag = 1;
  //sei();
}

void angleA() {
  //cli();
  angleReading = PIND & 0x3;
  if (angleReading == B0011 && angleAFlag) {
    angleCnt --;
    angleBFlag = 0;
    angleAFlag = 0;
  }
  else if (angleReading == B0001) angleBFlag = 1;
  //sei();
}

void angleB() {
  //cli();
  angleReading = PIND & 0x3;
  if (angleReading == B0011 && angleBFlag) {
    angleCnt ++;
    angleBFlag = 0;
    angleAFlag = 0;
  }
  else if (angleReading == B0010) angleAFlag = 1;
  //sei();
}

void doCount() {
  rpmReading = PIND & 0x4;
  if (rpmReading == B0100) {
    cnt++;
    cntTime = millis();
  }
} 
