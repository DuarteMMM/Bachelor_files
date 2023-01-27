import numpy as np
from numpy import *
import math
import matplotlib.pyplot as plt

A1_V2_1=8.9
A1_V2_2=8.9
A1_V2_3=8.6
A1_V2_4=8.6
A1_V2_5=9.0
A1_V2_6=8.9
A1_V2_7=8.8
A1_V2_8=8.9
A2_V2_1=1.4
A2_V2_2=2.7
A2_V2_3=4.1
A2_V2_4=10.1
A2_V2_5=7.1
A2_V2_6=7.2
A2_V2_7=4.1
A2_V2_8=2.2

V2_1=20*math.log10(A2_V2_1/A1_V2_1)
V2_2=20*math.log10(A2_V2_2/A1_V2_2)
V2_3=20*math.log10(A2_V2_3/A1_V2_3)
V2_4=20*math.log10(A2_V2_4/A1_V2_4)
V2_5=20*math.log10(A2_V2_5/A1_V2_5)
V2_6=20*math.log10(A2_V2_6/A1_V2_6)
V2_7=20*math.log10(A2_V2_7/A1_V2_7)
V2_8=20*math.log10(A2_V2_8/A1_V2_8)

K=1
Q=1
R11=10000
C2=4.7*10**(-9)
T=R11*C2

f1=499.8
omega1=2*math.pi*f1
f2=1.001*10**3
omega2=2*math.pi*f2
f3=1.4995*10**3
omega3=2*math.pi*f3
f4=3.9027*10**3
omega4=2*math.pi*f4
f5=2.4011*10**3
omega5=2*math.pi*f5
f6=6.092*10**3
omega6=2*math.pi*f6
f7=10.006*10**3
omega7=2*math.pi*f7
f8=20.019*10**3
omega8=2*math.pi*f8

x=[omega1, omega2, omega3, omega4, omega5, omega6, omega7, omega8]
y=[V2_1, V2_2, V2_3, V2_4, V2_5, V2_6, V2_7, V2_8]

omega = linspace(10, 200000, 1000)
transfer_f = 20*np.log10(abs(-K*1j*omega/T)/abs((1j*omega)**2+(1j*omega)/(T*Q)+1/T**2))

plt.scatter(x, y, c='black', label='Experimental')
plt.plot(omega, transfer_f, 'g', label='Teórico')

plt.ticklabel_format(axis="y")
plt.xlabel(r'$\omega\;(rad\cdot s^{-1})$', fontsize=10)
plt.xscale('log')
plt.title(r'$T_2=\frac{V_2}{V_i}$', fontsize=15)
plt.legend(loc='upper left', shadow=False, fontsize='large')
plt.grid()
plt.show()