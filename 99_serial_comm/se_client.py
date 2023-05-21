# -*- coding: utf-8 -*-
import serial



ser = serial.Serial("/dev/ttyS0", timeout = None)  # open first serial port

while True:
  inmsg = input()
  inmsg = inmsg + "\n"
  snd_size = ser.write(inmsg.encode('utf-8'))
  print("send size", snd_size)
  msg = ser.read(snd_size)
  print(msg)


ser.close()

