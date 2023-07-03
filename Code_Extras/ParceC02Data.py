#---------------------------------------------------------------------
# Program to parce CO2 data 
#---------------------------------------------------------------------
# Author:  Todd Lines
# Date: 2023-07-03
#########################################################
import numpy as np
import matplotlib.pyplot as plt
#from scipy.optimize import curve_fit
#from datetime import datetime
#import re

#  Here is where you read in C02 data

Ctdata = []
Ccdata = []
Ctsec = []



print("Reading File and parcing data")

file_to_open = "C:\\Users\\rtlines\\Documents\\CO2DATA_last_part.TXT"
file = open(file_to_open)
for line in file.readlines():
    print(line)
    line = line.strip().strip('\n')
    line = line.strip().strip('Day 1- ')
    print(line)
    if line:
       data = line.split(",")
       print(data)
       if (len(data)==5):
          temp =  data[0].split(":")
          if (len(temp)==3):
             print("test temp ",temp)
             hour = temp[0]
             minute = temp[1]
             second = temp[2]
             if ((hour != "") and (second != "") and (second != "")):
                tss= float(hour)*3600+float(minute)*60+float(second)
                # Only collect data from the launch to landing
#                if ((tss <= 59966) and (tss >=52694)):
                Ccdata.append(data[1])
                Ctdata.append(data[0])
                Ctsec.append(str(tss))
#              #   print(" date =" + date+time+Alt
file.close()

print(Ctsec)
print(len(Ctsec))
print("Data parced convert to arrays")

Ct=np.array(Ctdata)
Cc=np.array(Ccdata)
tsec=np.array(Ctsec)
tflight=[]
stflight=[]
print(Ctsec[0])
for i in range(len(Ctsec)):
    temp=(float(Ctsec[i]))-float(Ctsec[0])
    tflight.append(temp)
    stflight.append(str(temp))
    print(tflight[i],Cc[i])


#ct=Ct-Ct[0]
#print(At)
#print(Aa)

print("Plot graph")
#Calculate x-tics
x_t_max=max(tflight)
x_t_min=min(tflight)
x_t_inc=(x_t_max-x_t_min)/10
x_t=[0]
x_t_len =int( (x_t_max-x_t_min)%10)
for i in range(1, x_t_len):
    temp = x_t[-1]+x_t_inc
    x_t.append(temp)
x_ticks = x_t
#calculate y tics
ccn=[]
for i in range(len(Cc)):
    ccn.append(float(Cc[i]))
y_t_max=max(ccn)
y_t_min=min(ccn)
y_t_inc=(y_t_max-y_t_min)/5
y_t=[0]
y_t_len =int((y_t_max-y_t_min)/y_t_inc)

for i in range(1, y_t_len):
    temp = y_t[-1]+y_t_inc
    y_t.append(temp)
y_ticks = y_t
plt.xlabel('Time [seconds]')
plt.ylabel('CO2 in ppm')
plt.errorbar(tflight, ccn)
plt.show()

print("Output file")
#output_file = open("C:\\Users\\rtlines\\Documents\\Altimiter_data.TXT","w")
#for i in range (len(At)):
#    output_string = str(At[i])+", "+str(tsec[i])+","+str(tflight[i])+','+str(Aa[i])+"\n"
#    print(tsec[i])
#    output_file.write(output_string)
#output_file.close()
#print("done")

