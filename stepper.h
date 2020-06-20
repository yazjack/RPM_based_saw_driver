void stepForward() {
  if (stepperPos < maxPos) {
    digitalWrite(enablePin, LOW);
    digitalWrite(dirPin, LOW);
    digitalWrite(stepPin, HIGH);
    delay(delayValue);
    digitalWrite(stepPin, LOW);
    digitalWrite(enablePin, HIGH);
    stepperPos++;
    prevStepperPos = stepperPos;
  }
}

void stepBackward() {
  if (stepperPos > 0) {
    digitalWrite(enablePin, LOW);
    digitalWrite(dirPin, HIGH);
    digitalWrite(stepPin, HIGH);
    delay(delayValue);
    digitalWrite(stepPin, LOW);
    digitalWrite(enablePin, HIGH);
    stepperPos--;
    prevStepperPos = stepperPos;
  }
}

int goTo(int posNum) {
  if (posNum <= stepperPos) {
    while (posNum < stepperPos) {
      stepBackward();
    }
  }
  if (posNum >= stepperPos) {
    while (posNum > stepperPos) {
      stepForward();
    }
  }
}
