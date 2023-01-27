import numpy as np
from numpy import *
import math
import matplotlib.pyplot as plt

A1_V2_1=5.4
A1_V2_2=5.4
A1_V2_3=5.3
A1_V2_4=5.4
A1_V2_5=5.4
A1_V2_6=5.4
A2_V2_1=5.5
A2_V2_2=5.5
A2_V2_3=5.9
A2_V2_4=5.3
A2_V2_5=0.880
A2_V2_6=0.213

V2_1=20*math.log10(A2_V2_1/A1_V2_1)
V2_2=20*math.log10(A2_V2_2/A1_V2_2)
V2_3=20*math.log10(A2_V2_3/A1_V2_3)
V2_4=20*math.log10(A2_V2_4/A1_V2_4)
V2_5=20*math.log10(A2_V2_5/A1_V2_5)
V2_6=20*math.log10(A2_V2_6/A1_V2_6)

K=1
Q=1
R11=10000
C2=4.7*10**(-9)
T=R11*C2

f1=499.8
omega1=2*math.pi*f1
f2=998.36
omega2=2*math.pi*f2
f3=3.2012*10**3
omega3=2*math.pi*f3
f4=3.8258*10**3
omega4=2*math.pi*f4
f5=10.013*10**3
omega5=2*math.pi*f5
f6=20.029*10**3
omega6=2*math.pi*f6

x=[omega1, omega2, omega3, omega4, omega5, omega6]
y=[V2_1, V2_2, V2_3, V2_4, V2_5, V2_6]

omega = linspace(10, 200000, 1000)
transfer_f = 20*np.log10(abs(-K/T**2)/abs((1j*omega)**2+(1j*omega)/(T*Q)+1/T**2))

plt.scatter(x, y, c='black', label='Experimental')
plt.plot(omega, transfer_f, 'g', label='Teórico')

plt.ticklabel_format(axis="y")
plt.xlabel(r'$\omega\;(rad\cdot s^{-1})$', fontsize=10)
plt.ylabel('|T| (dB)', fontsize=10, rotation='horizontal', loc='top')
plt.xscale('log')
plt.title(r'$T_2=\frac{V_2}{V_i}$', fontsize=15)
plt.legend(loc='center left', shadow=False, fontsize='large')
plt.grid()
plt.show()