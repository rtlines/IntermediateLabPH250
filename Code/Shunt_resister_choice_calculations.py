###############################################################################
# Calculate Shunt Resistance Values
#
# Author:  R. Todd lines
# Date: Feb 4, 2026
#
###############################################################################
#
import numpy as np

R = 1000 # ohms
Rs = 100 # ohms
delta_Rs = 0.01*Rs
Delta_Vps = 3.5   # volts
delta_v=4.88E-3  # volta
print(delta_Rs)
# Find I
I = Delta_Vps/(R + Rs)
print(f"I = {I:.2e}")
# Find the voltage across the shunt resistor
Delta_Vs = I * Rs
print(f"Delta_Vs = {Delta_Vs:.2e}")
#Find the number of ADC units across Delta_Vs
NADC=int(Delta_Vs/delta_v)
print("NADC = ",NADC)
# Find the uncertainty in Delta_Vs
delta_Delta_Vs = Delta_Vs/NADC
print(f"delta_Delta_Vs = {delta_Delta_Vs:.2e}")
# Find the percent error in DeltaVs
print(f"Percent error in Delta_Vs = {delta_Delta_Vs/Delta_Vs:.2e}")
# Find the uncertainty in I. Calculate the uncertainty terms independently'
#   Then combine later
delta_I_1 = (delta_Delta_Vs/Rs)**2
delta_I_2 = (Delta_Vs*delta_Rs/Rs**2)**2
print(f"delta_I_1 = {delta_I_1:.2e}")
print(f"delta_I_2 = {delta_I_2:.2e}")
delta_I=np.sqrt(delta_I_1 + delta_I_2)
I_expected=Delta_Vps/R
fI=100*delta_I/I_expected
print(f"Iexpected = {I_expected:.2e}" , f" +- {delta_I:.2e}")
print("fractional uncertainty = ", fI)
#Calculate Voltage Error
Delta_Vtest=I*R
PD_Delta_Vtest=100*(Delta_Vtest-Delta_Vps)/Delta_Vtest
print(f"Delta_Vtest = {Delta_Vtest:.2e}")
print(f"Percent difference in Delta_V = {PD_Delta_Vtest:.2e}")
print("Program ended successfully")

