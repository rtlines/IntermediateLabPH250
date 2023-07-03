#---------------------------------------------------------------------
# Program to match altimiter data to sensor data using a time stamp
#---------------------------------------------------------------------
# Author:  Todd Lines
# Date:    
#########################################################
import numpy as np
import matplotlib.pyplot as plt
#from scipy.optimize import curve_fit
from datetime import datetime
import re

#  Here is where you read in the altimitor data

Atdata = []
Aadata = []

file =open("C:\\Users\\rtlines\\Documents\\Altimiter_data.csv")
for line in file.readlines():
    if(len(line)>3):   # remove blank lines
       #print(line)
       date =  line.split(',')[0]
       time = line.split(',')[1]
       Alt = line.split(',')[2]
       date = re.sub(r'[^\x00-\x7f]', "", date)  # remove extra chars
       #print(" date =" + date+time+Alt
       ts = (datetime.strptime(date+','+time, "%m/%d/%Y, %H:%M:%S"))
       #tm = (datetime.strptime(time, "%H:%M:%S"))
       tss= ts.hour*3600+ts.minute*60+ts.second
       Atdata.append(tss )

       Aadata.append( float(Alt) )
#        datetime.strptime("2020-01-01 14:00", "%Y-%m-%d %H:%M")

file.close()


At=np.array(Atdata)
Aa=np.array(Aadata)
At=At-At[0]
print(At)
print(Aa)


plt.xlabel('Time in seconds')
plt.ylabel('Altitude in meters')
plt.errorbar(At, Aa,  fmt='ro')
plt.show()


