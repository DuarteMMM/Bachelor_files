import numpy as np
from numpy import *
import math
import matplotlib.pyplot as plt

U1=229.8
U2=299.8
U3=432.4

x=[U1, U2, U3]
y=[U2, U3, U1]

reta = linspace(0, 650, 100)

plt.plot(reta, reta, '--', c='black', linewidth=1)
plt.scatter(x, y, c='blue', linewidth=5)
plt.xlim(0, 650)
plt.ylim(0, 650)

plt.xlabel(r'$U_n(mV)$', fontsize=15, loc='right')
plt.ylabel(r'$U_{n+1}(mV)$', fontsize=15, rotation='horizontal', loc='top')
plt.xticks(np.arange(0, 650, 50))
plt.yticks(np.arange(0, 650, 50))
plt.title('Mapa de intervalo (Período 3)', fontsize=20)
plt.grid()
plt.show()