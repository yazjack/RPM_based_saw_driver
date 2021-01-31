import interrupts as itr
import definitions as df
from ST7735 import TFT
from sysfont import sysfont

def mainMenuLayout():
    df.tft.fill(TFT.BLACK)
    left_margin = 15
    h = 5
    df.tft.text((left_margin, h), "MAIN MENU", TFT.GRAY, sysfont, 1, nowrap=True)
    h += sysfont["Height"]
    df.tft.text((left_margin, h), "Choose stock type", TFT.WHITE, sysfont, 1, nowrap=True)
    h += sysfont["Height"]
    df.tft.text((left_margin, h), "Choose stock size", TFT.WHITE, sysfont, 1, nowrap=True)
    h += sysfont["Height"]
    df.tft.text((left_margin, h), "Stock ammount", TFT.WHITE, sysfont, 1, nowrap=True)
    h += sysfont["Height"]
    df.tft.text((left_margin, h), "Valve o/c", TFT.WHITE, sysfont, 1, nowrap=True)
    h += sysfont["Height"]
    df.tft.text((left_margin, h), "Start cutting", TFT.WHITE, sysfont, 1, nowrap=True)
    h += sysfont["Height"]
    
def menuPointer(minValue, maxValue):
    left_margin = 5
    if itr.encoderPos <= maxValue and itr.encoderPos >= minValue:
        h = 5 + itr.encoderPos*sysfont["Height"]
        df.tft.text((left_margin, h), "*", TFT.RED, sysfont, 1, nowrap=True) 
        df.tft.text((left_margin, h-sysfont["Height"]), "*", TFT.BLACK, sysfont, 1, nowrap=True)
        df.tft.text((left_margin, h+sysfont["Height"]), "*", TFT.BLACK, sysfont, 1, nowrap=True)
    elif itr.encoderPos >= maxValue:
        itr.encoderPos = maxValue
    elif itr.encoderPos <= minValue:
        itr.encoderPos = minValue
    #print('Encoder @ position ',itr.encoderPos)
    
def rotaryMenu():
    itr.oldEncPos
    if  itr.oldEncPos != itr.encoderPos:
        itr.oldEncPos = itr.encoderPos 
