# pip3 install pyserial
# will be used in conjunction with pysolar to send results to Arduino to operate the rotation of motor

import serial
import sys
import time
from pysolar.solar import *
import datetime

arduino = serial.Serial('/dev/ttyACM0', 9600)
date = datetime.datetime.now(datetime.timezone.utc)

opCode = int(sys.argv[1])
altitude = int(get_altitude(32.448, -81.780, date))
#azimuth = int(get_azimuth(32.448, -81.780, date))
azimuth = int(90)



if __name__ == '__main__':


  ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
  ser.flush()

  ser.write(b"%d\n" %opCode)
  time.sleep(2)
  line = ser.readline().decode('utf-8').rstrip()
  #line = ser.readline().rstrip()
  print("opCode:",line)
  ser.write(b"%d\n" %azimuth)
  time.sleep(2)
  line = ser.readline().decode('utf-8').rstrip()
  #line = ser.readline().rstrip()
  print("azimuth:",line)
  ser.write(b"%d\n" %altitude)
  time.sleep(2)
  line = ser.readline().decode('utf-8').rstrip()
  #line = ser.readline().rstrip()
  print("altitude:",line)
  line = ser.readline().decode('utf-8').rstrip()
  time.sleep(2)