#Import necessary libraries
import numpy as np
from numpy import *
import math
import matplotlib.pyplot as plt

#Link: https://ahmedbadary.github.io/work_files/school/128a/4_8

#Constants in SI units
M_r=580E3
t=100E-9
MR=2
R_min=1E3
I=0.1E-3
H_keff=2E3

l_x=20E-6
l_z=2E-6

###For B=B1=10um
B1=10E-6
h_B1=B1/2

#Vector of the x-coordinate
x_B1 = linspace(-5*B1, 5*B1, 10000)

#Variable for the sensor output voltage 
V_B1=0

#Parameters for Simpson's method
n1=10
m1=10

x1_min=-l_x/2
x1_max=l_x/2
z1_min=-l_z/2
z1_max=l_z/2

h1=(x1_max-x1_min)/n1
k1=(z1_max-z1_min)/m1

#Calculate the several elements of the sum in the Simpson's method
x1=x1_min
z1=z1_min

V_B1+=(M_r/(4*math.pi)) * ( np.log ( ( (h_B1+z1)**2 + (x_B1+x1)**2 ) / ( (t+h_B1+z1)**2 + (x_B1+x1)**2 ) ) - np.log ( ( (h_B1+z1)**2 + (B1-(x_B1+x1))**2 ) / ( (t+h_B1+z1)**2 + (B1-(x_B1+x1))**2 ) ))

for i in range (1, int(n1/2-1+1)):
    x1=x1_min+(2*i)*h1
    V_B1+=((2*M_r)/(4*math.pi)) * ( np.log ( ( (h_B1+z1)**2 + (x_B1+x1)**2 ) / ( (t+h_B1+z1)**2 + (x_B1+x1)**2 ) ) - np.log ( ( (h_B1+z1)**2 + (B1-(x_B1+x1))**2 ) / ( (t+h_B1+z1)**2 + (B1-(x_B1+x1))**2 ) ))

for i in range (1, int(n1/2+1)):
    x1=x1_min+(2*i-1)*h1
    V_B1+=((4*M_r)/(4*math.pi)) * ( np.log ( ( (h_B1+z1)**2 + (x_B1+x1)**2 ) / ( (t+h_B1+z1)**2 + (x_B1+x1)**2 ) ) - np.log ( ( (h_B1+z1)**2 + (B1-(x_B1+x1))**2 ) / ( (t+h_B1+z1)**2 + (B1-(x_B1+x1))**2 ) ))

x1=x1_max
V_B1+=(M_r/(4*math.pi)) * ( np.log ( ( (h_B1+z1)**2 + (x_B1+x1)**2 ) / ( (t+h_B1+z1)**2 + (x_B1+x1)**2 ) ) - np.log ( ( (h_B1+z1)**2 + (B1-(x_B1+x1))**2 ) / ( (t+h_B1+z1)**2 + (B1-(x_B1+x1))**2 ) ))

x1=x1_min

for j in range (1, int(m1/2-1+1)):
    z1=z1_min+(2*j)*k1
    V_B1+=((2*M_r)/(4*math.pi)) * ( np.log ( ( (h_B1+z1)**2 + (x_B1+x1)**2 ) / ( (t+h_B1+z1)**2 + (x_B1+x1)**2 ) ) - np.log ( ( (h_B1+z1)**2 + (B1-(x_B1+x1))**2 ) / ( (t+h_B1+z1)**2 + (B1-(x_B1+x1))**2 ) ))

for j in range (1, int(m1/2-1+1)):
    z1=z1_min+(2*j)*k1
    for i in range (1, int(n1/2-1+1)):
        x1=x1_min+(2*i)*h1
        V_B1+=((4*M_r)/(4*math.pi)) * ( np.log ( ( (h_B1+z1)**2 + (x_B1+x1)**2 ) / ( (t+h_B1+z1)**2 + (x_B1+x1)**2 ) ) - np.log ( ( (h_B1+z1)**2 + (B1-(x_B1+x1))**2 ) / ( (t+h_B1+z1)**2 + (B1-(x_B1+x1))**2 ) ))

for j in range (1, int(m1/2-1+1)):
    z1=z1+(2*j)*k1
    for i in range (1, int(n1/2+1)):
        x1=x1_min+(2*i-1)*h1
        V_B1+=((8*M_r)/(4*math.pi)) * ( np.log ( ( (h_B1+z1)**2 + (x_B1+x1)**2 ) / ( (t+h_B1+z1)**2 + (x_B1+x1)**2 ) ) - np.log ( ( (h_B1+z1)**2 + (B1-(x_B1+x1))**2 ) / ( (t+h_B1+z1)**2 + (B1-(x_B1+x1))**2 ) ))

x1=x1_max

for j in range (1, int(m1/2-1+1)):
    z1=z1_min+(2*j)*k1
    V_B1+=((2*M_r)/(4*math.pi)) * ( np.log ( ( (h_B1+z1)**2 + (x_B1+x1)**2 ) / ( (t+h_B1+z1)**2 + (x_B1+x1)**2 ) ) - np.log ( ( (h_B1+z1)**2 + (B1-(x_B1+x1))**2 ) / ( (t+h_B1+z1)**2 + (B1-(x_B1+x1))**2 ) ))

x1=x1_min

for j in range (1, int(m1/2+1)):
    z1=z1_min+(2*j-1)*k1
    V_B1+=((4*M_r)/(4*math.pi)) * ( np.log ( ( (h_B1+z1)**2 + (x_B1+x1)**2 ) / ( (t+h_B1+z1)**2 + (x_B1+x1)**2 ) ) - np.log ( ( (h_B1+z1)**2 + (B1-(x_B1+x1))**2 ) / ( (t+h_B1+z1)**2 + (B1-(x_B1+x1))**2 ) ))

for j in range (1, int(m1/2+1)):
    z1=z1_min+(2*j-1)*k1
    for i in range (1, int(n1/2-1+1)):
        x1=x1_min+(2*i)*h1
        V_B1+=((8*M_r)/(4*math.pi)) * ( np.log ( ( (h_B1+z1)**2 + (x_B1+x1)**2 ) / ( (t+h_B1+z1)**2 + (x_B1+x1)**2 ) ) - np.log ( ( (h_B1+z1)**2 + (B1-(x_B1+x1))**2 ) / ( (t+h_B1+z1)**2 + (B1-(x_B1+x1))**2 ) ))

for j in range (1, int(m1/2+1)):
    z1=z1_min+(2*j-1)*k1
    for i in range (1, int(n1/2+1)):
        x1=x1_min+(2*i-1)*h1
        V_B1+=((16*M_r)/(4*math.pi)) * ( np.log ( ( (h_B1+z1)**2 + (x_B1+x1)**2 ) / ( (t+h_B1+z1)**2 + (x_B1+x1)**2 ) ) - np.log ( ( (h_B1+z1)**2 + (B1-(x_B1+x1))**2 ) / ( (t+h_B1+z1)**2 + (B1-(x_B1+x1))**2 ) ))

x1=x1_max

for j in range (1, int(m1/2+1)):
    z1=z1_min+(2*j-1)*k1
    V_B1+=((4*M_r)/(4*math.pi)) * ( np.log ( ( (h_B1+z1)**2 + (x_B1+x1)**2 ) / ( (t+h_B1+z1)**2 + (x_B1+x1)**2 ) ) - np.log ( ( (h_B1+z1)**2 + (B1-(x_B1+x1))**2 ) / ( (t+h_B1+z1)**2 + (B1-(x_B1+x1))**2 ) ))

x1=x1_min
z1=z1_max

V_B1+=(M_r/(4*math.pi)) * ( np.log ( ( (h_B1+z1)**2 + (x_B1+x1)**2 ) / ( (t+h_B1+z1)**2 + (x_B1+x1)**2 ) ) - np.log ( ( (h_B1+z1)**2 + (B1-(x_B1+x1))**2 ) / ( (t+h_B1+z1)**2 + (B1-(x_B1+x1))**2 ) ))

for i in range (1, int(n1/2-1+1)):
    x1=x1_min+(2*i)*h1
    V_B1+=((2*M_r)/(4*math.pi)) * ( np.log ( ( (h_B1+z1)**2 + (x_B1+x1)**2 ) / ( (t+h_B1+z1)**2 + (x_B1+x1)**2 ) ) - np.log ( ( (h_B1+z1)**2 + (B1-(x_B1+x1))**2 ) / ( (t+h_B1+z1)**2 + (B1-(x_B1+x1))**2 ) ))

for i in range (1, int(n1/2+1)):
    x1=x1_min+(2*i-1)*h1
    V_B1+=((4*M_r)/(4*math.pi)) * ( np.log ( ( (h_B1+z1)**2 + (x_B1+x1)**2 ) / ( (t+h_B1+z1)**2 + (x_B1+x1)**2 ) ) - np.log ( ( (h_B1+z1)**2 + (B1-(x_B1+x1))**2 ) / ( (t+h_B1+z1)**2 + (B1-(x_B1+x1))**2 ) ))

x1=x1_max

V_B1+=(M_r/(4*math.pi)) * ( np.log ( ( (h_B1+z1)**2 + (x_B1+x1)**2 ) / ( (t+h_B1+z1)**2 + (x_B1+x1)**2 ) ) - np.log ( ( (h_B1+z1)**2 + (B1-(x_B1+x1))**2 ) / ( (t+h_B1+z1)**2 + (B1-(x_B1+x1))**2 ) ))

V_B1*=((h1*k1)/9)
V_B1*=(1/(l_x*l_z))*((MR*R_min*I)/(2*H_keff))

###Same process, but for B=B2=100um
B2=100E-6
h_B2=B2/2
x_B2 = linspace(-5*B2, 5*B2, 10000)
V_B2=0
n2=10
m2=10
h2=(x1_max-x1_min)/n2
k2=(z1_max-z1_min)/m2

x1=x1_min
z1=z1_min

V_B2+=(M_r/(4*math.pi)) * ( np.log ( ( (h_B2+z1)**2 + (x_B2+x1)**2 ) / ( (t+h_B2+z1)**2 + (x_B2+x1)**2 ) ) - np.log ( ( (h_B2+z1)**2 + (B2-(x_B2+x1))**2 ) / ( (t+h_B2+z1)**2 + (B2-(x_B2+x1))**2 ) ))

for i in range (1, int(n2/2-1+1)):
    x1=x1_min+(2*i)*h2
    V_B2+=((2*M_r)/(4*math.pi)) * ( np.log ( ( (h_B2+z1)**2 + (x_B2+x1)**2 ) / ( (t+h_B2+z1)**2 + (x_B2+x1)**2 ) ) - np.log ( ( (h_B2+z1)**2 + (B2-(x_B2+x1))**2 ) / ( (t+h_B2+z1)**2 + (B2-(x_B2+x1))**2 ) ))

for i in range (1, int(n2/2+1)):
    x1=x1_min+(2*i-1)*h2
    V_B2+=((4*M_r)/(4*math.pi)) * ( np.log ( ( (h_B2+z1)**2 + (x_B2+x1)**2 ) / ( (t+h_B2+z1)**2 + (x_B2+x1)**2 ) ) - np.log ( ( (h_B2+z1)**2 + (B2-(x_B2+x1))**2 ) / ( (t+h_B2+z1)**2 + (B2-(x_B2+x1))**2 ) ))

x1=x1_max
V_B2+=(M_r/(4*math.pi)) * ( np.log ( ( (h_B2+z1)**2 + (x_B2+x1)**2 ) / ( (t+h_B2+z1)**2 + (x_B2+x1)**2 ) ) - np.log ( ( (h_B2+z1)**2 + (B2-(x_B2+x1))**2 ) / ( (t+h_B2+z1)**2 + (B2-(x_B2+x1))**2 ) ))

x1=x1_min

for j in range (1, int(m2/2-1+1)):
    z1=z1_min+(2*j)*k2
    V_B2+=((2*M_r)/(4*math.pi)) * ( np.log ( ( (h_B2+z1)**2 + (x_B2+x1)**2 ) / ( (t+h_B2+z1)**2 + (x_B2+x1)**2 ) ) - np.log ( ( (h_B2+z1)**2 + (B2-(x_B2+x1))**2 ) / ( (t+h_B2+z1)**2 + (B2-(x_B2+x1))**2 ) ))

for j in range (1, int(m2/2-1+1)):
    z1=z1_min+(2*j)*k2
    for i in range (1, int(n2/2-1+1)):
        x1=x1_min+(2*i)*h2
        V_B2+=((4*M_r)/(4*math.pi)) * ( np.log ( ( (h_B2+z1)**2 + (x_B2+x1)**2 ) / ( (t+h_B2+z1)**2 + (x_B2+x1)**2 ) ) - np.log ( ( (h_B2+z1)**2 + (B2-(x_B2+x1))**2 ) / ( (t+h_B2+z1)**2 + (B2-(x_B2+x1))**2 ) ))

for j in range (1, int(m2/2-1+1)):
    z1=z1+(2*j)*k2
    for i in range (1, int(n2/2+1)):
        x1=x1_min+(2*i-1)*h2
        V_B2+=((8*M_r)/(4*math.pi)) * ( np.log ( ( (h_B2+z1)**2 + (x_B2+x1)**2 ) / ( (t+h_B2+z1)**2 + (x_B2+x1)**2 ) ) - np.log ( ( (h_B2+z1)**2 + (B2-(x_B2+x1))**2 ) / ( (t+h_B2+z1)**2 + (B2-(x_B2+x1))**2 ) ))

x1=x1_max

for j in range (1, int(m2/2-1+1)):
    z1=z1_min+(2*j)*k2
    V_B2+=((2*M_r)/(4*math.pi)) * ( np.log ( ( (h_B2+z1)**2 + (x_B2+x1)**2 ) / ( (t+h_B2+z1)**2 + (x_B2+x1)**2 ) ) - np.log ( ( (h_B2+z1)**2 + (B2-(x_B2+x1))**2 ) / ( (t+h_B2+z1)**2 + (B2-(x_B2+x1))**2 ) ))

x1=x1_min

for j in range (1, int(m2/2+1)):
    z1=z1_min+(2*j-1)*k2
    V_B2+=((4*M_r)/(4*math.pi)) * ( np.log ( ( (h_B2+z1)**2 + (x_B2+x1)**2 ) / ( (t+h_B2+z1)**2 + (x_B2+x1)**2 ) ) - np.log ( ( (h_B2+z1)**2 + (B2-(x_B2+x1))**2 ) / ( (t+h_B2+z1)**2 + (B2-(x_B2+x1))**2 ) ))

for j in range (1, int(m2/2+1)):
    z1=z1_min+(2*j-1)*k2
    for i in range (1, int(n2/2-1+1)):
        x1=x1_min+(2*i)*h2
        V_B2+=((8*M_r)/(4*math.pi)) * ( np.log ( ( (h_B2+z1)**2 + (x_B2+x1)**2 ) / ( (t+h_B2+z1)**2 + (x_B2+x1)**2 ) ) - np.log ( ( (h_B2+z1)**2 + (B2-(x_B2+x1))**2 ) / ( (t+h_B2+z1)**2 + (B2-(x_B2+x1))**2 ) ))

for j in range (1, int(m2/2+1)):
    z1=z1_min+(2*j-1)*k2
    for i in range (1, int(n2/2+1)):
        x1=x1_min+(2*i-1)*h2
        V_B2+=((16*M_r)/(4*math.pi)) * ( np.log ( ( (h_B2+z1)**2 + (x_B2+x1)**2 ) / ( (t+h_B2+z1)**2 + (x_B2+x1)**2 ) ) - np.log ( ( (h_B2+z1)**2 + (B2-(x_B2+x1))**2 ) / ( (t+h_B2+z1)**2 + (B2-(x_B2+x1))**2 ) ))

x1=x1_max

for j in range (1, int(m2/2+1)):
    z1=z1_min+(2*j-1)*k2
    V_B2+=((4*M_r)/(4*math.pi)) * ( np.log ( ( (h_B2+z1)**2 + (x_B2+x1)**2 ) / ( (t+h_B2+z1)**2 + (x_B2+x1)**2 ) ) - np.log ( ( (h_B2+z1)**2 + (B2-(x_B2+x1))**2 ) / ( (t+h_B2+z1)**2 + (B2-(x_B2+x1))**2 ) ))

x1=x1_min
z1=z1_max

V_B2+=(M_r/(4*math.pi)) * ( np.log ( ( (h_B2+z1)**2 + (x_B2+x1)**2 ) / ( (t+h_B2+z1)**2 + (x_B2+x1)**2 ) ) - np.log ( ( (h_B2+z1)**2 + (B2-(x_B2+x1))**2 ) / ( (t+h_B2+z1)**2 + (B2-(x_B2+x1))**2 ) ))

for i in range (1, int(n2/2-1+1)):
    x1=x1_min+(2*i)*h2
    V_B2+=((2*M_r)/(4*math.pi)) * ( np.log ( ( (h_B2+z1)**2 + (x_B2+x1)**2 ) / ( (t+h_B2+z1)**2 + (x_B2+x1)**2 ) ) - np.log ( ( (h_B2+z1)**2 + (B2-(x_B2+x1))**2 ) / ( (t+h_B2+z1)**2 + (B2-(x_B2+x1))**2 ) ))

for i in range (1, int(n2/2+1)):
    x1=x1_min+(2*i-1)*h2
    V_B2+=((4*M_r)/(4*math.pi)) * ( np.log ( ( (h_B2+z1)**2 + (x_B2+x1)**2 ) / ( (t+h_B2+z1)**2 + (x_B2+x1)**2 ) ) - np.log ( ( (h_B2+z1)**2 + (B2-(x_B2+x1))**2 ) / ( (t+h_B2+z1)**2 + (B2-(x_B2+x1))**2 ) ))

x1=x1_max

V_B2+=(M_r/(4*math.pi)) * ( np.log ( ( (h_B2+z1)**2 + (x_B2+x1)**2 ) / ( (t+h_B2+z1)**2 + (x_B2+x1)**2 ) ) - np.log ( ( (h_B2+z1)**2 + (B2-(x_B2+x1))**2 ) / ( (t+h_B2+z1)**2 + (B2-(x_B2+x1))**2 ) ))

V_B2*=((h2*k2)/9)
V_B2*=(1/(l_x*l_z))*((MR*R_min*I)/(2*H_keff))

###Same process, but for B=B3=1mm
B3=1E-3
h_B3=B3/2
x_B3 = linspace(-5*B3, 5*B3, 10000)
V_B3=0
n3=10
m3=10
h3=(x1_max-x1_min)/n3
k3=(z1_max-z1_min)/m3

x1=x1_min
z1=z1_min

V_B3+=(M_r/(4*math.pi)) * ( np.log ( ( (h_B3+z1)**2 + (x_B3+x1)**2 ) / ( (t+h_B3+z1)**2 + (x_B3+x1)**2 ) ) - np.log ( ( (h_B3+z1)**2 + (B3-(x_B3+x1))**2 ) / ( (t+h_B3+z1)**2 + (B3-(x_B3+x1))**2 ) ))

for i in range (1, int(n3/2-1+1)):
    x1=x1_min+(2*i)*h3
    V_B3+=((2*M_r)/(4*math.pi)) * ( np.log ( ( (h_B3+z1)**2 + (x_B3+x1)**2 ) / ( (t+h_B3+z1)**2 + (x_B3+x1)**2 ) ) - np.log ( ( (h_B3+z1)**2 + (B3-(x_B3+x1))**2 ) / ( (t+h_B3+z1)**2 + (B3-(x_B3+x1))**2 ) ))

for i in range (1, int(n3/2+1)):
    x1=x1_min+(2*i-1)*h3
    V_B3+=((4*M_r)/(4*math.pi)) * ( np.log ( ( (h_B3+z1)**2 + (x_B3+x1)**2 ) / ( (t+h_B3+z1)**2 + (x_B3+x1)**2 ) ) - np.log ( ( (h_B3+z1)**2 + (B3-(x_B3+x1))**2 ) / ( (t+h_B3+z1)**2 + (B3-(x_B3+x1))**2 ) ))

x1=x1_max
V_B3+=(M_r/(4*math.pi)) * ( np.log ( ( (h_B3+z1)**2 + (x_B3+x1)**2 ) / ( (t+h_B3+z1)**2 + (x_B3+x1)**2 ) ) - np.log ( ( (h_B3+z1)**2 + (B3-(x_B3+x1))**2 ) / ( (t+h_B3+z1)**2 + (B3-(x_B3+x1))**2 ) ))

x1=x1_min

for j in range (1, int(m3/2-1+1)):
    z1=z1_min+(2*j)*k3
    V_B3+=((2*M_r)/(4*math.pi)) * ( np.log ( ( (h_B3+z1)**2 + (x_B3+x1)**2 ) / ( (t+h_B3+z1)**2 + (x_B3+x1)**2 ) ) - np.log ( ( (h_B3+z1)**2 + (B3-(x_B3+x1))**2 ) / ( (t+h_B3+z1)**2 + (B3-(x_B3+x1))**2 ) ))

for j in range (1, int(m3/2-1+1)):
    z1=z1_min+(2*j)*k3
    for i in range (1, int(n3/2-1+1)):
        x1=x1_min+(2*i)*h3
        V_B3+=((4*M_r)/(4*math.pi)) * ( np.log ( ( (h_B3+z1)**2 + (x_B3+x1)**2 ) / ( (t+h_B3+z1)**2 + (x_B3+x1)**2 ) ) - np.log ( ( (h_B3+z1)**2 + (B3-(x_B3+x1))**2 ) / ( (t+h_B3+z1)**2 + (B3-(x_B3+x1))**2 ) ))

for j in range (1, int(m3/2-1+1)):
    z1=z1+(2*j)*k3
    for i in range (1, int(n3/2+1)):
        x1=x1_min+(2*i-1)*h3
        V_B3+=((8*M_r)/(4*math.pi)) * ( np.log ( ( (h_B3+z1)**2 + (x_B3+x1)**2 ) / ( (t+h_B3+z1)**2 + (x_B3+x1)**2 ) ) - np.log ( ( (h_B3+z1)**2 + (B3-(x_B3+x1))**2 ) / ( (t+h_B3+z1)**2 + (B3-(x_B3+x1))**2 ) ))

x1=x1_max

for j in range (1, int(m3/2-1+1)):
    z1=z1_min+(2*j)*k3
    V_B3+=((2*M_r)/(4*math.pi)) * ( np.log ( ( (h_B3+z1)**2 + (x_B3+x1)**2 ) / ( (t+h_B3+z1)**2 + (x_B3+x1)**2 ) ) - np.log ( ( (h_B3+z1)**2 + (B3-(x_B3+x1))**2 ) / ( (t+h_B3+z1)**2 + (B3-(x_B3+x1))**2 ) ))

x1=x1_min

for j in range (1, int(m3/2+1)):
    z1=z1_min+(2*j-1)*k3
    V_B3+=((4*M_r)/(4*math.pi)) * ( np.log ( ( (h_B3+z1)**2 + (x_B3+x1)**2 ) / ( (t+h_B3+z1)**2 + (x_B3+x1)**2 ) ) - np.log ( ( (h_B3+z1)**2 + (B3-(x_B3+x1))**2 ) / ( (t+h_B3+z1)**2 + (B3-(x_B3+x1))**2 ) ))

for j in range (1, int(m3/2+1)):
    z1=z1_min+(2*j-1)*k3
    for i in range (1, int(n3/2-1+1)):
        x1=x1_min+(2*i)*h3
        V_B3+=((8*M_r)/(4*math.pi)) * ( np.log ( ( (h_B3+z1)**2 + (x_B3+x1)**2 ) / ( (t+h_B3+z1)**2 + (x_B3+x1)**2 ) ) - np.log ( ( (h_B3+z1)**2 + (B3-(x_B3+x1))**2 ) / ( (t+h_B3+z1)**2 + (B3-(x_B3+x1))**2 ) ))

for j in range (1, int(m3/2+1)):
    z1=z1_min+(2*j-1)*k3
    for i in range (1, int(n3/2+1)):
        x1=x1_min+(2*i-1)*h3
        V_B3+=((16*M_r)/(4*math.pi)) * ( np.log ( ( (h_B3+z1)**2 + (x_B3+x1)**2 ) / ( (t+h_B3+z1)**2 + (x_B3+x1)**2 ) ) - np.log ( ( (h_B3+z1)**2 + (B3-(x_B3+x1))**2 ) / ( (t+h_B3+z1)**2 + (B3-(x_B3+x1))**2 ) ))

x1=x1_max

for j in range (1, int(m3/2+1)):
    z1=z1_min+(2*j-1)*k3
    V_B3+=((4*M_r)/(4*math.pi)) * ( np.log ( ( (h_B3+z1)**2 + (x_B3+x1)**2 ) / ( (t+h_B3+z1)**2 + (x_B3+x1)**2 ) ) - np.log ( ( (h_B3+z1)**2 + (B3-(x_B3+x1))**2 ) / ( (t+h_B3+z1)**2 + (B3-(x_B3+x1))**2 ) ))

x1=x1_min
z1=z1_max

V_B3+=(M_r/(4*math.pi)) * ( np.log ( ( (h_B3+z1)**2 + (x_B3+x1)**2 ) / ( (t+h_B3+z1)**2 + (x_B3+x1)**2 ) ) - np.log ( ( (h_B3+z1)**2 + (B3-(x_B3+x1))**2 ) / ( (t+h_B3+z1)**2 + (B3-(x_B3+x1))**2 ) ))

for i in range (1, int(n3/2-1+1)):
    x1=x1_min+(2*i)*h3
    V_B3+=((2*M_r)/(4*math.pi)) * ( np.log ( ( (h_B3+z1)**2 + (x_B3+x1)**2 ) / ( (t+h_B3+z1)**2 + (x_B3+x1)**2 ) ) - np.log ( ( (h_B3+z1)**2 + (B3-(x_B3+x1))**2 ) / ( (t+h_B3+z1)**2 + (B3-(x_B3+x1))**2 ) ))

for i in range (1, int(n3/2+1)):
    x1=x1_min+(2*i-1)*h3
    V_B3+=((4*M_r)/(4*math.pi)) * ( np.log ( ( (h_B3+z1)**2 + (x_B3+x1)**2 ) / ( (t+h_B3+z1)**2 + (x_B3+x1)**2 ) ) - np.log ( ( (h_B3+z1)**2 + (B3-(x_B3+x1))**2 ) / ( (t+h_B3+z1)**2 + (B3-(x_B3+x1))**2 ) ))

x1=x1_max

V_B3+=(M_r/(4*math.pi)) * ( np.log ( ( (h_B3+z1)**2 + (x_B3+x1)**2 ) / ( (t+h_B3+z1)**2 + (x_B3+x1)**2 ) ) - np.log ( ( (h_B3+z1)**2 + (B3-(x_B3+x1))**2 ) / ( (t+h_B3+z1)**2 + (B3-(x_B3+x1))**2 ) ))

V_B3*=((h3*k3)/9)
V_B3*=(1/(l_x*l_z))*((MR*R_min*I)/(2*H_keff))

#Graph for all values of B
x_Bs = linspace(-5*B1, 5*B1, 10000)
plt.plot(x_Bs*1E5, V_B1*10E1, 'r', label=r'B=10 $\mu$m')
plt.plot(x_Bs*1E5, V_B2*10E1, 'b', label=r'B=100 $\mu$m')
plt.plot(x_Bs*1E5, V_B3*10E1, 'g', label=r'B=1 mm')
plt.xlabel(r'x ($\cdot10^{-5}$ m)', fontsize=14, loc='right')
plt.ylabel(r'$\Delta$V ($\cdot10^{-1}$ V)', fontsize=14, rotation='horizontal', loc='top')
plt.title(r'Question 3: $\Delta$V(x) for N=1', fontsize=15)
plt.legend(loc='best', shadow=False, fontsize='large')
plt.grid()
plt.show()
#Graph for B=B1
plt.plot(x_B1*1E5, V_B1*10E1, 'r')
plt.xlabel(r'x ($\cdot10^{-5}$ m)', fontsize=14, loc='right')
plt.ylabel(r'$\Delta$V ($\cdot10^{-1}$ V)', fontsize=14, rotation='horizontal', loc='top')
plt.title(r'Question 3: $\Delta$V(x) for N=1 and B=10 $\mu$m', fontsize=15)
plt.grid()
plt.show()
#Graph for B=B2
plt.plot(x_B2*1E5, V_B2*10E2, 'b')
plt.xlabel(r'x ($\cdot10^{-5}$ m)', fontsize=14, loc='right')
plt.ylabel(r'$\Delta$V ($\cdot10^{-2}$ V)', fontsize=14, rotation='horizontal', loc='top')
plt.title(r'Question 3: $\Delta$V(x) for N=1 and B=100 $\mu$m', fontsize=15)
plt.grid()
plt.show()
#Graph for B=B3
plt.plot(x_B3*1E5, V_B3*10E3, 'g')
plt.xlabel(r'x ($\cdot10^{-5}$ m)', fontsize=14, loc='right')
plt.ylabel(r'$\Delta$V ($\cdot10^{-3}$ V)', fontsize=14, rotation='horizontal', loc='top')
plt.title(r'Question 3: $\Delta$V(x) for N=1 and B=1 mm', fontsize=15)
plt.grid()
plt.show()