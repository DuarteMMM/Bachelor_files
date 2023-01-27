from numpy import *
import math
import matplotlib.pyplot as plt

z = linspace(-10, 30 , 400)
h = 1
R = 1
g = 9.8

ro = 10
ro_f = 1
a1 = -math.pi*h*R*R*ro*g*z+(math.pi/2)*ro_f*g*R*R*z*z

ro = 15
ro_f = 1
b1 = -math.pi*h*R*R*ro*g*z+(math.pi/2)*ro_f*g*R*R*z*z

ro = 100
ro_f = 1
c1 = -math.pi*h*R*R*ro*g*z+(math.pi/2)*ro_f*g*R*R*z*z

ro = 1000
ro_f = 1
d1 = -math.pi*h*R*R*ro*g*z+(math.pi/2)*ro_f*g*R*R*z*z

ro_f = 10
ro = 1
a2 = -math.pi*h*R*R*ro*g*z+(math.pi/2)*ro_f*g*R*R*z*z

ro_f = 15
ro = 1
b2 = -math.pi*h*R*R*ro*g*z+(math.pi/2)*ro_f*g*R*R*z*z

ro_f = 100
ro = 1
c2 = -math.pi*h*R*R*ro*g*z+(math.pi/2)*ro_f*g*R*R*z*z

ro_f = 1000
ro = 1
d2 = -math.pi*h*R*R*ro*g*z+(math.pi/2)*ro_f*g*R*R*z*z

plt.plot(z, a1, 'r', label=r'$ \rho = 10 \rho_{f}$')
plt.plot(z, b1, 'b', label=r'$ \rho = 20\rho_{f}$')
#plt.plot(z, c1, 'g', label=r'$ \rho_{f} = 100\rho$')
#plt.plot(z, d1, 'y',label=r'$ \rho_{f} = 1000\rho$')

plt.plot(z, a2, 'r', linestyle='dashed', label=r'$ \rho_{f} = 10 \rho$')
plt.plot(z, b2, 'b', linestyle='dashed', label=r'$ \rho_{f} = 20\rho$')
#plt.plot(z, c2, 'g', linestyle='dashed', label=r'$ \rho_{f} = 100\rho$')
#plt.plot(z, d2, 'y',label=r'$ \rho_{f} = 1000\rho$')

axes = plt.gca()
axes.set_ylim([-7000,20000])

plt.ticklabel_format(axis="y", style="sci", scilimits=(0,0))
plt.xlabel('z', fontsize=10)
plt.ylabel('$V_{ef}$', fontsize=10)
plt.title("Representação conjunta", fontsize=15)
plt.legend(loc='best', shadow=False, fontsize='large')
plt.grid()
plt.show()