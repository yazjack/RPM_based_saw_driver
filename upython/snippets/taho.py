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

t = time.ticks_ms()
tdt = 1

hallPin = pyb.Pin('Y1')

def truncate(n, decimals):
    multiplier = 10 ** decimals
    return int(n * multiplier) / multiplier

def clbHall(v):
    global t
    global tdt
    tdt = time.ticks_diff(time.ticks_ms(), t)
    t = time.ticks_ms()

hall = ExtInt(hallPin, ExtInt.IRQ_RISING, Pin.PULL_NONE, clbHall)
    
def RPM(deltaTime):
    frq = 1/deltaTime
    rpm = frq*20000 # (ms to s) 1000 * (s to min) 60 / (3 times per rotaion) 3
    tft.text((15, 75), "Angle: "+str(truncate(rpm, 1))+" ", TFT.WHITE, sysfont, 1, nowrap=True)

def main():
    RPM(tdt)

while 1:
    main()

