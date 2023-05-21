import serial



ser = serial.Serial("/dev/ttyUSB0", timeout = None)  # open first serial port

while True:
  line = ser.read()          # read one byte
  #line = ser.readline()   # read a '\n' terminated line
  print(line)
  ser.write(line)

#snd_size = ser.write('hello I am here\n'.encode('utf-8'))      # write a string
#msg = ser.read(snd_size) #read the content of the input buffer until you get 100 byte o
#print(msg) #print the content you might need to decode it print(decode(msg))
ser.close()
