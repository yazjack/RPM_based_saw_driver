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

cntA = 0
cntB = 0
cntBtn = 0

def clbEncA(self):
    print("intr A")
    #cntA += 1
    #print(cntA)
def clbEncB(self):
    print("intr B")
    #cntB += 1
    #print(cntB)
def clbEncBtn(v):
    global cntBtn
    #print("intr btn")
    cntBtn += 1
    print(cntBtn)

encA = ExtInt(Pin('Y1'), ExtInt.IRQ_RISING, Pin.PULL_UP, clbEncA)
encB = ExtInt(Pin('Y3'), ExtInt.IRQ_RISING, Pin.PULL_UP, clbEncB)
encBtn = ExtInt(Pin('Y2'), ExtInt.IRQ_RISING, Pin.PULL_UP, clbEncBtn)

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

def main():
    tft.fill(TFT.BLACK)
    mainMenuLayout()

main()
