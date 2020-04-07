# pip3 install pyserial
# will be used in conjunction with pysolar to send results to Arduino to operate the rotation of motor

import serial
import sys
import time
from pysolar.solar import *
import datetime

arduino = serial.Serial('/dev/ttyACM0', 9600)
date = datetime.datetime.now(datetime.timezone.utc)

opCode = str(sys.argv[1])
altitude = str(int(get_altitude(32.448, -81.780, date)))
azimuth = str(int(get_azimuth(32.448, -81.780, date)))

if (int(altitude) < 10):
  altitude = ("00"+altitude)
if (int(altitude)>10 and int(altitude)<100):
  altitude = ("0"+altitude)
if (int(azimuth) < 10):
  azimuth = ("00"+azimuth)
if (int(altitude)>10 and int(azimuth)<100):
  azimuth = ("0"+azimuth)

print("opCode:",opCode)
print("azimuth:",azimuth)
print("altitude:",altitude)

message = opCode+azimuth+altitude+"\r"
print(message)
arduino.write(message.encode())