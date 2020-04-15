# pip3 install pyserial pysolar
# will be used in conjunction with pysolar to send results to Arduino to operate the rotation of motor

import serial
import sys
import time
from pysolar.solar import *
import datetime

# sometimes the arduino will be listed as a different device
try:
  arduino = serial.Serial('/dev/ttyACM0', 115200)
except:
  arduino = serial.Serial('/dev/ttyACM1', 115200)

arduino.flushInput()

date = datetime.datetime.now(datetime.timezone.utc)
# accept opCode as argument
opCode = str(sys.argv[1])
altitude = int(float(get_altitude(32.448, -81.780, date)))
azimuth = int(float(get_azimuth(32.448, -81.780, date)))

if (altitude<0):
  altitude = "000"
if (altitude>70):
  altitude = "070"

if (azimuth < 0):
  azimuth += 360

azimuth = str(azimuth)
altitude = str(azimuth)

while(len(altitude)<3):
  altitude = "0" + altitude
while(len(azimuth)<3):
  azimuth = "0" + azimuth

print("opCode:",opCode)
print("azimuth:",azimuth)
print("altitude:",altitude)

message = opCode+azimuth+altitude # +encoderPos

while(True):
  s = arduino.readline()
  s = s.strip()
  if (s.decode("utf-8") == "<Arduino is ready>"):
    arduino.write(message.encode())
    break