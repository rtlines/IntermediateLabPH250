#---------------------------------------------------------------------
# Program to parce CO2 data from CFC group
#---------------------------------------------------------------------
# Author:  Todd Lines
# Date: 2023-07-03
#########################################################
import matplotlib.pyplot as plt
#from scipy.optimize import curve_fit
#from datetime import datetime
#import re

###########################################################################
def plotdata(xdata, ydata, x_label, y_label):
    if (printgraph == "TRUE"):
        #Calculate x-tics
        x_t_max=max(xdata)
        x_t_min=min(xdata)
        x_t_inc=(x_t_max-x_t_min)/10
        x_t=[0]
        x_t_len =int( (x_t_max-x_t_min)%10)
        for i in range(1, x_t_len):
            temp = x_t[-1]+x_t_inc
            x_t.append(temp)
            x_ticks = x_t
            #calculate y tics
            y_t_max=max(ydata)
            y_t_min=min(ydata)
            y_t_inc=(y_t_max-y_t_min)/5
            y_t=[0]
            y_t_len =int((y_t_max-y_t_min)/y_t_inc)

        for i in range(1, y_t_len):
            temp = y_t[-1]+y_t_inc
            y_t.append(temp)
            y_ticks = y_t
            plt.xlabel(x_label)
            plt.ylabel(y_label)
            plt.errorbar(xdata, ydata)
            plt.show()

###########################################################################
###########################################################################
#  Here is where you read in C02 data
#  First let's make a place for it
#  Here is where you read in C02 data

Ctdata = []   # space for CO2 tiem stamp
CO2data = []  # space for the Co2 data itself
Ctsec = []    # space for the time stamp converted to seconds as a string
tflight=[]    # space fosr the time stamp in seconds but as a number

print("Reading File and parcing data")

file_to_open = "C:\\Users\\rtlines\\Documents\\CO2DATA_last_part.TXT"
file = open(file_to_open)
for line in file.readlines():
    #print(line)
    line = line.strip().strip('\n')
    line = line.strip().strip('Day 1- ')
    #print(line)
    if line:
       data = line.split(",")
       #print(data)
       if (len(data)==5):
          temp =  data[0].split(":")
          if (len(temp)==3):
             #print("test temp ",temp)
             hour = temp[0]
             minute = temp[1]
             second = temp[2]
             if ((hour != "") and (second != "") and (second != "")):
                tss= float(hour)*3600+float(minute)*60+float(second)
                CO2data.append(data[1])
                Ctdata.append(data[0])
                Ctsec.append(str(tss))
                tflight.append(tss)
                #print(tss, data[1])
file.close()

#print(Ctsec)
print(len(Ctsec))
print("Data parced convert to arrays")


print("Data parced ")

# Bring in the Altimiter data
#It turns out the altimiter data is in UTC so we have to subtract off 6 hours
sixhours = 6*3600
print("bring in altimiter data")
atime=[]   # space for the altitimeter time
aalt=[]    # space for the altimiter value
file_to_open  = "C:\\Users\\rtlines\\Documents\\Altimiter_data.TXT"
afile = open(file_to_open)
for line in afile.readlines():
    data = line.split(",")
    print(data[0], float(data[0])-sixhours)
    atime.append(float(data[0])-sixhours)
    aalt.append(float(data[1]))
afile.close()

#try to match CO2 data to altitude
#Turn the CO2 data into a number as we go

cppm=[]  # CO2 data as a number
calt=[]  # the interpolated altitude for our CO2 data
print(min(atime), max(atime), min(tflight), max(tflight))
for i in range(0,len(CO2data)):
    for j in range(1,len(atime)-1):
        if (tflight[i]>atime[j-1]) and (tflight[i]<atime[j]):
            tpercent=(tflight[i]-atime[j-1])/(atime[j]-atime[j-1])
            calt.append((aalt[j]-aalt[j-1])*tpercent+aalt[j-1])
            cppm.append(float(CO2data[i]))
            break

print(len(calt))
print("Plot graph")
printgraph="TRUE"
if (printgraph == "TRUE"):
    xdata=calt
    x_label="Altitude(m)"
    ydata=cppm
    y_label = "CO2 ppm"
    # I want my data plotted with the altitude on the y-axis because
    #  I have studied meterology. You might want your altitude on the 
    #  x-axis.  If so, uncomment out the first line and coment out the 
    #  second.
    #plotdata(xdata, ydata, x_label, y_label)
    plotdata(ydata, xdata, y_label, x_label)


print("Output file")
output_file = open("C:\\Users\\rtlines\\Documents\\CO2_Group_Processed_CO2_data.TXT","w")
for i in range (len(calt)):
    output_string = str(calt[i])+','+str(cppm[i])+"\n"

    output_file.write(output_string)
output_file.close()

# and we are finished!
print("done")

