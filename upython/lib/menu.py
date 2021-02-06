import interrupts as itr
import definitions as df
from ST7735 import TFT
from sysfont import sysfont
left_margin = 15

class spawnMenu:
    def __init__(self, menuName, menuMin, menuMax, *arg):
        self.menuName = menuName
        self.menuMin = menuMin
        self.menuMax = menuMax
        self.arg = arg
        
    def menuDisplay(self):
        global left_margin
        df.tft.fill(TFT.BLACK)
        h = 5
        for item in self.arg:
            print(self.arg)
            df.tft.text((left_margin, h), item, TFT.WHITE, sysfont, 1, nowrap=True)
            h += sysfont["Height"]

    def menuPointer(self):
        global left_margin
        margin = left_margin -10
        if itr.encoderPos <= self.menuMax and itr.encoderPos >= self.menuMin:
            h = 5 + itr.encoderPos*sysfont["Height"]
            df.tft.text((margin, h), "*", TFT.RED, sysfont, 1, nowrap=True) 
            df.tft.text((margin, h-sysfont["Height"]), "*", TFT.BLACK, sysfont, 1, nowrap=True)
            df.tft.text((margin, h+sysfont["Height"]), "*", TFT.BLACK, sysfont, 1, nowrap=True)
        elif itr.encoderPos >= self.menuMax:
            itr.encoderPos = self.menuMax
        elif itr.encoderPos <= self.menuMin:
            itr.encoderPos = self.menuMin

def rotaryMenu():
    itr.oldEncPos
    if  itr.oldEncPos != itr.encoderPos:
        itr.oldEncPos = itr.encoderPos 
