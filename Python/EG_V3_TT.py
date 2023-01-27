import numpy as np
from numpy import *
import math
import matplotlib.pyplot as plt

A1_V3_1=5.4
A1_V3_2=5.3
A1_V3_3=5.3
A1_V3_4=5.3
A1_V3_5=5.3
A1_V3_6=5.3
A2_V3_1=5.5
A2_V3_2=5.5
A2_V3_3=6.0
A2_V3_4=5.4
A2_V3_5=0.920
A2_V3_6=0.249

V3_1=20*math.log10(A2_V3_1/A1_V3_1)
V3_2=20*math.log10(A2_V3_2/A1_V3_2)
V3_3=20*math.log10(A2_V3_3/A1_V3_3)
V3_4=20*math.log10(A2_V3_4/A1_V3_4)
V3_5=20*math.log10(A2_V3_5/A1_V3_5)
V3_6=20*math.log10(A2_V3_6/A1_V3_6)

K=1
Q=1
R11=10000
C2=4.7*10**(-9)
T=R11*C2

f1=499.85
omega1=2*math.pi*f1
f2=1.0012*10**3
omega2=2*math.pi*f2
f3=3.0026*10**3
omega3=2*math.pi*f3
f4=3.7985*10**3
omega4=2*math.pi*f4
f5=10.000*10**3
omega5=2*math.pi*f5
f6=20.022*10**3
omega6=2*math.pi*f6

x=[omega1, omega2, omega3, omega4, omega5, omega6]
y=[V3_1, V3_2, V3_3, V3_4, V3_5, V3_6]

omega = linspace(10, 200000, 1000)
transfer_f = 20*np.log10(abs(-K/T**2)/abs((1j*omega)**2+(1j*omega)/(T*Q)+1/T**2))

plt.scatter(x, y, c='black', label='Experimental')
plt.plot(omega, transfer_f, 'b', label='Teórico')

plt.ticklabel_format(axis="x", style="sci", scilimits=(0,0))
plt.ticklabel_format(axis="y", style="sci", scilimits=(0,0))
plt.ylabel('|T| (dB)', fontsize=10, rotation='horizontal', loc='top')
plt.xscale('log')
plt.title(r'$T_3=\frac{V_3}{V_i}$', fontsize=15)
plt.legend(loc='center left', shadow=False, fontsize='large')
plt.grid()
plt.show()