###############################################################################
# Code to find the uncertainty in a current value based on the input 
#   voltage and the shunt resistance.  This is part of Lab 5 for PH250 at
#   BYU-Idaho.
###############################################################################
#
#Import libraries
import numpy as np
#
#
# Define variables
DeltaVps = 2.3      #V   The power supply voltage applied to the circuit
Rtest = 10000      #ohms The resistance of the circut begin tested
Rs = 1000       #ohms The shunt resistance for our ammeter
DeltaVmin = 5/1024 #V the quantization error for an Arduino
Rtollarence = 0.01 #% the ristor code tollerance band percentage
deltaRs=0.01*Rs

Rtotal = Rtest + Rs 
I = DeltaVps/Rtotal

DeltaVs =DeltaVps*Rs/(Rtest + Rs)
NADC = DeltaVs//DeltaVmin

print("Delta Vs ",DeltaVs," V")
print("Our minimum detectable voltage step is ",DeltaVmin," V")
print("The number of ADC usnits this reperestens is ",NADC)

deltaDeltaVs = DeltaVs/NADC

print("The voltage uncertainty unit for DeltaVs ", deltaDeltaVs,"V")
print("The percent error for DeltaVs ", 100*deltaDeltaVs/DeltaVs,"%")

#Error terms 
ET1 = (deltaDeltaVs/Rs)**2
ET2 = (DeltaVs*deltaRs/Rs**2)**2
print("ET1, ET2 ",ET1,ET2)
DeltaI = np.sqrt(ET1+ET2)
print("The uncertainty in our current measurement is ",DeltaI, " A")
RDeltaI = 100*DeltaI/I
print("The relative uncertainty in our current measurement is",RDeltaI," %")
