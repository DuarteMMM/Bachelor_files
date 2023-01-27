import numpy as np
from numpy import *
import math
import matplotlib.pyplot as plt

A1_V1_1=5.4
A1_V1_2=5.4
A1_V1_3=5.4
A1_V1_4=5.3
A1_V1_5=5.3
A1_V1_6=5.4
A1_V1_7=5.3
A2_V1_1=0.690
A2_V1_2=1.45
A2_V1_3=5.3
A2_V1_4=3.7
A2_V1_5=3.7
A2_V1_6=2.25
A2_V1_7=1.09

V1_1=20*math.log10(A2_V1_1/A1_V1_1)
V1_2=20*math.log10(A2_V1_2/A1_V1_2)
V1_3=20*math.log10(A2_V1_3/A1_V1_3)
V1_4=20*math.log10(A2_V1_4/A1_V1_4)
V1_5=20*math.log10(A2_V1_5/A1_V1_5)
V1_6=20*math.log10(A2_V1_6/A1_V1_6)
V1_7=20*math.log10(A2_V1_7/A1_V1_7)

K=1
Q=1
R11=10000
C2=4.7*10**(-9)
T=R11*C2

f1=500.45
omega1=2*math.pi*f1
f2=1.0015*10**3
omega2=2*math.pi*f2
f3=4.0026*10**3
omega3=2*math.pi*f3
f4=2.2967*10**3
omega4=2*math.pi*f4
f5=6.595*10**3
omega5=2*math.pi*f5
f6=10.002*10**3
omega6=2*math.pi*f6
f7=19.997*10**3
omega7=2*math.pi*f7

x=[omega1, omega2, omega3, omega4, omega5, omega6, omega7]
y=[V1_1, V1_2, V1_3, V1_4, V1_5, V1_6, V1_7]

omega = linspace(10, 200000, 1000)
transfer_f = 20*np.log10(abs(-K*(1j*omega)/T)/abs((1j*omega)**2+(1j*omega)/(T*Q)+1/T**2))

plt.scatter(x, y, c='black', label='Experimental')
plt.plot(omega, transfer_f, 'r', label='Teórico')

plt.xlabel(r'$\omega\;(rad\cdot s^{-1})$', fontsize=10)
plt.ylabel('|T| (dB)', fontsize=10, rotation='horizontal', loc='top')
plt.xscale('log')
plt.title(r'$T_1=\frac{V_1}{V_i}$', fontsize=15)
plt.legend(loc='center left', shadow=False, fontsize='large')
plt.grid()
plt.show()