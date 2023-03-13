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

# Type in your data into arrays
x=np.array([0.001274, 0.001764, 0.001029, 0.00049, 0.000735, 0.002058, 
            0.000049, 0.000735, 0.001127, 0.00147  ])
y=np.array([2.8824 , 3.807, 2.3275, 1.1907, 1.7003, 4.3659, 0.3087, 
            1.7787, 2.5333, 3.1164 ])

# Plot the data, you may have to adjust the plot axis 
#  limits
#plt.axis([-1,11, -1,11])
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