from numpy import *
import math
import matplotlib.pyplot as plt

z = linspace(-1, 1, 400)
h = 1
R = 1
g = 9.8

ro_f = 10
ro = 1
a = -math.pi*h*R*R*ro*g*z+(math.pi/2)*ro_f*g*R*R*z*z

ro_f = 50
b = -math.pi*h*R*R*ro*g*z+(math.pi/2)*ro_f*g*R*R*z*z

ro_f = 100
c = -math.pi*h*R*R*ro*g*z+(math.pi/2)*ro_f*g*R*R*z*z

ro_f = 1000
d = -math.pi*h*R*R*ro*g*z+(math.pi/2)*ro_f*g*R*R*z*z


plt.plot(z, a, 'r', label=r'$ \rho_{f} = 10 \rho$')
plt.plot(z, b, 'b', label=r'$ \rho_{f} = 50\rho$')
plt.plot(z, c, 'g', label=r'$ \rho_{f} = 100\rho$')
#plt.plot(z, d, 'y',label=r'$ \rho = 1000\rho_{f}$')

plt.ticklabel_format(axis="y", style="sci", scilimits=(0,0))
plt.xlabel('z', fontsize=10)
plt.ylabel('$V_{ef}$', fontsize=10)
plt.title(r'$ \rho_{f} > \rho $', fontsize=15)
plt.legend(loc='best', shadow=False, fontsize='large')
plt.grid()
plt.show()