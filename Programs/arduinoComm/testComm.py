# pip3 install pyserial
# will be used in conjunction with pysolar to send results to Arduino to operate the rotation of motor

import serial
import time
from pysolar.solar import *
import datetime

arduino = serial.Serial('/dev/ttyACM0', 9600)
date = datetime.datetime.now(datetime.timezone.utc)

opCode = 1200

altitude = get_altitude(32.448, -81.780)
azimuth = get_azimuth(32.448, -81.780)

print(altitude)
print(azimuth)

arduino.write(b'%d' %opCode)
time.sleep(5)
arduino.write(b'%d' %altitude)
time.sleep(5)
arduino.write(b'%d' %azimuth)