import numpy as np
import matplotlib.pyplot as plt
import pathlib       #  For finding the silly file on Windows
import datetime

#path_name = r"C:\\Users\\rtlines\\OneDrive - BYU-Idaho\\BYUI-Synced\\CodeProjects\\Fridge\\LOGS\\"
path_name = r"C:\\Users\\rtlines\\OneDrive - BYU-Idaho\\BYUI-Synced\\CodeProjects\\Fridge\\"
file_name = r'Fridge_2023_03_23_2.TXT'

print("  ")


dates = []
temps = []
time = []

delta_time = 0.5  #minutes
t = 0

file_to_open = pathlib.Path(path_name+file_name)
print(file_name)
with open(file_to_open, mode='r') as fid:
     for line in fid:
         line_part_A  = line.split(',')[0]
         line_part_B  = line.split(',')[1]
         line_part_C  = line.split(',')[2]
         line_part_D  = line.split(',')[3]
         line_part_E  = line.split(',')[4]
         line_part_B = line_part_B.replace(" Temperature =","").replace("C","").strip()   
         temps.append(float(line_part_B))
         line_part_A=line_part_A.strip()
         dates.append(datetime.datetime.strptime(line_part_A,'%Y-%m-%d %H:%M:%S'))
         time.append(t)
         t = t + delta_time


tempC=np.array(temps)
tempf=(tempC* 9/5) + 32
time=np.array(time)
preferedTemp =  np.full(shape=(np.size(time)), fill_value=0)
MaxTemp =  np.full(shape=(np.size(time)), fill_value=10)
TooHighTemp = np.full(shape=(np.size(time)), fill_value=12)
print(max(tempf)) 
print(min(tempf))
print(np.mean(tempf))
print(max(dates))
print(min(dates))
print(max(dates)-min(dates))
plt.figure()
plt.xlabel("time in minutes")
plt.ylabel('temperature in deg F')

plt.plot(time,tempf)
plt.plot(time,preferedTemp,linestyle = 'dotted', color = 'g')
plt.plot(time,MaxTemp,linestyle = 'dotted',  color = 'r')
plt.plot(time,TooHighTemp,linestyle = 'dotted',  color = 'm')
plt.show()
# remove the cooldown and then take an average
print(tempf[100:len(tempf)].mean())
print(tempf.argmax())