# Importação das bibliotecas necessárias
# https://numpy.org/doc/stable/reference/routines.math.html
import numpy as np
import matplotlib.pyplot as plt

# Estilo de linha
dashdotdotted = (0, (3, 5, 1, 5, 1, 5))

print("\n\nMatemática Computacional")
print("Simulação COVID-19")

# Definição do sistema de equações diferenciais
def Sder(S, E, IA, IS, P):
    return b - (beta1*S*P)/(1+alpha1*P) - (beta2*S*(IA+IS))/(1+alpha2*(IA+IS)) + psi*E - mu*S
def Eder(S, E, IA, IS, P):
    return (beta1*S*P)/(1+alpha1*P) + (beta2*S*(IA+IS))/(1+alpha2*(IA+IS)) - (psi + mu + omega)*E
def IAder(E, IA):
    return (1-delta)*omega*E - (mu+sigma + gammaA)*IA
def ISder(E, IS):
    return delta*omega*E - (mu+sigma + gammaS)*IS
def Rder(IA, IS, R):
    return gammaA*IA + gammaS*IS - mu*R
def Pder(IA, IS, P):
    return etaA*IA + etaS*IS - muP*P
def f(S, E, IA, IS, R, P):
    return [Sder(S, E, IA, IS, P), Eder(S, E, IA, IS, P), IAder(E, IA), ISder(E, IS), Rder(IA, IS, R), Pder(IA, IS, P)]

# Definição do método de Runge-Kutta
def RK(h, S_0, E_0, IA_0, IS_0, R_0, P_0):
    k1 = f(S_0, E_0, IA_0, IS_0, R_0, P_0)
    k2 = f(S_0+h/3*k1[0], E_0+h/3*k1[1], IA_0+h/3*k1[2], IS_0+h/3*k1[3], R_0+h/3*k1[4], P_0+h/3*k1[5])
    k3 = f(S_0+2*h/3*k2[0], E_0+2*h/3*k2[1], IA_0+2*h/3*k2[2], IS_0+2*h/3*k2[3], R_0+2*h/3*k2[4], P_0+2*h/3*k2[5])
    return [S_0+h/4*(k1[0]+3*k3[0]), E_0+h/4*(k1[1]+3*k3[1]), IA_0+h/4*(k1[2]+3*k3[2]), IS_0+h/4*(k1[3]+3*k3[3]), R_0+h/4*(k1[4]+3*k3[4]), P_0+h/4*(k1[5]+3*k3[5])]

# Função auxiliar de leitura
def read(var, string):
    inp = input(string)
    if (inp == "quit"):
        exit()
    elif (inp != ''):
        return float(eval(inp))
    else:
        print(var)
        return var

# Definção dos valores default para os parâmetros
b = 2.30137e-5
mu = 3.38238e-5
muP = 0.1724
beta1 = 0.00414
beta2 = 0.0115
delta = 0.7
psi = 0.0051
omega = 0.09
sigma = 0.005
gammaS = 0.05
gammaA = 0.0714
etaS = 0.1
etaA = 0.05
S0 = 50000
E0 = 500
IA0 = 30
IS0 = 20
R0 = 0
P0 = 500
days = 90

# Definição dos pares alpha1 e alpha2 (e outros atributos)
par = [[0.1, 0.1, 0, 'solid'], [0.05, 0.1, 1, 'dotted'], [0.1, 0.05, 2, 'dashed'], [0.05, 0.05, 3, dashdotdotted]]

# Definição dos arrays onde serão armazenados os dados
dataS = []
dataE = []
dataIA = []
dataIS = []
dataR = []
dataP = []

for p in par:
    # Definição dos parâmetros
    alpha1 = p[0]
    alpha2 = p[1]

    # Definição dos arrays onde serão armazenados os valores
    t = np.arange(0, days+1, 1)
    Svals = []
    Evals = []
    IAvals = []
    ISvals = []
    Rvals = []
    Pvals = []

    # Armazenamento dos valores iniciais
    Svals.append(S0)
    Evals.append(E0)
    IAvals.append(IA0)
    ISvals.append(IS0)
    Rvals.append(R0)
    Pvals.append(P0)

    # Cálculo dos valores seguintes
    i = 1
    while (i <= days):
        vals = RK(1, Svals[i-1], Evals[i-1], IAvals[i-1], ISvals[i-1], Rvals[i-1], Pvals[i-1])
        Svals.append(vals[0])
        Evals.append(vals[1])
        IAvals.append(vals[2])
        ISvals.append(vals[3])
        Rvals.append(vals[4])
        Pvals.append(vals[5])
        i += 1

    # Armazenamento dos dados
    dataS.append(Svals)
    dataE.append(Evals)
    dataIA.append(IAvals)
    dataIS.append(ISvals)
    dataR.append(Rvals)
    dataP.append(Pvals)

print("\n---- Combinações consideradas ----")
for p in par:
    leg = '$\\alpha _1 = $' + str(p[0]) + "$, \\alpha_2 = $" + str(p[1])
    print("alpha_1 = %f, alpha_2 = %f" % (p[0], p[1]))
    plt.figure(0)
    plt.plot(t, dataS[p[2]], color='lightskyblue', linestyle=p[3], linewidth=1, label=leg)
    plt.title('Grupo suscetível')
    plt.figure(1)
    plt.plot(t, dataE[p[2]], color='darkorange', linestyle=p[3], linewidth=1, label=leg)
    plt.title('Grupo exposto')
    plt.figure(2)
    plt.plot(t, dataIA[p[2]], color='indigo', linestyle=p[3], linewidth=1, label=leg)
    plt.title('Infetados assintomáticos')
    plt.figure(3)
    plt.plot(t, dataIS[p[2]], color='maroon', linestyle=p[3], linewidth=1, label=leg)
    plt.title('Infetados sintomáticos')
    plt.figure(4)
    plt.plot(t, dataR[p[2]], color='forestgreen', linestyle=p[3], linewidth=1, label=leg)
    plt.title('Recuperados')
    plt.figure(5)
    plt.plot(t, dataP[p[2]], color='orchid', linestyle=p[3], linewidth=1, label=leg)
    plt.title('Patógenos')
it = 0
while (it < 6):
    plt.figure(it)
    plt.xlabel("Dias")
    plt.legend(loc='best', shadow=False, fontsize='small')
    it += 1
plt.show()