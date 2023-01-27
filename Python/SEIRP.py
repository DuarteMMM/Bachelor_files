# Importação das bibliotecas necessárias
# https://numpy.org/doc/stable/reference/routines.math.html
import numpy as np
import matplotlib.pyplot as plt

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

# Definição do método de Runge Kutta
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

while (True):
    print("\n\n(enter para parâmetro default, <quit> para sair)")

    # Definção dos valores default para os parâmetros
    b = 2.30137e-5
    mu = 3.38238e-5
    muP = 0.1724
    alpha1 = 0.1
    alpha2 = 0.1
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

    # Leitura dos parâmetros
    print("---- Parâmetros ----")
    b = read(b, "Taxa de natalidade: ")
    mu = read(mu, "Taxa de mortalidade: ")
    muP = read(muP, "Taxa de mortalidade natural de patógenos no meio ambiente: ")
    alpha1 = read(alpha1, "Proporção de interação com um ambiente infeccioso: ")
    alpha2 = read(alpha2, "Proporção de interação com um indivíduo infeccioso: ")
    beta1 = read(beta1, "Taxa de transmissão de S para E devido ao contacto com P: ")
    beta2 = read(beta2, "Taxa de transmissão de S para E devido ao contacto com IA e/ou IS: ")
    delta = read(delta, "Proporção de indivíduos infecciosos sintomáticos: ")
    psi = read(psi, "Taxa de progressão de E para S devido a sistema imunológico robusto: ")
    omega = read(omega, "Taxa de progressão de E para IA ou IS: ")
    sigma = read(sigma, "Taxa de mortalidade devido à COVID-19: ")
    gammaS = read(gammaS, "Taxa de recuperação da população humana sintomática: ")
    gammaA = read(gammaA, "Taxa de recuperação da população humana assintomática: ")
    etaS = read(etaS, "Taxa de disseminação do vírus para o ambiente por indivíduos infecciosos sintomáticos: ")
    etaA = read(etaA, "Taxa de disseminação do vírus para o ambiente por indivíduos infecciosos assintomáticos: ")
    # Leitura do estado inicial
    print("\n---- Estado inicial da epidemia ----")
    S0 = read(S0, "Grupo suscetível(0): ")
    E0 = read(E0, "Grupo exposto(0): ")
    IA0 = read(IA0, "Infecciosos assintomáticos(0): ")
    IS0 = read(IS0, "Infecciosos sintomáticos(0): ")
    R0 = read(R0, "Recuperados(0): ")
    P0 = read(P0, "Patógenos(0): ")
    # Leitura do número de dias a avaliar
    days = read(days, "\nNúmero de dias da simulação: ")

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

    # Gráfico
    plt.plot(t, Svals, color='lightskyblue', linestyle='dashed', linewidth=1, label='Grupo suscetível')
    plt.plot(t, Evals, color='darkorange', linestyle='dashed', linewidth=1, label='Grupo exposto')
    plt.plot(t, IAvals, color='indigo', linestyle='dashed', linewidth=1, label='Infetados assintomáticos')
    plt.plot(t, ISvals, color='maroon', linestyle='dashed', linewidth=1, label='Infetados sintomáticos')
    plt.plot(t, Rvals, color='forestgreen', linestyle='dashed', linewidth=1, label='Recuperados')
    plt.plot(t, Pvals, color='orchid', linestyle='dashed', linewidth=1, label='Patógenos')
    plt.xlabel("Dias")
    plt.title("Evolução da epidemia")
    plt.legend(loc='best', shadow=False, fontsize='small')
    plt.show()
    val = input("\nSair? (<quit> para terminar, enter para proceder) ")
    if (val == "quit"):
        break
    elif (val == ''):
        continue
    else:
        print("Erro")
        break