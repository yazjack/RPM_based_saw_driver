#https://github.com/boochow/MicroPython-ST7735
from ST7735 import TFT
from sysfont import sysfont
from pyb import ExtInt, Pin
import math
import pins as pn
import interrupts as itr
import definitions as df
import menu as mu

mainMenuLayout = mu.spawnMenu('mainMenu', 1, 5, 'MAIN MENU', 'Choose stock type', 'Choose stock size', 'Stock ammount', 'Balade position', 'Start cutting')
stockAmmountMenuLayout = mu.spawnMenu('stockAmmount', 1, 3, 'STOCK AMMOUNT', 'Hroizontal ammount', 'Vertical ammount', 'Back')
currentMenu = mainMenuLayout.menuName
mainMenuLayout.menuDisplay()

def main():
    global currentMenu
    if currentMenu == mainMenuLayout.menuName and itr.cntMenuBtn == 1:
        df.tft.fill(TFT.BLACK)
        mainMenuLayout.menuDisplay()
        itr.cntMenuBtn = 0
        currentMenu = mainMenuLayout.menuName
        
    if currentMenu == mainMenuLayout.menuName and itr.cntMenuBtn == 0:
        mainMenuLayout.menuPointer()
        df.RPM()
        df.armAngleRead(itr.cntAngleEnc)
        
    if currentMenu == mainMenuLayout.menuName and itr.encoderPos == 3:
        if itr.cntMenuBtn == 1:
            currentMenu = stockAmmountMenuLayout.menuName
            df.tft.fill(TFT.BLACK)
            itr.encoderPos = 1
            stockAmmountMenuLayout.menuDisplay()
            itr.cntMenuBtn = 0
            
    if currentMenu == stockAmmountMenuLayout.menuName and itr.cntMenuBtn == 0:
        stockAmmountMenuLayout.menuPointer()
    
    if currentMenu == stockAmmountMenuLayout.menuName and itr.encoderPos == 3:
        if itr.cntMenuBtn == 1:
            currentMenu = mainMenuLayout.menuName
            
while 1:
    main()

