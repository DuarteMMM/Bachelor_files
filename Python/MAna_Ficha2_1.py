from numpy import *
import math
import matplotlib.pyplot as plt
import numpy

t = linspace(0, 10, 500)
m = 9.1E-31
a11 = 1
a12 = -1
a21 = 1
a22 = -1
a3 = 1
wb = 1
lambda_per = 2
lambda_par = 2

xvec = a11*m*(wb-lambda_per)*numpy.exp((wb-lambda_per)*t)+a12*m*(-(wb+lambda_per))*numpy.exp(-(wb+lambda_per)*t)
yvec = a21*m*(wb-lambda_per)*numpy.exp((wb-lambda_per)*t)+a22*m*(-(wb+lambda_per))*numpy.exp(-(wb+lambda_per)*t)
zvec = -a3*lambda_par*numpy.exp(-lambda_par*t)

plt.plot(t, xvec, 'r')
#plt.plot(z, b, 'b', label=r'$ \rho = 50\rho_{f}$')
#plt.plot(z, c, 'g', label=r'$ \rho = 100\rho_{f}$')
#plt.plot(z, d, 'y',label=r'$ \rho = 1000\rho_{f}$')

plt.ticklabel_format(axis="y", style="sci", scilimits=(0,0))
plt.xlabel(r'$t$', fontsize=10)
plt.ylabel(r'$p_z (t)$', fontsize=10)
#plt.title(r'$ \omega_B > \lambda $', fontsize=15)
#plt.legend(loc='best', shadow=False, fontsize='large')
plt.grid()
plt.show()