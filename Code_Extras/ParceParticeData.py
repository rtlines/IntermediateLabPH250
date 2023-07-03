#---------------------------------------------------------------------
# Program to parce particle counter data 
#---------------------------------------------------------------------
# Author:  Todd Lines
# Date:    2023-07-03
#########################################################
import matplotlib.pyplot as plt
#from scipy.optimize import curve_fit


#  Here is where you read in the altimitor data

Padata = []
nPadata = []
Ptsec = []
nPtsec = []
tflight=[]

print("Reading File and parcing data")

for i in range(5,82):
    filenumber=str(i)
    if len(filenumber)<2:
       filenumber="0"+filenumber
    file_to_open = "C:\\Users\\rtlines\\Documents\\LOGS\\LOG0"+filenumber+".TXT"
    print(file_to_open)

    file = open(file_to_open)
    for line in file.readlines():
        line = line.strip().strip('\n)')
        if line:
           data = line.split(",")
           #print(len(data))
           if (len(data)==4):
              #print(data)
              hour = data[0]
              minute = data[1]
              second = data[2]
              counts = data[3]
              if ((hour != "") and (second != "") and (second != "")):
                  tss= (float(hour)+8)*3600+float(minute)*60+float(second)
                  # Only collect data from the launch to landing
                  Padata.append(counts)
                  Ptsec.append(str(tss))
                  nPadata.append(float(counts))
                  nPtsec.append(float(tss))
                  print(tss,counts)
    file.close()

print("Data parced convert to arrays")

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

pcounts=[]  # CO2 data as a number
palt=[]  # the interpolated altitude for our CO2 data
tflight=nPtsec

for i in range(0,len(nPadata)):
    for j in range(1,len(atime)-1):
        if (tflight[i]>atime[j-1]) and (tflight[i]<atime[j]):
            tpercent=(tflight[i]-atime[j-1])/(atime[j]-atime[j-1])
            palt.append((aalt[j]-aalt[j-1])*tpercent+aalt[j-1])
            pcounts.append(float(Padata[i]))
            break

plotgraph='TRUE'
if (plotgraph=='TRUE'):
   print("Plot graph")
   plt.xlabel('Altitude [m]')
   plt.ylabel('counts')
   plt.errorbar(palt, pcounts )
   plt.show()