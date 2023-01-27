import numpy as np
from numpy import *
import math
import matplotlib.pyplot as plt

U1=112.9+142.3
U2=325.4+142.3
U3=135.7+142.3
U4=344.4+142.3

x=[U1, U2, U3, U4]
y=[U2, U3, U4, U1]

reta = linspace(200, 650, 100)

plt.plot(reta, reta, '--', c='black', linewidth=1)
plt.scatter(x, y, c='blue', linewidth=5)
plt.xlim(200, 650)
plt.ylim(200, 650)

plt.xlabel(r'$U_n(mV)$', fontsize=15, loc='right')
plt.ylabel(r'$U_{n+1}(mV)$', fontsize=15, rotation='horizontal', loc='top')
plt.xticks(np.arange(200, 650, 50))
plt.yticks(np.arange(200, 650, 50))
plt.title('Mapa de intervalo (Período 4)', fontsize=20)
plt.grid()
plt.show()