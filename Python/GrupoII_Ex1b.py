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

# Definição das constantes específicas do exercício
a1 = 5/9
a2 = 8/9
a3 = 5/9

print("\n\nMatemática Computacional\n")
print("Quadratura de Gauss Composta para Aproximação de Integrais\n\n")
print("Insira 'man' (em vez de uma função) para ver o manual de funções e constantes suportadas ou 'quit' para terminar o programa.\n")

val = input("Insira uma função (de uma variável t): f(t) = ")

func = ["sin", "cos", "tan"]
func2 = ["exp", "log", "log10", "sqrt", "cbrt", "fabs", "power(base, exponent)"]
consts = ["pi", "e "]

while (val != "quit"):
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
    else:
        # Input do intervalo
        tmin = float(eval(input("Insira o mínimo do intervalo de cálculo do integral: ")))
        tmax = float(eval(input("Insira o máximo do intervalo de cálculo do integral: ")))

        # Teste
        if (tmin > tmax):
            print("Erro")
            exit()

        # Input do número de passos
        n = int(input("Insira o número de passos a considerar na aproximação do integral: "))
        if (n < 1):
            print("Erro")
            exit()

        # Definição do step size (h)
        h = (tmax-tmin)/n

        # Definição do cálculo da função
        def fu(t):
            return eval(val)

        # Cálculo do nodo utilizado
        def node1(i): return i + h*((1-sqrt(3/5))/2)
        def node3(i): return i + h*((1+sqrt(3/5))/2)
        def node2(i): return i + h/2

        i = tmin
        sum1 = 0
        sum2 = 0
        sum3 = 0

        # Vetores a utilizar caso se queira mostrar as iterações no gráfico
        #y1 = []
        #y2 = []
        #y3 = []
        #x1 = []
        #x2 = []
        #x3 = []
        #x4 = []
        #y4 = []

        while (i < tmax):
            sum1 += fu(node1(i))
            sum2 += fu(node2(i))
            sum3 += fu(node3(i))
            #y1.append(fu(node1(i)))
            #y2.append(fu(node2(i)))
            #y3.append(fu(node3(i)))
            #y4.append(fu(i))
            #x1.append(i + h*((1-sqrt(3/5))/2))
            #x2.append(i + h/2)
            #x3.append(i + h*((1+sqrt(3/5))/2))
            #x4.append(i)
            i += h

        Q = h/2 * (a1 * sum1 + a2 * sum2 + a3 * sum3)

        print("Q(f) = ", Q)

        # ---- Gráfico ----
        # Cálculo da função entre tmin e tmax
        dt = (tmax-tmin) / 1000
        t = np.arange(tmin, tmax+dt, dt)
        # Cálculo da função
        y = []
        for p in t:
            y.append(fu(p))
        # Plot da função
        plt.plot(t, y, 'r--')
        #plt.plot(x1, y1, 'yo')
        #plt.plot(x2, y2, 'go')
        #plt.plot(x3, y3, 'bo')
        #plt.plot(x4, y4, 'ko')
        # Definição de legendas
        plt.xlabel('$t$')
        plt.ylabel('$f(t)$')
        plt.title("$f(t) = $" + val)
        # Desenho do gráfico
        plt.show()

    print("\n\nInsira 'man' (em vez de uma função) para ver o manual de funções e constantes suportadas ou 'quit' para terminar o programa.\n")
    val = input("Insira uma função (de uma variável t): f(t) = ")