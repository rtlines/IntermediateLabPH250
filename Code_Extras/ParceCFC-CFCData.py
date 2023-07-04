#---------------------------------------------------------------------
# Program to parce CFC data from CFC group
#---------------------------------------------------------------------
# Author:  Todd Lines
# Date: 2023-06-03
#########################################################
# Same code as the CFC Group CO2 Sensor data parcer because the 
#  group used the same data format.
###########################################################################
import matplotlib.pyplot as plt


###########################################################################
#Function to make the plot in a pretty way
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
# Main Parcer Code
###########################################################################
#  Here is where you read in C02 data
#  First let's make a place for it
Ctdata = []   # space for CO2 tiem stamp
CFCdata = []  # space for the Co2 data itself
Ctsec = []    # space for the time stamp converted to seconds as a string
tflight=[]    # space fosr the time stamp in seconds but as a number
print("Reading File and parcing data")

file_to_open = "C:\\Users\\rtlines\\Documents\\CFC_CFCDATA.TXT"
file = open(file_to_open)
# We are going to read in the lines one at a time
for line in file.readlines():
    line = line.strip().strip('\n') # Take out end of line characters
    if line:    # check to see if the line is blank
       data = line.split(",")  # if it has data, split it at the "," characters
       #print(data)
       if (len(data)==2):      # check to see that we got a data and CO2ppm
          temp =  data[0].split(" ")  # first part is time, split at the space
          date=temp[0]         # now date is in first part of split
          time=temp[1].split(":")  #time is in second part, split again at ":"       
          if (len(time)==3):   # check to make sure we got h m s
             #print("test temp ",temp)
             hour = time[0]    # first part is hour
             minute = time[1]  # second part is minuts
             second = time[2]  # third part is seconds
             # if we got all the parts, calculate the number of seconds
             #   that have passed since midnight until this time.  We
             #   will use this number to match to the altimiter
             if ((hour != "") and (second != "") and (second != "")):
                tss= float(hour)*3600+float(minute)*60+float(second)
                # put the CO2 data into CCdata and the time into Ctsec
                CFCdata.append(data[1].strip(" ppm"))
                Ctdata.append(data[0]) # the whole time stamp
                Ctsec.append(str(tss)) # just the time, but as a string
                tflight.append(tss)
# Close the CO2 File
file.close()
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
    atime.append(float(data[0])-sixhours)
    aalt.append(float(data[1]))
afile.close()

#try to match CO2 data to altitude
#Turn the CO2 data into a number as we go

cppm=[]  # CO2 data as a number
calt=[]  # the interpolated altitude for our CO2 data

for i in range(0,len(CFCdata)):
    for j in range(1,len(atime)-1):
        if (tflight[i]>atime[j-1]) and (tflight[i]<atime[j]):
            tpercent=(tflight[i]-atime[j-1])/(atime[j]-atime[j-1])
            calt.append((aalt[j]-aalt[j-1])*tpercent+aalt[j-1])
            cppm.append(float(CFCdata[i]))
            break

print("Plot graph")
printgraph="TRUE"
if (printgraph == "TRUE"):
    xdata=calt
    x_label="Altitude(m)"
    ydata=cppm
    y_label = "CFC ppm"
    # I want my data plotted with the altitude on the y-axis because
    #  I have studied meterology. You might want your altitude on the 
    #  x-axis.  If so, uncomment out the first line and coment out the 
    #  second.
    #plotdata(xdata, ydata, x_label, y_label)
    plotdata(ydata, xdata, y_label, x_label)


print("Output file")
output_file = open("C:\\Users\\rtlines\\Documents\\CFC_Group_CO2_data.TXT","w")
for i in range (len(calt)):
    output_string = str(calt[i])+','+str(cppm[i])+"\n"

    output_file.write(output_string)
output_file.close()

# and we are finished!
print("done")

