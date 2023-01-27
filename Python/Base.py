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

print("\n\nMatemática Computacional")
while (True):
    print("\n\nA função deve ser inserida em função de t")
    print("<man> para opções ou <quit> para sair")
    val = input("Insira uma função: f(t) = ")

    # Impressão de instruções de utilização, perante o input "man"
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

    # Definição do cálculo da função
    def fu(t):
        return eval(val)

    # ---- Gráfico ----
    # Cálculo da função entre tmin e tmax
    dt = (tmax-tmin) / 1000
    t = np.arange(tmin, tmax+dt, dt)
    y = []
    for p in t:
        y.append(fu(p))
    # Plot da função
    plt.plot(t, y, 'b--')
    # Definição de legendas
    plt.xlabel('$t$')
    plt.ylabel('$f(t)$')
    plt.title("f(t) = " + val)
    # Desenho do gráfico
    plt.show()