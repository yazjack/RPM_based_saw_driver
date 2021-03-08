import pyb
import time
from pyb import Pin, ExtInt

hallPin = Pin('Y1')

encMenuPinA = Pin('Y2') #Y2
encMenuPinB = Pin('Y4') #Y3
encMenuPinBtn = Pin('Y3') #Y4

encAnglePinA = Pin('X12') #Y5
encAnglePinB = Pin('X11') #Y6
encAnglePinZ = Pin('Y8') #Y7

t = time.ticks_ms()
tdt = 1
tt = 1

cntMenuBtn = 1
oldEncPos = 0
encoderPos = 1
aFlagMenu = 0
bFlagMenu = 0

cntAngleEnc = 0
aFlagAngle = 0
bFlagAngle = 0
zFlagAngle = 0

def clbEncA(v):
    global encoderPos
    global aFlagMenu
    global bFlagMenu
    if encMenuPinA.value()==1 and encMenuPinB.value()==1 and aFlagMenu==1:
        encoderPos += 1
        bFlagMenu = 0
        aFlagMenu = 0
    elif encMenuPinA.value()==1 and encMenuPinB.value()==0:
        bFlagMenu = 1

def clbEncB(v):
    global encoderPos
    global aFlagMenu
    global bFlagMenu
    if encMenuPinA.value()==1 and encMenuPinB.value()==1 and bFlagMenu==1:
        encoderPos -= 1
        bFlagMenu = 0
        aFlagMenu = 0
    elif encMenuPinA.value()==0 and encMenuPinB.value()==1:
        aFlagMenu = 1

def clbEncBtn(v):
    global cntMenuBtn
    cntMenuBtn = 1

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
    global t
    global tdt
    global tt
    #tdt = time.ticks_diff(time.ticks_ms(), t)
    #t = time.ticks_ms()
    tt += 1
    print(tt, ' ', tdt)
    
encMenuA = ExtInt(encMenuPinA, ExtInt.IRQ_RISING, Pin.PULL_NONE, clbEncA)
encMenuB = ExtInt(encMenuPinB, ExtInt.IRQ_RISING, Pin.PULL_NONE, clbEncB)
encMenuBtn = ExtInt(encMenuPinBtn, ExtInt.IRQ_RISING, Pin.PULL_NONE, clbEncBtn)

encAngleA = ExtInt(encAnglePinA, ExtInt.IRQ_RISING, Pin.PULL_UP, clbEncAngA)
encAngleB = ExtInt(encAnglePinB, ExtInt.IRQ_RISING, Pin.PULL_UP, clbEncAngB)

hall = ExtInt(hallPin, ExtInt.IRQ_RISING, Pin.PULL_NONE, clbHall) 
