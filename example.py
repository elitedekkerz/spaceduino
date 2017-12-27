#!/usr/bin/env python3
import json
import serial

import logging

ser = serial.Serial('/dev/ttyUSB0',115200)
ser.timeout = 1
status = ''


while True:
    try:
        #get status
        ser.write('\n'.encode('utf-8'))
        status = json.loads(ser.readline().decode('utf-8'))
        print(status)

        #set all outputs low
        outArray = []
        for output in status['outputs']:
            outArray.append(0)
        ser.write((str(outArray)+'\n').encode('utf-8'))

        #proove that the outputs went low
        print(json.loads(ser.readline().decode('utf-8')))
        break;
    except:
        pass
