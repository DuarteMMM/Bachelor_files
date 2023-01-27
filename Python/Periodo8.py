import numpy as np
from numpy import *
import math
import matplotlib.pyplot as plt

U1=338.1+86.84
U2=373.4+86.84
U3=428.6+86.84
U4=351.3+86.84
U5=391.8+86.84
U6=377.0+86.84
U7=424.9+86.84
U8=351.3+86.84


x=[U1, U2, U3, U4, U5, U6, U7, U8]
y=[U2, U3, U4, U5, U6, U7, U8, U1]

reta = linspace(300, 650, 100)

plt.plot(reta, reta, '--', c='black', linewidth=1)
plt.scatter(x, y, c='blue', linewidth=5)
plt.xlim(300, 600)
plt.ylim(300, 600)

plt.xlabel(r'$U_n(mV)$', fontsize=15, loc='right')
plt.ylabel(r'$U_{n+1}(mV)$', fontsize=15, rotation='horizontal', loc='top')
plt.xticks(np.arange(300, 600, 50))
plt.yticks(np.arange(300, 600, 50))
plt.title('Mapa de intervalo (Período 8)', fontsize=20)
plt.grid()
plt.show()