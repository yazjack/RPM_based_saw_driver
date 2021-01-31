#https://github.com/boochow/MicroPython-ST7735
from ST7735 import TFT
from sysfont import sysfont
from pyb import ExtInt, Pin
import math
import pins as pn
import interrupts as itr
import definitions as df
import menu as mu

mu.mainMenuLayout()

def main():
    mu.menuPointer(1,5)
    mu.rotaryMenu()
    df.RPM()
    df.armAngleRead(itr.cntAngleEnc)


while 1:
    main()

