#https://github.com/boochow/MicroPython-ST7735
from ST7735 import TFT
from machine import SPI,Pin
from sysfont import sysfont
import time
import math
spi = SPI('X', baudrate=20000000, polarity=0, phase=0) #X rail SPI; SCK and MOSI only
tft=TFT(spi,'X4','X3','X5') #DC, reset, CS
tft.initr()
tft.rgb(True) 
