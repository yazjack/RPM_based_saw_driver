import interrupts as itr
import math
import time
from ST7735 import TFT
from sysfont import sysfont
from machine import SPI

spi = SPI('X', baudrate=20000000, polarity=0, phase=0)
tft=TFT(spi,'X4','X3','X5') #DC, reset, CS
tft.initr()
tft.rgb(True)

def truncate(n, decimals):
    multiplier = 10 ** decimals
    return int(n * multiplier) / multiplier
    
def armAngleRead(angleCnt):
    angle = round(360/2500*itr.cntAngleEnc, 3)
    tft.text((15, 60), "Angle: "+str(angle)+" ", TFT.WHITE, sysfont, 1, nowrap=True)

def RPM():
    itr.t
    itr.tt
    itr.tdt
    itr.tdt = time.ticks_diff(time.ticks_ms(), itr.t)
    if itr.tdt >=2000:
        itr.tt = 0
        itr.tdt = 0
        t = time.ticks_ms()
        tft.text((15, 75), "RPM: 0                       ", TFT.WHITE, sysfont, 1, nowrap=True)
    if itr.tt >= 3 and itr.tdt <=3000:
        deltaTime = itr.tdt/itr.tt
        frq = 1/deltaTime
        itr.tt = 0
        itr.tdt = 0
        itr.t = time.ticks_ms()
        rpm = frq*10000 # (ms to s) 1000 * (s to min) 60 / (3 times per rotaion) 3
        tft.text((15, 75), "RPM: "+str(int(rpm))+"                        ", TFT.WHITE, sysfont, 1, nowrap=True) 
