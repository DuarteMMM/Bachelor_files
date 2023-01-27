# Importação das bibliotecas necessárias
# https://numpy.org/doc/stable/reference/routines.math.html
import numpy as np
import matplotlib.pyplot as plt
import math

# Definição das funções necessárias
def sin(x):
    return np.sin(x)
def cos(x):
    return np.cos(x)
def tan(x):
    return np.tan(x)
def arcsin(x):
    return np.arcsin(x)
def arccos(x):
    return np.arccos(x)
def arctan(x):
    return np.arctan(x)
def sinh(x):
    return np.sinh(x)
def cosh(x):
    return np.cosh(x)
def tanh(x):
    return np.tanh(x)
def arcsinh(x):
    return np.arcsinh(x)
def arccosh(x):
    return np.arccosh(x)
def arctanh(x):
    return np.arctanh(x)   
def exp(x):
    return np.exp(x)
def log(x):
    return np.log(x)
def log10(x):
    return np.log10(x)
def sqrt(x):
    return np.sqrt(x)
def cbrt(x):
    return np.cbrt(x)
def fabs(x):
    return np.fabs(x)
def power(x, y):
    return np.power(x, y)

# Definição das constantes necessárias
e = np.e
pi = np.pi

# Definição das constantes específicas do exercício
a1 = 5/9
a2 = 8/9
a3 = 5/9

#print("\n\nMatemática Computacional\n")
#print("Grupo II Exercício 2.d)\n\n")

# Função do exercício 2 do grupo II
val = "sqrt(1+exp(-t/2)*pow(1-t/4,2))"

# Definição do cálculo da função
def fu(t):
    return eval(val)

# O extremo mínimo de integração é sempre 0
tmin = 0

# Array para os integrais
Q = []

# Array para os extremos máximos de integração
t = []

# Para tmax=0=tmin, o integral é 0
Q.append(0)
t.append(0)

for x in range(1,101):
    # Extremo máximo de integração para cada integral
    tmax = x*0.15
    t.append(tmax)

    # Definição do step size (h) com n=1
    n = 1
    h = tmax/n

    # Cálculo do nodo utilizado
    def node1(i): return i + h*((1-sqrt(3/5))/2)
    def node3(i): return i + h*((1+sqrt(3/5))/2)
    def node2(i): return i + h/2

    # Q1=Q_n Q2=Q_2n
    Q1 = 0
    Q2 = 1

    # Cálculo de Q_n e de Q_2n até |Q_n-Q_2n| <= 10^-6
    while (math.fabs(Q1-Q2) > 0.000001):
        i = tmin
        sum1 = 0
        sum2 = 0
        sum3 = 0
        while (i < tmax):
            sum1 += fu(node1(i))
            sum2 += fu(node2(i))
            sum3 += fu(node3(i))
            i += h

        Q1 = h/2 * (a1 * sum1 + a2 * sum2 + a3 * sum3)
        
        n *= 2
        h = tmax/n

        i = tmin
        sum1 = 0
        sum2 = 0
        sum3 = 0
        while (i < tmax):
            sum1 += fu(node1(i))
            sum2 += fu(node2(i))
            sum3 += fu(node3(i))
            i += h

        Q2 = h/2 * (a1 * sum1 + a2 * sum2 + a3 * sum3)
        
        n /= 2
        n += 1
        h = tmax/n

    Q.append(Q1)
    #print(n-1)
    #print(Q1)

# ---- Gráfico ----
# Plot dos pontos 
plt.plot(t, Q, linewidth=0, marker='o', markeredgecolor='lime',markerfacecolor='lime', markersize=1)
# Definição do título e dos eixos
plt.xlabel('Extremo máximo de integração - \u03C4')
plt.ylabel('L(\u03C4)')
plt.title(r'$f(t) = \sqrt{1+e^{-\frac{t}{2}}{\left(1-\frac{t}{4}\right)}^2}$')
# Desenho do gráfico
plt.show()