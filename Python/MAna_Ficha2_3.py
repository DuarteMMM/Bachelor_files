from matplotlib import pyplot as plt
from scipy.integrate import odeint
import numpy as np

c=1
r=10
def f(u,x):
    return (u[1],6*c*u[0]-4.5*u[0]*u[0]+r)
y0=[0,0]
xs=np.linspace(1,10,200)
us=odeint(f,y0,xs)
ys=us[:,0]
#plt.plot(us,'-')
plt.plot(ys,'g-')
plt.xlabel('t')
plt.ylabel(r'$ \eta$')
plt.title('Ondas periódicas (c=1, r=10)')
plt.show()