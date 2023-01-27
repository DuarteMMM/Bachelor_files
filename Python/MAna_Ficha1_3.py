from numpy import *
import math
import matplotlib.pyplot as plt

x = linspace(0.0001,1000, 400)
h = 1
R = 1
g = 9.8

ro = 10
ro_f = 1
a = -math.pi*h*R*R*ro*g*z+(math.pi/2)*ro_f*g*R*R*z*z

ro = 50
b = -math.pi*h*R*R*ro*g*z+(math.pi/2)*ro_f*g*R*R*z*z

ro = 100
c = -math.pi*h*R*R*ro*g*z+(math.pi/2)*ro_f*g*R*R*z*z

ro = 1000
d = -math.pi*h*R*R*ro*g*z+(math.pi/2)*ro_f*g*R*R*z*z


plt.plot(z, a, 'r', label=r'$ \rho = 10 \rho_{f}$')
plt.plot(z, b, 'b', label=r'$ \rho = 50\rho_{f}$')
plt.plot(z, c, 'g', label=r'$ \rho = 100\rho_{f}$')
plt.plot(z, d, 'y',label=r'$ \rho = 1000\rho_{f}$')

plt.ticklabel_format(axis="y", style="sci", scilimits=(0,0))
plt.xlabel('z', fontsize=10)
plt.ylabel('$V_{ef}$', fontsize=10)
plt.title(r'$ \rho > \rho_{f} $', fontsize=15)
plt.legend(loc='best', shadow=False, fontsize='large')
plt.grid()
plt.show()