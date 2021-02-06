#https://github.com/boochow/MicroPython-ST7735
from ST7735 import TFT
from sysfont import sysfont
from pyb import ExtInt, Pin
import math
import pins as pn
import interrupts as itr
import definitions as df
import menu as mu

mainMenuLayout = mu.spawnMenu('mainMenu', 0, 5, 'MAIN MENU', 'Choose stock type', 'Choose stock size', 'Stock ammount', 'Balade position', 'Start cutting')        
mainMenuLayout.menuDisplay()

def main():
    #mu.menuPointer(1,5)
    mainMenuLayout.menuPointer()
    mu.rotaryMenu()
    df.RPM()
    df.armAngleRead(itr.cntAngleEnc)


while 1:
    main()

