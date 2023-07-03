#---------------------------------------------------------------------
# Program to parce ALTA altimiter data 
#---------------------------------------------------------------------
# Author:  Todd Lines
# Date:    2023-07-01
#########################################################
import matplotlib.pyplot as plt

###########################################################################
def plotdata(xdata, ydata, x_label, y_label):
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

# I looked at the data and found the launch and landing times in 
#   seconds since midnight. You might want to limit the output to just 
#   the flight, ignoring the setup time before launch and the time 
#   the payload is on the ground before we find it and turn off the altimiter.
#   If so, look for the launcha nd landing times and pPut them here along 
#   with the flag to say you want to limit the output.

t_land = 59966
t_launch = 52694
limit_flag = 'TRUE'
#limit_flag = 'FALSE'

# A graph of the data is nice to see, but it takes a long time to make
#  Set the following flag to "TRUE" if you want to see the graph
plotgraph='TRUE'


#  Here is where you read in the altimitor data
# Make a place to put the data
Atdata = []   # Altimiter time stamp
Aadata = []   # Altitude string
Andata = []   # Altitude converted to a float
Atsec = []    # Time stamp converted to seconds since midnight
tflight=[]    # String value for the time stamp in seconds starting with
              #    launch being zero
tnflight=[]   # numeric form of tflight

# We will use the time stamp in seconds since midnight to interpolate
#  the sensor data points to an altitude by noting wich two altitude
#  time stamps the sensor points fall between. To do this, it is easier
#  to have a single nuber for the time stamp.  So I build one, the 
#  number of seconds since midnight. 

print("Reading File and parcing data")

# The altimiter puts the altutude data into many files. The idea is to
#   guard against files being corrupted.  If one file is corrupted
#   the others should still be fine, so you won't lose all yor data.
#   We need to read in the many files.  The files are named GPSLOGXX.TXT
#   where the XX is a number.  They are numbered sequentially.
#
# Number of files for this run
N_files = 37
for i in range(N_files):
    # Build the file name for the next file to open
    filenumber=str(i)
    if len(filenumber)<2:
       filenumber="0"+filenumber
    file_to_open = "C:\\Users\\rtlines\\Documents\\GPSLOG"+filenumber+".TXT"

    # Open the file and read the data   
    file = open(file_to_open)
    for line in file.readlines():
        line = line.strip().strip('\n)')     # get rid of line endings
        if line:                             # if the line isn't blank
           data = line.split(",")            # break it appart at the commas
           if (len(data)==12):               # there should be 12 pieces
              #print(data)                   # if there arn't skip the line
              temp =  data[0].split(":")     # the first part is the time
              if (len(temp)==3):             # split at the ":" chars
                  hour = temp[0]             # the order is h m s
                  minute = temp[1]
                  second = temp[2]
                  #print(hour)
                  date = data[1]             # next is the date
                  #print(date)
                  Alt = float(data[10].strip(' Altitude:')) # get the altitude
                  #We only want data from this flight. Check the dates
                  if (date == " Date: 1/7/23"):
                      # Now make sure the whole time stamp was printed,
                      #   Skip the line if it wasn't
                      if ((hour != "") and (second != "") and (second != "")):
                          # Calculate time since midnight it seconds
                          tss= float(hour)*3600+float(minute)*60+float(second)
                          # I looked at the data and found the time for the 
                          #   launch and landing. If limit_flag = 'TRUE'
                          #   Only collect data from the launch to landing. 
                          #   Numbers are given above. Otherwise, output
                          #   all the data.
                          if (limit_flag == 'TRUE'):
                              if ((tss <= t_land) and (tss >=t_launch)):
                                  Atdata.append(data[0])
                                  Aadata.append(Alt)
                                  Andata.append(float(Alt))
                                  Atsec.append(str(tss))
                          else:
                              Atdata.append(data[0])
                              Aadata.append(Alt)
                              Andata.append(float(Alt))
                              Atsec.append(str(tss))
                              
    # Close the file
    file.close()

print("Data parced ")

# for some reason I wanted a set of times in seconds where zero was the 
#  launch time. I guess it makes the plot look nice
for i in range(len(Atsec)):
    temp=(float(Atsec[i]))-float(Atsec[0])
    tflight.append(str(temp))
    tnflight.append(temp)

# Graph the data if the plotgraph flag is set above
if (plotgraph=='TRUE'):
   print("Plot graph")
   xdata=tnflight
   x_label='Time [seconds]'
   ydata=Andata
   y_label ='Altitude in meters'
   plotdata(xdata, ydata, x_label, y_label)


print("Output file")
output_file = open("C:\\Users\\rtlines\\Documents\\Altimiter_data.TXT","w")
for i in range (len(Atsec)):
    #output_string = At[i]+','+str(tsec[i])+','+str(Aa[i])+"\n"
    output_string = str(Atsec[i])+','+str(Aadata[i]) +"\n"
    print(output_string)
    output_file.write(output_string)
output_file.close()
print("done")

