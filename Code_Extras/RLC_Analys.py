import numpy as np
from matplotlib import pyplot as plt

L_og = 2.3057 * 10**(-3) #N/A**2
C = 26.4 * 10**-9 # F
delta_C = 0.2*C

# Other Group estimate for Frequency
L_og = 2.3057 * 10**(-3) #N/A**2
f_og = 1/(2*np.pi*np.sqrt(L_og*C))
print("f_og estimate =", f_og)

# Calculate L from our measurements
layers =5     #I assumed five layers
delta_layers = 1
count = 104   #the number of coil turns I counted
N = layers * count
mu_o = 1.2566 * 10**(-6)  # N/A**2
delta_mu_o = 1.9 * 10**(-16) # N/A**2
length = 0.147 # m
delta_length = 0.005 # m
D = 0.045 # m
delta_D = 0.01 # m

# Calculate the inductance
L_th = mu_o * (layers*count)**2 *np.pi *D**2/(4*length)

# Predict the frquency
f_th = 1/(2*np.pi*np.sqrt(L_th*C))
print("f_th estimate =", f_th)

# Calculate the uncertainty in the inductance
delta_Lth_1 = ((layers*count)**2*np.pi*D**2*delta_mu_o/(4*length))**2
delta_Lth_2 = (mu_o*2*(layers*count)*np.pi*D**2/(4*length)*(delta_layers))**2
delta_Lth_3 = 0
delta_Lth_4 = (mu_o*(layers*count)**2*np.pi*D**2*delta_length/(4*length**2))**2
delta_Lth_5 = (mu_o*(layers*count)**2*np.pi*D*delta_D/(2*length))**2

#print(delta_Lth_1)
#print(delta_Lth_2)
#print(delta_Lth_3)
#print(delta_Lth_4)
#print(delta_Lth_5)

delta_Lth=np.sqrt(delta_Lth_1+delta_Lth_2+delta_Lth_3+delta_Lth_4+delta_Lth_5)
# Print out our theoretical inductance
print("L_th =", L_th, "+-", delta_Lth)

# Now calculate our inductance based on our resonant frequency
f = 16090 #Hz
delta_f=0.01*f

# inductance from the frequency measurement is then 
L_A=1/(4*np.pi**2*f**2*C)

# calculate the uncertainty in L_A
delta_LA_1 = (delta_f/(4*np.pi**2*f**3*C))**2
delta_LA_2 = (delta_C/(4*np.pi**2*f**2*C**2))**2
#print("delta_LA_1 ", delta_LA_1)
#print("delta_LA_2 ", delta_LA_2)

delta_LA = np.sqrt(delta_LA_1+delta_LA_2)

print("L_A = ", L_A, "+-",delta_LA)

# Now make the plot

xA=[1]
yA=[L_A]
xT=[2]
yT=[L_th]
yerrorA=[delta_LA]
yerrorT=[delta_Lth]
plt.xlabel(" ")
plt.xlim([0, 3])
plt.ylabel("Inductance (N/A**2)")
plt.errorbar(xA,yA, yerr = yerrorA, fmt = 'o')
plt.errorbar(xT,yT, yerr = yerrorT, fmt = 'o')
ax = plt.gca()
ax.xaxis.set_tick_params(labelbottom=False)
plt.legend(['L from resonance',"L from theory"],loc ="upper left")
plt.show()




