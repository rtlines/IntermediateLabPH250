#########################################################
# Program to do a curve fit in python with a user defined 
#  fit equation and %  with data supplied by the user.
# The user types the data into numpy arrays by hand,
#  and supplies a function with the fit equation.
#  In this example, the function is called RC_Charging.
#
# Author:  Todd Lines
# Date:    2023-02-20
#########################################################
import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

# Define the Gaussian function
print("  ")
print("Find a curve fit to a user defined function")

#Here is where you define the function to use in the fit
def RC_Charging(x, A, B, C):
    y = A*(np.exp(-B*x)) + C
    return y

#here is where you give the data to fit. Put it into numpy 
#  arrays. Say our data is voltage vs. time. Put the
#  time #  values in the xdata array and the voltage 
#  values in the #  ydata array. For the exmple the units
#  are seconds and volts
xdata = np.array([10,20,30,40,50,60,70,80,90,100,110,120, 
                  130, 140, 150, 160, 170, 180])
ydata = np.array([2.5,2.28,2.1,1.88,1.71,1.53,1.37,1.21,
                  1.05,0.9,0.77,0.64,0.51,0.4,0.28,0.18,
                  0.1,0.06])

#we also need the ydata uncertainty for error bars. 
#  Say it is 0.1  (you sould calculate what your
#  value should be)
ydata_err = 0.049 #V

#Now plot the data so we can see the data points
#plt.plot(xdata, ydata, 'o')


#Now perform the curve fit. We can't just use a linear 
#  fit. The data is very much not linear. So we 
#  will use a more robust curve fit rotine from scipy.
#  The sciepy optimize curve_fit() routine needs the 
#  equation to use for the fit as a function (here 
#  RC_Charting()) and it needs the fit parameters and
#  for the error on the fit parameters we need the 
# covariance matrix to be output
parameters, covariance = curve_fit(RC_Charging, 
                                   xdata, ydata)

#Pull out the fit prameters
fit_A = parameters[0]
fit_B = parameters[1]
fit_C = parameters[2]


#Pull out the uncertanty from the diagonal elements 
#  of the covariance matrix. Remember that the 
#  diagonal elements #  are the error squared.
SE = np.sqrt(np.diag(covariance))
SE_A = SE[0]
SE_B = SE[1]
SE_C = SE[2]

#Use the fit parameters to make a set of estamated 
#  y values #  from the fit equation. We can pass 
#  in the whole xdata array #  and get out all the 
#  y value estimates at once using our #  function 
#  with our fit equation.  I called the new y-values
#  fit_y.
fit_y = RC_Charging(xdata, fit_A, fit_B, fit_C)

#Plot the data (as dots) and the fit (as a line) to 
#  see if the equation makes sense as a good fit.
plt.xlabel('Time in seconds')
plt.ylabel('Voltage (V)')
plt.errorbar(xdata, ydata, yerr = ydata_err, 
             label ='data', fmt='ro')
plt.plot(xdata, fit_y, 'b-', label='fit')
plt.legend()
plt.show()

#and print out our fit parameters and their 
#  uncertainties
print("  ")
print('The value of A is ',fit_A, end =" ") 
print ('with standard error of ', SE_A)
print('The value of B is ', fit_B, end =" ")
print('with standard error of', SE_B)
print('The value of C is', fit_C, end =" ")
print('with standard error of', SE_C)
print("  ")

#sometimes the curve fit routine throws a 
#  math warning, let the user know that the program 
#  ended and not to be upset about the warning
print('successful end of program')
print('warning about overflow may follow')
print("  ")