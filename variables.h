int cutCounter;

//pins
const byte dirPin = 15, stepperEndStop = 16, stepPin = 17, enablePin = 29;
const byte anglePinA = 21, anglePinB = 20, angleEndStop = 18;
const byte hallPin = 19;
const byte encPinA = 2, encPinB = 3, buttonPin = 5;
const byte relay = 32, laser = 34; 

//stepper
const int maxPos = 60, delayValue = 20;
int stepperPos = 0, prevStepperPos, posNum;

//angle measurement declarations
int angleAmmount;
float angles[10];
float a, B, C, topAngle, bottomAngle, angle, anglePrevCnt, thick_sett, b_cut = 11, B_cut, a_cut;
const float c = 271.0, A = 90 * 3.1415 / 180;

unsigned long start, elapsed;
double dpm, mmTic=0.24609;
bool timingFlag = true;

//RPM meter declarations
const int resetTime = 1000, minRotNum = 1;
int rotTime = 0, measureCnt = 0, distance;
volatile unsigned long rpm = 0, maxrpm = 0, prevRpm = 0;
bool dropFlag = true, cutFlag = false, cutPauseFlag, nextCutFlag;

// Menu and subMenu/setting declarations
byte maxH0 = 150, maxV0 = 128, maxH45 = 75, maxV45 = 95;
byte oldButtonState = HIGH;
const unsigned long debounceTime = 10;
unsigned long buttonPressTime;
boolean buttonPressed = 0;
byte Menu, subMenu1, subMenu2, lastSub, stockType_sett = 6, width_sett, height_sett, hor_sett, vert_sett, angle_sett, M2FontsXPos = 115, M2SettingsXPos = M2FontsXPos + 21;

//interrupts
volatile byte aFlag, bFlag, oldEncPos, reading, encoderPos = 1, angleReading, angleAFlag, angleBFlag;
volatile unsigned long cnt = 0, cntTime = 0, rpmReading;
unsigned long measureTime = 0, curTime, startTime = 0;
volatile float angleCnt = 0;
