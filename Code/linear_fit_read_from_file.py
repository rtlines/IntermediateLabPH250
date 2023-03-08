#######################################################
# Program to do a simple linear curve fit in python
#  with data supplied by the user.
#  The user types the data into numpy arrays by hand.
#
# Author:  Todd Lines
# Date:    2023-02-20
#######################################################
# linear_fit.py
#######################################################
# libraries to import
import scipy as sp
import numpy as np
import matplotlib.pyplot as plt

xlist=[]
ylist=[]

# Read data in from file
with open("C:\\Users\\rtlines\\Documents\\data2.txt") as fp:
     for line in fp:
         text1 ,text2 = line.split(",")
         xlist.append(float(text1.strip()))
         ylist.append(float(text2.strip()))
# Type in your data into arrays
x = np.array(xlist)
y = np.array(ylist)



# Plot the data, you may have to adjust the plot axis 
#  limits
plt.axis([0,max(x), 0,max(y)])
plt.plot(x,y,'bo')

# now let's do the curve fit
result= sp.stats.linregress(x, y)

# result holds all of the data from the fit in this order
#   slope, intercept, rvalue, pvalue, stderr (error on the 
#   slope), and #  intercept_stderr (error on the 
#   y-intercept) Let's print out the slope and intercept
print ("slope is  ",result.slope, "+- ", result.stderr)
print ("intercept is  ", result.intercept, "+- ", 
       result.intercept_stderr)

# Now let's try the curve fit to see how it does
xf=np.linspace(0, max(x), 11)
yf=np.zeros(11)
for i in range(11):
    yf[i]=result.slope*xf[i] + result.intercept

# and add the fit line to our graph
plt.plot(xf,yf,'r')

# and we are done. Tell the user we have finished
print('program ended successfully')