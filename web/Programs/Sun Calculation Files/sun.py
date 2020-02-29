# pip3 install pyserial
# will be used in conjunction with pysolar to send results to Arduino to operate the rotation of motor
from pysolar.solar import *
import datetime
import serial
import time

arduino = serial.Serial('/dev/ttyACM0', 9600)

date = datetime.datetime.now(datetime.timezone.utc)
azimuth = get_altitude(32.448, -81.780, date)		# Statesboro coordinates
altitude = get_azimuth(32.448, -81.780, date)		# (32.448, -81.780)

arduino.write(b'%d' %azimuth)		# send azimuth to arduino
time.sleep(1)				# give arduino time to receive and process and store azimuth
arduino.write(b'%d' %altitude)		# send altitude to arduino