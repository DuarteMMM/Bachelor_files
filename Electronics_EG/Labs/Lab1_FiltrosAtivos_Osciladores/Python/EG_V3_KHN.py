import numpy as np
from numpy import *
import math
import matplotlib.pyplot as plt

A1_V3_1=8.6
A1_V3_2=8.6
A1_V3_3=8.8
A1_V3_4=8.6
A1_V3_5=9.0
A1_V3_6=8.7
A2_V3_1=9.5
A2_V3_2=9.8
A2_V3_3=11.7
A2_V3_4=10.4
A2_V3_5=1.8
A2_V3_6=0.600

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

f1=500.5
omega1=2*math.pi*f1
f2=999.8
omega2=2*math.pi*f2
f3=3.103*10**3
omega3=2*math.pi*f3
f4=3.9034*10**3
omega4=2*math.pi*f4
f5=9.994*10**3
omega5=2*math.pi*f5
f6=19.968*10**3
omega6=2*math.pi*f6

x=[omega1, omega2, omega3, omega4, omega5, omega6]
y=[V3_1, V3_2, V3_3, V3_4, V3_5, V3_6]

omega = linspace(10, 200000, 1000)
transfer_f = 20*np.log10(abs(K/T**2)/abs((1j*omega)**2+(1j*omega)/(T*Q)+1/T**2))

plt.scatter(x, y, c='black', label='Experimental')
plt.plot(omega, transfer_f, 'b', label='Teórico')

plt.ticklabel_format(axis="x", style="sci", scilimits=(0,0))
plt.ticklabel_format(axis="y", style="sci", scilimits=(0,0))
plt.ylabel('|T| (dB)', fontsize=10, rotation='horizontal', loc='top')
plt.xscale('log')
plt.title(r'$T_3=\frac{V_3}{V_i}$', fontsize=15)
plt.legend(loc='best', shadow=False, fontsize='large')
plt.grid()
plt.show()