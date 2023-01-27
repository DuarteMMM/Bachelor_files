#Import necessary libraries
import numpy as np
from numpy import *
import math
import matplotlib.pyplot as plt

#Constants in SI units
M_r=580E3
t=100E-9
MR=2
R_min=1E3
I=0.1E-3
H_keff=2E3
l_z=2E-6
B=100E-6
h_B=B/2

N=100

#Vector for the sensor's length along x (l_x), now a variable
l_x = linspace(1E-9, 1E-2, 1000)

#x-value for which the sensor output voltage is maximum
#x_B = ((2*(N-2)+1)*B)/2 (suggested in the question) was not used;
#Instead, the previous code was ran for N=100 and the x-value for which DeltaV was maximum was determined:
x_B=0.0199042604260426

#Variable for the sensor output voltage
V_B=0

#Parameters for Simpson's method
n1=200
m1=200

x1_min=-l_x/2
x1_max=l_x/2
z1_min=-l_z/2
z1_max=l_z/2

h1=(x1_max-x1_min)/n1
k1=(z1_max-z1_min)/m1

#Calculate the several elements of the sum in the Simpson's method
x1=x1_min
z1=z1_min

for a in range (0, N):
    V_B+=(M_r/(4*math.pi)) * ( np.log ( ( (h_B+z1)**2 + (2*a*B-(x_B+x1))**2 ) / ( (t+h_B+z1)**2 + (2*a*B-(x_B+x1))**2 ) ) - np.log ( ( (h_B+z1)**2 + ((2*a+1)*B-(x_B+x1))**2 ) / ( (t+h_B+z1)**2 + ((2*a+1)*B-(x_B+x1))**2 ) ))

for i in range (1, int(n1/2-1+1)):
    x1=x1_min+(2*i)*h1
    for a in range (0, N):
        V_B+=((2*M_r)/(4*math.pi)) * ( np.log ( ( (h_B+z1)**2 + (2*a*B-(x_B+x1))**2 ) / ( (t+h_B+z1)**2 + (2*a*B-(x_B+x1))**2 ) ) - np.log ( ( (h_B+z1)**2 + ((2*a+1)*B-(x_B+x1))**2 ) / ( (t+h_B+z1)**2 + ((2*a+1)*B-(x_B+x1))**2 ) ))

for i in range (1, int(n1/2+1)):
    x1=x1_min+(2*i-1)*h1
    for a in range (0, N):
        V_B+=((4*M_r)/(4*math.pi)) * ( np.log ( ( (h_B+z1)**2 + (2*a*B-(x_B+x1))**2 ) / ( (t+h_B+z1)**2 + (2*a*B-(x_B+x1))**2 ) ) - np.log ( ( (h_B+z1)**2 + ((2*a+1)*B-(x_B+x1))**2 ) / ( (t+h_B+z1)**2 + ((2*a+1)*B-(x_B+x1))**2 ) ))

x1=x1_max

for a in range (0, N):
    V_B+=(M_r/(4*math.pi)) * ( np.log ( ( (h_B+z1)**2 + (2*a*B-(x_B+x1))**2 ) / ( (t+h_B+z1)**2 + (2*a*B-(x_B+x1))**2 ) ) - np.log ( ( (h_B+z1)**2 + ((2*a+1)*B-(x_B+x1))**2 ) / ( (t+h_B+z1)**2 + ((2*a+1)*B-(x_B+x1))**2 ) ))

x1=x1_min

for j in range (1, int(m1/2-1+1)):
    z1=z1_min+(2*j)*k1
    for a in range (0, N):
        V_B+=((2*M_r)/(4*math.pi)) * ( np.log ( ( (h_B+z1)**2 + (2*a*B-(x_B+x1))**2 ) / ( (t+h_B+z1)**2 + (2*a*B-(x_B+x1))**2 ) ) - np.log ( ( (h_B+z1)**2 + ((2*a+1)*B-(x_B+x1))**2 ) / ( (t+h_B+z1)**2 + ((2*a+1)*B-(x_B+x1))**2 ) ))

for j in range (1, int(m1/2-1+1)):
    z1=z1_min+(2*j)*k1
    for i in range (1, int(n1/2-1+1)):
        x1=x1_min+(2*i)*h1
        for a in range (0, N):
            V_B+=((4*M_r)/(4*math.pi)) * ( np.log ( ( (h_B+z1)**2 + (2*a*B-(x_B+x1))**2 ) / ( (t+h_B+z1)**2 + (2*a*B-(x_B+x1))**2 ) ) - np.log ( ( (h_B+z1)**2 + ((2*a+1)*B-(x_B+x1))**2 ) / ( (t+h_B+z1)**2 + ((2*a+1)*B-(x_B+x1))**2 ) ))

for j in range (1, int(m1/2-1+1)):
    z1=z1+(2*j)*k1
    for i in range (1, int(n1/2+1)):
        x1=x1_min+(2*i-1)*h1
        for a in range (0, N):
            V_B+=((8*M_r)/(4*math.pi)) * ( np.log ( ( (h_B+z1)**2 + (2*a*B-(x_B+x1))**2 ) / ( (t+h_B+z1)**2 + (2*a*B-(x_B+x1))**2 ) ) - np.log ( ( (h_B+z1)**2 + ((2*a+1)*B-(x_B+x1))**2 ) / ( (t+h_B+z1)**2 + ((2*a+1)*B-(x_B+x1))**2 ) ))

x1=x1_max

for j in range (1, int(m1/2-1+1)):
    z1=z1_min+(2*j)*k1
    for a in range (0, N):
        V_B+=((2*M_r)/(4*math.pi)) * ( np.log ( ( (h_B+z1)**2 + (2*a*B-(x_B+x1))**2 ) / ( (t+h_B+z1)**2 + (2*a*B-(x_B+x1))**2 ) ) - np.log ( ( (h_B+z1)**2 + ((2*a+1)*B-(x_B+x1))**2 ) / ( (t+h_B+z1)**2 + ((2*a+1)*B-(x_B+x1))**2 ) ))

x1=x1_min

for j in range (1, int(m1/2+1)):
    z1=z1_min+(2*j-1)*k1
    for a in range (0, N):
        V_B+=((4*M_r)/(4*math.pi)) * ( np.log ( ( (h_B+z1)**2 + (2*a*B-(x_B+x1))**2 ) / ( (t+h_B+z1)**2 + (2*a*B-(x_B+x1))**2 ) ) - np.log ( ( (h_B+z1)**2 + ((2*a+1)*B-(x_B+x1))**2 ) / ( (t+h_B+z1)**2 + ((2*a+1)*B-(x_B+x1))**2 ) ))

for j in range (1, int(m1/2+1)):
    z1=z1_min+(2*j-1)*k1
    for i in range (1, int(n1/2-1+1)):
        x1=x1_min+(2*i)*h1
        for a in range (0, N):
            V_B+=((8*M_r)/(4*math.pi)) * ( np.log ( ( (h_B+z1)**2 + (2*a*B-(x_B+x1))**2 ) / ( (t+h_B+z1)**2 + (2*a*B-(x_B+x1))**2 ) ) - np.log ( ( (h_B+z1)**2 + ((2*a+1)*B-(x_B+x1))**2 ) / ( (t+h_B+z1)**2 + ((2*a+1)*B-(x_B+x1))**2 ) ))

for j in range (1, int(m1/2+1)):
    z1=z1_min+(2*j-1)*k1
    for i in range (1, int(n1/2+1)):
        x1=x1_min+(2*i-1)*h1
        for a in range (0, N):
            V_B+=((16*M_r)/(4*math.pi)) * ( np.log ( ( (h_B+z1)**2 + (2*a*B-(x_B+x1))**2 ) / ( (t+h_B+z1)**2 + (2*a*B-(x_B+x1))**2 ) ) - np.log ( ( (h_B+z1)**2 + ((2*a+1)*B-(x_B+x1))**2 ) / ( (t+h_B+z1)**2 + ((2*a+1)*B-(x_B+x1))**2 ) ))

x1=x1_max

for j in range (1, int(m1/2+1)):
    z1=z1_min+(2*j-1)*k1
    for a in range (0, N):
        V_B+=((4*M_r)/(4*math.pi)) * ( np.log ( ( (h_B+z1)**2 + (2*a*B-(x_B+x1))**2 ) / ( (t+h_B+z1)**2 + (2*a*B-(x_B+x1))**2 ) ) - np.log ( ( (h_B+z1)**2 + ((2*a+1)*B-(x_B+x1))**2 ) / ( (t+h_B+z1)**2 + ((2*a+1)*B-(x_B+x1))**2 ) ))

x1=x1_min
z1=z1_max

for a in range (0, N):
    V_B+=(M_r/(4*math.pi)) * ( np.log ( ( (h_B+z1)**2 + (2*a*B-(x_B+x1))**2 ) / ( (t+h_B+z1)**2 + (2*a*B-(x_B+x1))**2 ) ) - np.log ( ( (h_B+z1)**2 + ((2*a+1)*B-(x_B+x1))**2 ) / ( (t+h_B+z1)**2 + ((2*a+1)*B-(x_B+x1))**2 ) ))

for i in range (1, int(n1/2-1+1)):
    x1=x1_min+(2*i)*h1
    for a in range (0, N):
        V_B+=((2*M_r)/(4*math.pi)) * ( np.log ( ( (h_B+z1)**2 + (2*a*B-(x_B+x1))**2 ) / ( (t+h_B+z1)**2 + (2*a*B-(x_B+x1))**2 ) ) - np.log ( ( (h_B+z1)**2 + ((2*a+1)*B-(x_B+x1))**2 ) / ( (t+h_B+z1)**2 + ((2*a+1)*B-(x_B+x1))**2 ) ))

for i in range (1, int(n1/2+1)):
    x1=x1_min+(2*i-1)*h1
    for a in range (0, N):
        V_B+=((4*M_r)/(4*math.pi)) * ( np.log ( ( (h_B+z1)**2 + (2*a*B-(x_B+x1))**2 ) / ( (t+h_B+z1)**2 + (2*a*B-(x_B+x1))**2 ) ) - np.log ( ( (h_B+z1)**2 + ((2*a+1)*B-(x_B+x1))**2 ) / ( (t+h_B+z1)**2 + ((2*a+1)*B-(x_B+x1))**2 ) ))

x1=x1_max

for a in range (0, N):
    V_B+=(M_r/(4*math.pi)) * ( np.log ( ( (h_B+z1)**2 + (2*a*B-(x_B+x1))**2 ) / ( (t+h_B+z1)**2 + (2*a*B-(x_B+x1))**2 ) ) - np.log ( ( (h_B+z1)**2 + ((2*a+1)*B-(x_B+x1))**2 ) / ( (t+h_B+z1)**2 + ((2*a+1)*B-(x_B+x1))**2 ) ))

V_B*=((h1*k1)/9)
V_B*=(1/(l_x*l_z))*((MR*R_min*I)/(2*H_keff))

#Graph
plt.plot(l_x, V_B*1E3, 'r')
plt.xlabel(r'$l_x$ (m)', fontsize=14, loc='right')
plt.ylabel(r'$\Delta$V ($\cdot10^{-3}$ V)', fontsize=14, rotation='horizontal', loc='top')
plt.title(r'Question 4: $\Delta$V($l_x$) for N=100', fontsize=15)
plt.grid()
plt.show()

#l_x for which DeltaV is no longer constant (seen with Python cursor): l_x=1E-5 (approximately)