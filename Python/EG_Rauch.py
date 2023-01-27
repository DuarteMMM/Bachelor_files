import numpy as np
from numpy import *
import math
import matplotlib.pyplot as plt

A1_1=0.480
A1_2=0.480
A1_3=0.480
A1_4=0.480
A1_5=0.460
A1_6=0.480
A1_7=0.480
A2_1=1.23
A2_2=5.8
A2_3=4.4
A2_4=5.9
A2_5=4.4
A2_6=0.423
A2_7=0.207

V1_1=20*math.log10(A2_1/A1_1)
V1_2=20*math.log10(A2_2/A1_2)
V1_3=20*math.log10(A2_3/A1_3)
V1_4=20*math.log10(A2_4/A1_4)
V1_5=20*math.log10(A2_5/A1_5)
V1_6=20*math.log10(A2_6/A1_6)
V1_7=20*math.log10(A2_7/A1_7)


f1=498.78
omega1=2*math.pi*f1
f2=1.0030*10**3
omega2=2*math.pi*f2
f3=837.80
omega3=2*math.pi*f3
f4=982.20
omega4=2*math.pi*f4
f5=1.1143*10**3
omega5=2*math.pi*f5
f6=4.9880*10**3
omega6=2*math.pi*f6
f7=9.9851*10**3
omega7=2*math.pi*f7

x=[omega1, omega2, omega3, omega4, omega5, omega6, omega7]
y=[V1_1, V1_2, V1_3, V1_4, V1_5, V1_6, V1_7]

B=500*math.pi
#epsilon=math.sqrt(-10**(-24/10)+1)
epsilon=1
w0=2000*math.pi

omega = linspace(10, 200000, 1000)
transfer_f = -20*np.log10(abs(B*1j*omega/epsilon)/abs((1j*omega)**2+(1j*omega)*B/epsilon+w0**2))
#print(20*np.log10(abs(B*1j*2*math.pi*1000/epsilon)/abs((1j*2*math.pi*1000)**2+(1j*2*math.pi*1000)*B/epsilon+w0**2)))

plt.scatter(x, y, c='black', label='Experimental')
plt.plot(omega, transfer_f, 'r', label='Teórico')

plt.xlabel(r'$\omega\;(rad\cdot s^{-1})$', fontsize=10)
plt.ylabel('|T| (dB)', fontsize=10, rotation='horizontal', loc='top')
plt.xscale('log')
plt.title(r'$T=\frac{V_{out}}{V_{in}}$', fontsize=15)
plt.legend(loc='best', shadow=False, fontsize='large')
plt.grid()
plt.show()