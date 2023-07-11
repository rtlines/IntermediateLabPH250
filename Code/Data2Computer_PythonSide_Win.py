#---------------------------------------------------------------------
# Python Code to read a stream of data from the serial port
#   and save it to a file
#---------------------------------------------------------------------
#   The idea is to read a series of voltages from an Arduino 
#   connected to the serial port where the Arduino is being 
#   used as the Analog to Digital converter. Both the voltage
#   and the time the voltage was taken are sent to the serial port.
#
# We will use two libraries, serial and time
#   The serial library is used to read the serial port
#   The time library is used to space out our data collection by
#   adding a delay in between data points. The amount of time 
#   to wait in between data points is called "timeBetween." 
#
# We may have to install the serial library. If you have the
#   Anaconda Python for Windows, you can open an Anaconda 
#   window and use the command 'conda install pyserial'
#   This must be done before the code can run.
#
# Debugging issues:  The Anaconda Python distribution tends to 
#   hang on to the serial port even if the program does not run. 
#   If this happens, try sending the python command ser.close()
#   at the command prompt. If this doesn't work, You may have to 
#   restart Python.
#   In windows, closing (after saving) the IDE and reopening it 
#   might be enough.
#---------------------------------------------------------------------
# import libraries
import serial
import time
 
# define variables for the delay time we wait between data points
timeBetween=5 #seconds
 
# define the number of data points to collect
N=20
 
#the next line opens a file and creates a pointer or handle for that file
#  to use as a reference. You have to use double slashes in the path.
#  The pointer, "dataFile" takes the place of all the path and file
#  name so it is easier to use in the code below
#  This line worked for Brother Lines, but won't work for you as it is.
#  You need to replace "rtlines" with your username at a minimum.
dataFile=open('C:\\Users\\rtlines\\Documents\\data3.txt','w')
 
#the next line opens the serial port for communication. You need to 
#  set the COM port based on where the Arduino IDE says the Arduino
#  is plugged into your computer. On Windows, this is usually COM1 
#  through COM 8.
ser=serial.Serial('COM6', baudrate = 9600, timeout=1)
 
#there will be a delay before the first data point comes from the 
#  serial port, warn the user so they don't worry.
print('\n getting started...\n')
 
# set our index to zero
i=0
 
 
# Now for N points (set above), collect data and write it to a file
while (i<N):    #Begin data collection loop
    #We will take data every "timeBetween" seconds. We need to know 
    #   when we start waiting so we can tell if it is time to collect 
    #   data yet. Use the time.time() to get the current time in seconds
    #   since Jan 1,1970. Yes that is a weird way to measure time, but 
    #   computers do it this way.
    waitStart=time.time()
    
    #Data comes to the serial port fast. We will continually read 
    #  the data as fast as it comes, but only save it every timeBetween
    #  seconds. The next while loop keeps us reading in data, but only 
    #  when the current time - waitStart >= timeBetweem will we use 
    #  the data. All the data points inbetween get thrown away.
    while (time.time()-waitStart<timeBetween): #Begin Data read loop
         # Get data from the serial port
         # it should have a time and a voltage
         arduinoData=ser.readline().decode('ascii')
         # end of the Data read loop
         
    # the next line just prints the time and voltageon the console 
    #   so the user feels like something is happening.
    print(arduinoData)
    # This next line makes sure our Arduino data is in a python 
    #   string format
    writeString=str(arduinoData) #+ " \n"
    # The next line writes our Arduino data value to the file.
    dataFile.write(writeString)
    # And finely we increment the loop counter so we can see if we have 
    #  collected data N times adnd are ready to quit.
    i=i+1      # end Data collection loop   
    
# Print out a message saying we are done
print("done with data collection, closing the  file and the serial port")
# Close the file
dataFile.close()
# Close the serial port   
ser.close() 
#---------------------------------------------------------------------
#---------------------------------------------------------------------