#---------------------------------------------------------------------
# Program to parce ALTA altimiter data 
#---------------------------------------------------------------------
# Author:  Todd Lines
# Date:    2023-07-01
#########################################################
import numpy as np
import matplotlib.pyplot as plt
#from scipy.optimize import curve_fit
from datetime import datetime
import re

#  Here is where you read in the altimitor data

Atdata = []
Aadata = []
Atsec = []



print("Reading File and parcing data")

for i in range(37):
    filenumber=str(i)
    if len(filenumber)<2:
       filenumber="0"+filenumber
    file_to_open = "C:\\Users\\rtlines\\Documents\\GPSLOG"+filenumber+".TXT"
    #print(file_to_open)

    file = open(file_to_open)
    for line in file.readlines():
        line = line.strip().strip('\n)')
        if line:
           data = line.split(",")
           #print(len(data))
           if (len(data)==12):
              #print(data)
              temp =  data[0].split(":")
              if (len(temp)==3):
                  #print("test temp ",temp)
                  hour = temp[0]
                  minute = temp[1]
                  second = temp[2]
                  #print(hour)
                  date = data[1]
                  #print(date)
                  Alt = float(data[10].strip(' Altitude:'))
                  #print(Alt)
                  if (date == " Date: 1/7/23"):
                      if ((hour != "") and (second != "") and (second != "")):
                          tss= float(hour)*3600+float(minute)*60+float(second)
                          # Only collect data from the launch to landing
                          if ((tss <= 59966) and (tss >=52694)):
                               Atdata.append(data[0])
                               Aadata.append(Alt)
                               Atsec.append(str(tss))
              #   print(" date =" + date+time+Alt
    file.close()

print("Data parced convert to arrays")

At=np.array(Atdata)
Aa=np.array(Aadata)
tsec=np.array(Atsec)
tflight=[]
print(tsec[0])
for i in range(len(tsec)):
    temp=(float(tsec[i]))-float(tsec[0])
    tflight.append(str(temp))

#At=At-At[0]
#print(At)
#print(Aa)
plotgraph='FALSE'
if (plotgraph=='TRUE'):
   print("Plot graph")
   plt.xlabel('Time [seconds]')
   plt.ylabel('Altitude in meters')
   plt.errorbar(tflight, Aa)
   plt.show()

print("Output file")
output_file = open("C:\\Users\\rtlines\\Documents\\Altimiter_data.TXT","w")
for i in range (len(At)):
    #output_string = At[i]+','+str(tsec[i])+','+str(Aa[i])+"\n"
    output_string = str(tsec[i])+','+str(Aa[i])+"\n"
    print(output_string)
    output_file.write(output_string)
output_file.close()
print("done")

