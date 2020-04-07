# pip3 install pyserial
# will be used in conjunction with pysolar to send results to Arduino to operate the rotation of motor

import serial
import sys
import time
from pysolar.solar import *
import datetime

arduino = serial.Serial('/dev/ttyACM0', 115200)
File = open("encoderPos.txt","r")
arduino.flushInput()
date = datetime.datetime.now(datetime.timezone.utc)

opCode = str(sys.argv[1])
altitude = str(int(get_altitude(32.448, -81.780, date)))
azimuth = int(get_azimuth(32.448, -81.780, date))
if (int(azimuth) < 0):
  azimuth += 360
azimuth = str(azimuth)

#encoderPos = File.read()
#encoderPos = str(int(float(encoderPos)))
#print("encoderPos:",encoderPos)


if (int(altitude) < 10):
  altitude = ("00"+altitude)
if (int(altitude)>10 and int(altitude)<100):
  altitude = ("0"+altitude)
if (int(azimuth) < 10):
  azimuth = ("00"+azimuth)
if (int(altitude)>10 and int(azimuth)<100):
  azimuth = ("0"+azimuth)
#if (int(encoderPos) < 10):
#  encoderPos = "0000"+encoderPos
#if (int(encoderPos) > 10 and int(encoderPos) < 100):
#  encoderPos = "000"+encoderPos
#if (int(encoderPos) > 100 and int(encoderPos) < 1000):
#  encoderPos = "00"+encoderPos
#if (int(encoderPos) > 1000 and int(encoderPos) < 10000):
#  encoderPos = "0"+encoderPos

print("opCode:",opCode)
print("azimuth:",azimuth)
print("altitude:",altitude)
#print("encoderPos:",encoderPos)

message = opCode+azimuth+altitude # +encoderPos

while(True):
  s = arduino.readline()
  s = s.strip()
  if (s.decode("utf-8") == "<Arduino is ready>"):
    arduino.write(message.encode())
    break


#while(True):
#  s = arduino.readline()
#  s = s.strip()
#  if (s.decode("utf-8") == "<Encoder is ready>"):
#    print("encoder received")  
#    s = arduino.readline()
#    s = s.strip()
#    encoderPos = s.decode("utf-8")
#    break
#
#File = open("encoderPos.txt","w")
#File.write(encoderPos)