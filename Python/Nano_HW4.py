#Import necessary libraries
import numpy as np
from numpy import *
import matplotlib.pyplot as plt

#Constants in SI units
A=2E8
B=1E-10
C=2.7E-30

#Vector of n
n = logspace(14, 24, num=1000)
#Vector of IQE
IQE = (B*(n**2))/(A*n+B*(n**2)+C*(n**3))

#Graph
plt.plot(n, IQE*100, 'b', label=r'Without C')
plt.xlabel(r'n ($cm^{-3}$)', fontsize=21, loc='right')
plt.ylabel(r'IQE ($\%$)', fontsize=21, rotation='horizontal', loc='top')
plt.xlim(1E14, 1E24)
plt.grid()
plt.show()

#Highest IQE and respective n
n_max = n[np.argmax(IQE)] 
print ("Value of n (cm^-3): ", n_max)
print ("Value of IQE (%): ", max(IQE)*100)