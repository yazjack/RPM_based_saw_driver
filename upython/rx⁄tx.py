from machine import UART
from pyb import Timer

uart = UART(6, 9600)
uart.init(9600, bits=8, parity=None, stop=1)
#i2c = I2C('Y', freq=115200)
#i2c.scan()

tm = Timer(4, freq=1)

def send(timer):
    uart.write('123')
    #i2c.writeto(4, b'1123')

tm.callback(send)
