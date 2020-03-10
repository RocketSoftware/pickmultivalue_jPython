import math
from decimal import Decimal
def distance_between_points(lat1, long1, lat2, long2):
  lat1 = Decimal(lat1)
  lat2 = Decimal(lat2)
  long1 = Decimal(long1)
  long2 = Decimal(long2)
# Convert latitude and longitude to
# spherical coordinates in radians.
  radius = 6378 # kilometres or 3960 miles
  dlat = math.radians(lat2-lat1)
  dlon = math.radians(long2-long1)
  a = math.sin(dlat/2)*math.sin(dlat/2) + math.cos(math.radians(lat1)) \
  * math.cos(math.radians(lat2)) * math.sin(dlon/2) * math.sin(dlon/2)
  c = 2 * math.atan2(math.sqrt(a), math.sqrt(1-a))
  d = radius * c
  return d
