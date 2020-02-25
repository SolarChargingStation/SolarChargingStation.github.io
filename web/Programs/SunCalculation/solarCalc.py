from pysolar.solar import *
import datetime

date = datetime.datetime.now(datetime.timezone.utc)
print("Altitude:",get_altitude(32.448, -81.780, date))
print("Azimuth:",get_azimuth(32.448, -81.780, date))