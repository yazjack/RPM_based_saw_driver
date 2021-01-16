#https://github.com/boochow/MicroPython-ST7735
from ST7735 import TFT
from machine import SPI,Pin
from pyb import ExtInt
from sysfont import sysfont
import time
import math
spi = SPI('X', baudrate=20000000, polarity=0, phase=0)
tft=TFT(spi,'X4','X3','X5') #DC, reset, CS
tft.initr()
tft.rgb(True)

cntMenuEnc = 0
aFlagMenu = 0
bFlagMenu = 0

cntAngleEnc = 0
aFlagAngle = 0
bFlagAngle = 0
zFlagAngle = 0

laserPin = pyb.Pin('X12')
ssrPin = pyb.Pin('X11')

hallPin = pyb.Pin('Y1')

encMenuPinA = pyb.Pin('Y2') #Y2
encMenuPinB = pyb.Pin('Y4') #Y3
encMenuPinBtn = pyb.Pin('Y3') #Y4

encAnglePinA = pyb.Pin('X12') #Y5
encAnglePinB = pyb.Pin('X11') #Y6
encAnglePinZ = pyb.Pin('Y8') #Y7

def clbEncA(v):
    global cntMenuEnc
    global aFlagMenu
    global bFlagMenu
    if encMenuPinA.value()==1 and encMenuPinB.value()==1 and aFlagMenu==1:
        cntMenuEnc += 1
        print('Encoder @ position ',cntMenuEnc)
        bFlagMenu = 0
        aFlagMenu = 0
    elif encMenuPinA.value()==1 and encMenuPinB.value()==0:
        bFlagMenu = 1

def clbEncB(v):
    global cntMenuEnc
    global aFlagMenu
    global bFlagMenu
    if encMenuPinA.value()==1 and encMenuPinB.value()==1 and bFlagMenu==1:
        cntMenuEnc -= 1
        print('Encoder @ position ',cntMenuEnc)
        bFlagMenu = 0
        aFlagMenu = 0
    elif encMenuPinA.value()==0 and encMenuPinB.value()==1:
        aFlagMenu = 1

def clbEncBtn(v):
    global cntMenuBtn
    print('button pressed')

def clbEncAngA(v):
    global cntAngleEnc
    global aFlagAngle
    global bFlagAngle
    if encAnglePinA.value()==1 and encAnglePinB.value()==1 and aFlagAngle==1:
        cntAngleEnc += 1
        #print('Encoder @ position ',cntAngleEnc)
        bFlagAngle = 0
        aFlagAngle = 0
    elif encAnglePinA.value()==1 and encAnglePinB.value()==0:
        bFlagAngle = 1
    
def clbEncAngB(v):
    global cntAngleEnc
    global aFlagAngle
    global bFlagAngle
    if encAnglePinA.value()==1 and encAnglePinB.value()==1 and bFlagAngle==1:
        cntAngleEnc -= 1
        #print('Encoder @ position ',cntAngleEnc)
        bFlagAngle = 0
        aFlagAngle = 0
    elif encAnglePinA.value()==0 and encAnglePinB.value()==1:
        aFlagAngle = 1    
    
def clbHall(v):
    print('hall')
    
encMenuA = ExtInt(encMenuPinA, ExtInt.IRQ_RISING, Pin.PULL_NONE, clbEncA)
encMenuB = ExtInt(encMenuPinB, ExtInt.IRQ_RISING, Pin.PULL_NONE, clbEncB)
encMenuBtn = ExtInt(encMenuPinBtn, ExtInt.IRQ_RISING, Pin.PULL_NONE, clbEncBtn)

encAngleA = ExtInt(encAnglePinA, ExtInt.IRQ_RISING, Pin.PULL_UP, clbEncAngA)
encAngleB = ExtInt(encAnglePinB, ExtInt.IRQ_RISING, Pin.PULL_UP, clbEncAngB)

hall = ExtInt(hallPin, ExtInt.IRQ_RISING, Pin.PULL_NONE, clbHall)

def calculateAngle(encoderPosition):
    angle = 360/2500*encoderPosition
    print(angle,' deg')

def mainMenuLayout():
    tft.fill(TFT.BLACK)
    left_margin = 15
    h = 5
    tft.text((left_margin, h), "MAIN MENU", TFT.GRAY, sysfont, 1, nowrap=True)
    h += sysfont["Height"]
    tft.text((left_margin, h), "Choose stock type", TFT.WHITE, sysfont, 1, nowrap=True)
    h += sysfont["Height"]
    tft.text((left_margin, h), "Choose stock size", TFT.WHITE, sysfont, 1, nowrap=True)
    h += sysfont["Height"]
    tft.text((left_margin, h), "Stock ammount", TFT.WHITE, sysfont, 1, nowrap=True)
    h += sysfont["Height"]
    tft.text((left_margin, h), "Valve o/c", TFT.WHITE, sysfont, 1, nowrap=True)
    h += sysfont["Height"]
    tft.text((left_margin, h), "Start cutting", TFT.WHITE, sysfont, 1, nowrap=True)
    h += sysfont["Height"]
    
def menuPointer():
    left_margin = 5
    h = 5 + cntMenuEnc*sysfont["Height"]
    if cntMenuEnc < 6 and cntMenuEnc > 0:
        tft.text((left_margin, h), "*", TFT.RED, sysfont, 1, nowrap=True)
        tft.text((left_margin, h-sysfont["Height"]), "*", TFT.BLACK, sysfont, 1, nowrap=True)
        tft.text((left_margin, h+sysfont["Height"]), "*", TFT.BLACK, sysfont, 1, nowrap=True)
    
mainMenuLayout()

def main():
    global cntAngleEnc
    angle = round(360/2500*cntAngleEnc, 3)
    tft.text((15, 60), "Angle: "+str(angle)+" ", TFT.WHITE, sysfont, 1, nowrap=True)

while 1:
    main()
    menuPointer()
