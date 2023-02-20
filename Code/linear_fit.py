import scipy as sp
import numpy as np
import matplotlib.pyplot as plt
import random as rd


#Type in your data into arrays
x=np.array([ 0.,  1.,  2.,  3.,  4.,  5.,  6.,  7.,  8.,
            9., 10.])
y=np.array([2.95491226, 0.38578942, 4.58771916, 
            2.16887048, 3.66484311, 2.83660703, 
            6.6584007 , 7.84011419, 9.55442455, 
            8.80618692, 7.39340476])

#Plot the data, you may have to adjust the plot axis limits
plt.axis([-1,11, -1,11])
plt.plot(x,y,'bo')

# now let's do the curve fit
result= sp.stats.linregress(x, y)

#result holds all of the data from the fit in this order
#  slope, intercept, rvalue, pvalue, stderr (error on the 
#  slope), and #  intercept_stderr (error on the 
#  y-intercept) Let's print out the slope and intercept
print ("slope is  ",result.slope, "+- ", result.stderr)
print ("intercept is  ", result.intercept, "+- ", 
       result.intercept_stderr)

#Now let's try the curve fit to see how it does
xf=np.linspace(0, 10, 11)
yf=np.zeros(11)
for i in range(11):
    yf[i]=result.slope*xf[i] + result.intercept

#and add the fit line to our graph
plt.plot(xf,yf,'r')

#and we are done. Tell the user we have finished
print('program ended successfully')