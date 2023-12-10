# Untitled - By: user - Ср июн 7 2023

import sensor, image, time
from pyb import Pin, I2C

p_out0 = Pin('P0', Pin.OUT_PP)
p_out1 = Pin('P1', Pin.OUT_PP)
p_in1 = Pin('P2', Pin.IN)

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.HVGA)
sensor.skip_frames(time = 1000)
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False)
clock = time.clock()
#thresholds = [(  70,  110, -40, 0,  30,  90), (30, 70, -40, 0, 30, 70)]
thresholds = [(  10,  50, 40, 80,  -100,  -70), (10, 50, -10, 30, -60, -20)]
signals = [0, 0]


while(True):
    clock.tick()
    img = sensor.snapshot()
    blob_list = img.find_blobs(thresholds, pixels_threshold=200, area_threshold=200, merge=True, margin=10)
    clock.tick()



    for b in blob_list:
        img.draw_rectangle(b.rect(), color=(0,255,0), thickness=2)
        img.draw_cross(b.cx(), b.cy(), color=(0,255,0), thickness=2)

        #print(b.cx())
        if b.cx() <= 180:
           signals[0] = 1
           p_out0.high()
           p_out1.low()
        elif b.cx() >= 300:
           signals[1] = 1
           p_out1.high()
           p_out0.low()
        else:
            signals[0] = 1
            signals[1] = 1
            p_out0.high()
            p_out1.high()
   # print(str(signals))
    if signals[0] == 0 and signals[1] == 0:
        p_out0.low()
        p_out1.low()
    signals[0] = 0
    signals[1] = 0

