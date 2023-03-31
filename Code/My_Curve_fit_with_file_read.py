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
    y = A*(1-np.exp(-B*x)) + C
    return y

#here is where you give the data to fit. Put it into numpy 
#  arrays. Say our data is voltage vs. time. Put the
#  time #  values in the xdata array and the voltage 
#  values in the #  ydata array. For the exmple the units
#  are seconds and volts
#  The pythong serial capture program gives data in the form
#  <"time in sec ">,<time>,<" voltage across C">,<voltage>
#  The "time in sec" and " voltage across C " are helpful 
#  on the serial monitor, but not when we read the data in 
#  from a file.  Here we will need to strip off these 
#  data titles.

xdata = []
ydata = []

file =open("C:\\Users\\rtlines\\Documents\\RC_Data_Kavin.csv")
for line in file.readlines():
    print(line)
    #xtitles.append( (line.split(',')[0]) )
    xtitle =  line.split(',')[0]
    xdata.append( float(line.split(',')[1]) )
    ytitle = line.split(',')[2]
    ydata.append( float(line.split(',')[3]) )

file.close()

xdata=np.array(xdata)
ydata=np.array(ydata)
#we also need the ydata uncertainty for error bars. 
#  Say it is 0.2V
ydata_err = np.sqrt(2)*0.0049 #V

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

#and print out our fit parameters and their uncertainties
print("  ")
print(F'The value of A is {fit_A:.5f} with standard error of {SE_A:.5f}.')
print(F'The value of B is {fit_B:.5f} with standard error of {SE_B:.5f}.')
print(F'The value of C is {fit_C:.5f} with standard error of {SE_C:.5f}.')
print("  ")

# the time constant is 1/B. Let's out put this for the user
tau = 1/fit_B
delta_tau = (1/(fit_B**2))*SE_B
print(F'The time constant is {tau:.2f} +- {delta_tau:.2f} seconds')
print("  ")
#sometimes the curve fit routine throws a math warning, let the user know 
#  that the program ended and not to be upset about the warning

print("successful end of program, warning about overflow may follow")
print("  ")