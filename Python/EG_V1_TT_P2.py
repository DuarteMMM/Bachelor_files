import numpy as np
from numpy import *
import math
import matplotlib.pyplot as plt

#P2=10kohm
A1_V1_1_10=5.4
A1_V1_2_10=5.4
A1_V1_3_10=5.4
A1_V1_4_10=5.3
A1_V1_5_10=5.3
A1_V1_6_10=5.4
A1_V1_7_10=5.3
A2_V1_1_10=0.690
A2_V1_2_10=1.45
A2_V1_3_10=5.3
A2_V1_4_10=3.7
A2_V1_5_10=3.7
A2_V1_6_10=2.25
A2_V1_7_10=1.09

V1_1_10=20*math.log10(A2_V1_1_10/A1_V1_1_10)
V1_2_10=20*math.log10(A2_V1_2_10/A1_V1_2_10)
V1_3_10=20*math.log10(A2_V1_3_10/A1_V1_3_10)
V1_4_10=20*math.log10(A2_V1_4_10/A1_V1_4_10)
V1_5_10=20*math.log10(A2_V1_5_10/A1_V1_5_10)
V1_6_10=20*math.log10(A2_V1_6_10/A1_V1_6_10)
V1_7_10=20*math.log10(A2_V1_7_10/A1_V1_7_10)

f1_10=500.45
omega1_10=2*math.pi*f1_10
f2_10=1.0015*10**3
omega2_10=2*math.pi*f2_10
f3_10=4.0026*10**3
omega3_10=2*math.pi*f3_10
f4_10=2.2967*10**3
omega4_10=2*math.pi*f4_10
f5_10=6.595*10**3
omega5_10=2*math.pi*f5_10
f6_10=10.002*10**3
omega6_10=2*math.pi*f6_10
f7_10=19.997*10**3
omega7_10=2*math.pi*f7_10

x_10=[omega1_10, omega2_10, omega3_10, omega4_10, omega5_10, omega6_10, omega7_10]
y_10=[V1_1_10, V1_2_10, V1_3_10, V1_4_10, V1_5_10, V1_6_10, V1_7_10]

#P2=5kohm
A1_V1_1_5=5.4
A1_V1_2_5=5.3
A1_V1_3_5=5.3
A1_V1_4_5=5.2
A1_V1_5_5=5.4
A1_V1_6_5=5.3
A1_V1_7_5=5.3
A2_V1_1_5=1.39
A2_V1_2_5=2.81
A2_V1_3_5=10.5
A2_V1_4_5=7.4
A2_V1_5_5=7.4
A2_V1_6_5=4.4
A2_V1_7_5=2.09

V1_1_5=20*math.log10(A2_V1_1_5/A1_V1_1_5)
V1_2_5=20*math.log10(A2_V1_2_5/A1_V1_2_5)
V1_3_5=20*math.log10(A2_V1_3_5/A1_V1_3_5)
V1_4_5=20*math.log10(A2_V1_4_5/A1_V1_4_5)
V1_5_5=20*math.log10(A2_V1_5_5/A1_V1_5_5)
V1_6_5=20*math.log10(A2_V1_6_5/A1_V1_6_5)
V1_7_5=20*math.log10(A2_V1_7_5/A1_V1_7_5)

f1_5=499.20
omega1_5=2*math.pi*f1_5
f2_5=1.0016*10**3
omega2_5=2*math.pi*f2_5
f3_5=3.7958*10**3
omega3_5=2*math.pi*f3_5
f4_5=2.4284*10**3
omega4_5=2*math.pi*f4_5
f5_5=6.1395*10**3
omega5_5=2*math.pi*f5_5
f6_5=10.006*10**3
omega6_5=2*math.pi*f6_5
f7_5=20.042*10**3
omega7_5=2*math.pi*f7_5

x_5=[omega1_5, omega2_5, omega3_5, omega4_5, omega5_5, omega6_5, omega7_5]
y_5=[V1_1_5, V1_2_5, V1_3_5, V1_4_5, V1_5_5, V1_6_5, V1_7_5]

#P2=1kohm
A1_V1_1_1=2.05
A1_V1_2_1=2.09
A1_V1_3_1=2.05
A1_V1_4_1=2.05
A1_V1_5_1=2.05
A1_V1_6_1=2.05
A1_V1_7_1=2.09
A2_V1_1_1=2.65
A2_V1_2_1=5.5
A2_V1_3_1=19.5
A2_V1_4_1=13.9
A2_V1_5_1=13.7
A2_V1_6_1=8.2
A2_V1_7_1=3.9

V1_1_1=20*math.log10(A2_V1_1_1/A1_V1_1_1)
V1_2_1=20*math.log10(A2_V1_2_1/A1_V1_2_1)
V1_3_1=20*math.log10(A2_V1_3_1/A1_V1_3_1)
V1_4_1=20*math.log10(A2_V1_4_1/A1_V1_4_1)
V1_5_1=20*math.log10(A2_V1_5_1/A1_V1_5_1)
V1_6_1=20*math.log10(A2_V1_6_1/A1_V1_6_1)
V1_7_1=20*math.log10(A2_V1_7_1/A1_V1_7_1)

f1_1=500.20
omega1_1=2*math.pi*f1_1
f2_1=999.64
omega2_1=2*math.pi*f2_1
f3_1=3.8031*10**3
omega3_1=2*math.pi*f3_1
f4_1=2.2474*10**3
omega4_1=2*math.pi*f4_1
f5_1=6.2352*10**3
omega5_1=2*math.pi*f5_1
f6_1=10.002*10**3
omega6_1=2*math.pi*f6_1
f7_1=19.971*10**3
omega7_1=2*math.pi*f7_1

x_1=[omega1_1, omega2_1, omega3_1, omega4_1, omega5_1, omega6_1, omega7_1]
y_1=[V1_1_1, V1_2_1, V1_3_1, V1_4_1, V1_5_1, V1_6_1, V1_7_1]

#P2=0.5kohm
A1_V1_1_05=0.980
A1_V1_2_05=0.960
A1_V1_3_05=0.980
A1_V1_4_05=0.980
A1_V1_5_05=0.980
A1_V1_6_05=1.01
A1_V1_7_05=0.960
A2_V1_1_05=2.49
A2_V1_2_05=5.1
A2_V1_3_05=18.3
A2_V1_4_05=12.7
A2_V1_5_05=12.9
A2_V1_6_05=7.3
A2_V1_7_05=3.6

V1_1_05=20*math.log10(A2_V1_1_05/A1_V1_1_05)
V1_2_05=20*math.log10(A2_V1_2_05/A1_V1_2_05)
V1_3_05=20*math.log10(A2_V1_3_05/A1_V1_3_05)
V1_4_05=20*math.log10(A2_V1_4_05/A1_V1_4_05)
V1_5_05=20*math.log10(A2_V1_5_05/A1_V1_5_05)
V1_6_05=20*math.log10(A2_V1_6_05/A1_V1_6_05)
V1_7_05=20*math.log10(A2_V1_7_05/A1_V1_7_05)

f1_05=499.93
omega1_05=2*math.pi*f1_05
f2_05=1.0002*10**3
omega2_05=2*math.pi*f2_05
f3_05=3.4983*10**3
omega3_05=2*math.pi*f3_05
f4_05=2.2825*10**3
omega4_05=2*math.pi*f4_05
f5_05=6.093*10**3
omega5_05=2*math.pi*f5_05
f6_05=10.012*10**3
omega6_05=2*math.pi*f6_05
f7_05=19.992*10**3
omega7_05=2*math.pi*f7_05

x_05=[omega1_05, omega2_05, omega3_05, omega4_05, omega5_05, omega6_05, omega7_05]
y_05=[V1_1_05, V1_2_05, V1_3_05, V1_4_05, V1_5_05, V1_6_05, V1_7_05]

#Teórico P2=10kohm

R4=10000
P2_10=9894
K_10=R4/P2_10
P2_5=5050
K_5=R4/P2_5
P2_1=999.8
K_1=R4/P2_1
P2_05=507.0
K_05=R4/P2_05
Q=1
R11=10000
C2=4.7*10**(-9)
T=R11*C2

omega = linspace(10, 200000, 1000)
transfer_f_10 = 20*np.log10(abs(-K_10*(1j*omega)/T)/abs((1j*omega)**2+(1j*omega)/(T*Q)+1/T**2))
transfer_f_5 = 20*np.log10(abs(-K_5*(1j*omega)/T)/abs((1j*omega)**2+(1j*omega)/(T*Q)+1/T**2))
transfer_f_1 = 20*np.log10(abs(-K_1*(1j*omega)/T)/abs((1j*omega)**2+(1j*omega)/(T*Q)+1/T**2))
transfer_f_05 = 20*np.log10(abs(-K_05*(1j*omega)/T)/abs((1j*omega)**2+(1j*omega)/(T*Q)+1/T**2))


plt.scatter(x_10, y_10, c='blue', label=r'$P_2=10\;k\Omega$')
plt.plot(omega, transfer_f_10, 'blue')
plt.scatter(x_5, y_5, c='red', label=r'$P_2=5\;k\Omega$')
plt.plot(omega, transfer_f_5, 'red')
plt.scatter(x_1, y_1, c='green', label=r'$P_2=1\;k\Omega$')
plt.plot(omega, transfer_f_1, 'green')
plt.scatter(x_05, y_05, c='black', label=r'$P_2=0.5\;k\Omega$')
plt.plot(omega, transfer_f_05, 'black')

plt.xlabel(r'$\omega\;(rad\cdot s^{-1})$', fontsize=10)
plt.ylabel('|T| (dB)', fontsize=10, rotation='horizontal', loc='top')
plt.xscale('log')
plt.title(r'$T_1=\frac{V_1}{V_i}$', fontsize=15)
plt.legend(loc='best', shadow=False, fontsize='large')
plt.grid()
plt.show()