# Importação das bibliotecas necessárias
# https://numpy.org/doc/stable/reference/routines.math.html
import numpy as np
import matplotlib.pyplot as plt

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

# Funções disponíveis
func = ["sin", "cos", "tan"]
func2 = ["exp", "log", "log10", "sqrt", "cbrt", "fabs", "power"]
consts = ["pi", "e "]

# Definição do método de Runge-Kutta
def RK(h, f, t0, y0):
    k1 = f(t0, y0)
    k2 = f(t0+h/3, y0+h/3*k1)
    k3 = f(t0+2*h/3, y0+2*h/3*k2)
    return y0 + h/4*(k1+3*k3)

print("\n\nMatemática Computacional")
print("Método Runge-Kutta")
while (True):
    print("\n\nA função deve ser inserida em função de t e de y")
    print("<man> para opções ou <quit> para sair")
    val = input("Insira uma função: f(t, y) = ")

    # Impressão de instruções de utilização, pertante o input "man"
    if (val == "man"):
        print("\nLista de funções suportadas:\n")
        for x in func:
            print(x)
        for x in func:
            print("arc" + x)
        for x in func:
            print(x + "h")
        for x in func:
            print("arc" + x + "h")
        for x in func2:
            print(x)
        print("\nLista de constantes suportadas:\n")
        for x in consts:
            print(x)
        continue
    elif (val == "quit"):
        break

    # Input do intervalo
    tmin = float(eval(input("Insira o t mínimo: ")))
    tmax = float(eval(input("Insira o t máximo: ")))
    # Teste
    if (tmin > tmax):
        print("Erro")
        exit()

    # Input do valor da função em tmin
    y0 = float(eval(input("Insira o valor inicial da função: ")))

    # Input do valor de n desejado
    n = float(eval(input("Insira o n pretendido: ")))
    # Cálculo de h
    h0 = (tmax-tmin) / n
    
    # Definição do cálculo da função
    def fu(t, y):
        return eval(val)

    # ---- Gráfico ----
    # Cálculo da função entre tmin e tmax
    t = np.arange(tmin, tmax+h0, h0)
    y = []
    y.append(y0)
    print("\n---- Aproximações (t, y) ----\n")
    print("%10.6g, %10.6g" % (tmin, y0))
    it = 1
    while (it < len(t)):
        yt = RK(h0, fu, t[it-1], y[it-1])
        print("%10.6g, %10.6g" % (t[it], yt))
        y.append(yt)
        it += 1
    # Plot da função
    plt.plot(t, y, color='darkorange', linestyle='dashed', linewidth=1, label='Spline linear')
    plt.plot(t, y, linewidth=0, marker='o', markeredgecolor='lightskyblue', markerfacecolor='lightskyblue', markersize=2, label='Pontos de cálculo')
    # Definição de legendas
    plt.xlabel('$t$')
    plt.ylabel('$y$')
    plt.title("f(t, y) = " + val)
    plt.legend(loc='best', shadow=False, fontsize='small')
    # Desenho do gráfico
    plt.show()