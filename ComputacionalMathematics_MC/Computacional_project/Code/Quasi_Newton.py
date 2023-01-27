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

print("\n\nMatemática Computacional\n\n")
print("Método Quasi-Newton")

print("A função deve ser inserida em função de t")
print("<man> para opções")
val = input("Insira uma função: f(t) = ")

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
    exit()

# Teste
# Neste caso a função não pode ser constante (a expressão tem que depender de t)
if ("t" not in val):
    print("Erro, função inválida")
    exit()

# Input do delta
delta = float(eval(input("Insira o delta: ")))
if delta <= 0:
    print("Erro, delta inválido")
    exit()

# Input do x0
x0 = float(eval(input("Insira a aproximação inicial x0: ")))

# Input do número máximo de iterações (mínimo de 1)
nmax = int(eval(input("Insira o número máximo de iterações a realizar: ")))
if nmax <= 1:
    print("Erro, número máximo de iterações inválido")
    exit()

# Input da tolerância
E = float(eval(input("Insira a tolerância de erro: ")))
if E <= 0:
    print("Erro, tolerância de erro inválida")
    exit()

# Definição do cálculo da função
def fu(t):
    return eval(val)

# Definição do cálculo do método de quasi-Newton
def calc(x):
    return x - delta / (fu(x+delta)-fu(x)) * fu(x)

# Definição do cálculo do majorante do erro, com um algarismo e arredondado para cima
# (Presume que x é positivo)
def err(x):
    num = float("{:e}".format(x).split('e')[0])
    pow = float("{:e}".format(x).split('e')[1])
    num = np.ceil(num)
    if (x >= num*(10**pow)):
        num += 1
        if (num == 10):
            num = 0
            pow += 1
    return num*(10**pow)

# Inicialização do vetor para as iteradas
x = []
# Introdução da iterada 0
x.append(x0)
# Introdução da iterada 1
x.append(calc(x0))
it = 1
# Cálculo das iteradas seguintes enquanto
# - O número de iteradas é inferior ao número máximo de iteradas permitido
# - Não é encontrado um zero
# - O erro é superior à tolerância
while ((it < nmax) and (fu(x[it]) != 0) and (abs(x[it]-x[it-1]) > E)):
    x.append(calc(x[it]))
    it = it + 1

# Impressão dos erros (tomando como valor real a última iterada)
# Cálculo da função nos pontos das iteradas
y = []
i = 0
print("\n---- Cálculo das iteradas ----\n")
for n in x:
    if (i != it):
        print("%4d: %16.15e +- %.0e" % (i, n, err(abs(n-x[it]))))
    else:
        print("%4d: %16.15e (f(z) = %.0e)" % (i, n, fu(n)))
    y.append(fu(n))
    i = i + 1

# ---- Gráfico ----
# Cálculo de uma escala para o gráfico
# Cálculo da função no intervalo entre a iterada mais pequena e a iterada maior, em 1000 pontos igualmente espaçados
t = np.arange(np.amin(x), np.amax(x)+(np.amax(x) - np.amin(x))/1000, (np.amax(x) - np.amin(x))/1000)
# Formatação do texto com o número da iterada
i = 0
while (i <= it):
    plt.annotate(str(i), (x[i], y[i]))
    i += 1
# Plot da função
plt.plot(t, fu(t), color='forestgreen', linestyle='dashed', label='f(t)')
# Plot dos pontos das iteradas
plt.plot(x, y, marker='x', color='gold', label='Iteradas ($x_i$, $f(x_i)$)', linewidth=0)
# Definição de legendas
plt.xlabel('$x_i$')
plt.ylabel('$f(t)$')
plt.title("f(t) = " + val)
plt.legend(loc='best', shadow=False, fontsize='small')
# Desenho do gráfico
plt.show()