import numpy as np
from numpy import *
import math
import matplotlib.pyplot as plt

U1=443.3
U2=502.3
U3=419.6
U4=93.43
U5=454.4
U6=439.7
U7=502.3
U8=506.5
U9=97.12
U10=465.4
U11=454.4
U12=402.3
U13=417.6
U14=75.02
U15=461.8
U16=436.0


x=[U1, U2, U3, U4, U5, U6, U7, U8, U9, U10, U11, U12, U13, U14, U15, U16]
y=[U2, U3, U4, U5, U6, U7, U8, U9, U10, U11, U12, U13, U14, U15, U16, U1]

reta = linspace(50, 600, 100)

plt.plot(reta, reta, '--', c='black', linewidth=1)
plt.scatter(x, y, c='blue', linewidth=5)
plt.xlim(50, 600)
plt.ylim(50, 600)

plt.xlabel(r'$U_n(mV)$', fontsize=15, loc='right')
plt.ylabel(r'$U_{n+1}(mV)$', fontsize=15, rotation='horizontal', loc='top')
plt.xticks(np.arange(50, 600, 50))
plt.yticks(np.arange(50, 600, 50))
plt.title('Mapa de intervalo (Período 16)', fontsize=20)
plt.grid()
plt.show()