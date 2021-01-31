import time
from machine import Pin

hallPin = pyb.Pin('X12')
hall = ExtInt(hallPin, ExtInt.IRQ_RISING, Pin.PULL_NONE, clbHall)

t = time.ticks_ms() #t = time.time()

def clbHall(n):
	global t
	dt = time.time_ms() - t
	if dt < 0.01: return

	freq = 1 / dt
	rpm = (freq / 2) * 60
	print "%.f" % (rpm,)
	t = time.time_ms()	

#while True: time.sleep(1e9)
