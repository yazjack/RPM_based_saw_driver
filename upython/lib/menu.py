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
        h = 10
        for item in self.arg:
            df.tft.text((left_margin, h), item, TFT.WHITE, sysfont, 1, nowrap=True)
            h += sysfont["Height"]

    def menuPointer(self):
        global left_margin
        margin = left_margin -10
        if itr.encoderPos <= self.menuMax and itr.encoderPos >= self.menuMin:
            h = 10 + itr.encoderPos*sysfont["Height"]
            df.tft.fillrect([margin, sysfont["Height"]+10], [sysfont["Width"], sysfont["Height"]*self.menuMax], TFT.BLACK)
            df.tft.text((margin, h), "*", TFT.RED, sysfont, 1, nowrap=True) 
            #print(itr.encoderPos)
        elif itr.encoderPos >= self.menuMax:
            itr.encoderPos = self.menuMax
        elif itr.encoderPos <= self.menuMin:
            itr.encoderPos = self.menuMin
