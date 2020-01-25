# pip3 install pyserial
# will be used in conjunction with pysolar to send results to Arduino to operate the rotation of motor

import serial
import time

arduino = serial.Serial('/dev/ttyACM0', 9600)

integer = 259

# sends 259 to Arduino
arduino.write(b'%d' %integer)