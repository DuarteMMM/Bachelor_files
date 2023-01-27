# Importação das bibliotecas necessárias
# https://numpy.org/doc/stable/reference/routines.math.html
import numpy as np
import scipy.integrate
import matplotlib.pyplot as plt

# Definição das funções necessárias
def exp(x):
    return np.exp(x)
def sqrt(x):
    return np.sqrt(x)
def power(x, y):
    return np.power(x, y)

# Definição das constantes específicas do exercício
a1 = 5/9
a2 = 8/9
a3 = 5/9

# Definição da função
def fu(t):
    return sqrt(1+exp(-t/2)*(1-t/4)*(1-t/4))

# Cálculo do nodo utilizado
def node1(i): return i + h*((1-sqrt(3/5))/2)
def node3(i): return i + h*((1+sqrt(3/5))/2)
def node2(i): return i + h/2

print("\n\nMatemática Computacional")
print("Determinar espaço percorrido por corpo em movimento com quadratura de Gauss composta")

# Valores específicos para estas alíneas
tmin=0
tmax=15

# Função que fornece valor do integral (i[0]) e erro associado(i[1])
i = scipy.integrate.quad(fu, 0, 15)
print ("\nValor verdadeiro do integral: %0.15f" % i[0])
print ("Erro associado: %0.15f" % i[1])

# Número de ciclos
contador = 0

while (True):

    val = input("\nInsira uma das seguintes opções:\n->'quit' se deseja sair do programa;\n-> n, número de passos inicial (inteiro superior ou igual a 1).\n\n")

    if val.isdigit() :

        # Obtenção do valor de n
        n = int(val)
        if (n < 1):
            print("Erro: O número de passos inicial deve ser um número inteiro superior ou igual a 1\n")
            exit()

        # Obtenção do número de iteradas (linhas da tabela)
        iter = input("\nQuantas linhas da tabela deseja ter? ")
        if (iter.isdigit()==False or int(iter) < 1):
            print("\nErro: Deve digitar um número inteiro igual ou superior a 1.\n")
            exit()
        else:
            iter = int(iter)

        # Guardar o valor inicial de n
        n_copia = n

        # Vetores para valores n e Q, respetivamente
        a=[] 
        b=[]

        # Cálculo das várias iteradas
        for cont in range(0, iter):

            # Adicionar valor de n ao vetor a
            a.append(n)

            # Definição do step size (h)
            h = (tmax-tmin)/n

            i = tmin
            sum1 = 0
            sum2 = 0
            sum3 = 0
            while (i < tmax):
                sum1 += fu(node1(i))
                sum2 += fu(node2(i))
                sum3 += fu(node3(i))
                i += h

            Q = h/2 * (a1 * sum1 + a2 * sum2 + a3 * sum3)

            # Guardar o valor da quadratura no vetor respetivo
            b.append(Q)

            # Alterar o valor de n
            n *= 2
        
        # Vetores com a terceira e quarta colunas da tabela, respetivamente
        c=[]
        d=[]

        # Primeira linha
        if iter>1:
            col3 = abs(b[1] - b[0])
            c.append(col3)
            d.append(-1)

        # Linhas intermédias
        if iter>2:
            for cont in range (1, iter-1):
                col3 = abs(b[cont+1] - b[cont])
                col4 = col3 / (abs(b[cont] - b[cont-1]))
                c.append(col3)
                d.append(col4)

        # Última linha
        c.append(-1)
        d.append(-1)

        # Escrita da tabela num ficheiro
        if contador==0:
            ficheiro=open(r"ProjetoMC_Grupo2_Exercicio2b.txt", "w")
        ficheiro.write ("Eis a tabela final para número de passos inicial n=%d e %d iteradas:\n" % (n_copia, iter))
        ficheiro.write ("{} {} {} {} {} {} {}".format(" n",11*' ', "Q_n", 14*' ', "|Q_2n - Q_n|", 4*' ', "|(Q_2n - Q_n)/(Q_n-Q_n/2)|"))

        for cont in range(iter):
            ficheiro.write ('\n')
            ficheiro.write ("{} {}".format("%3.0f" % a[cont], '   '))
            ficheiro.write ("{} {}".format("%.15f" % b[cont], '   '))
            if c[cont]==-1:
                ficheiro.write ("{} {} {} {}".format(9*' ', '-', 9*' ', '    '))
            else:
                ficheiro.write ("{} {}".format("%.15e" % c[cont], '    '))
            if d[cont]==-1:
                ficheiro.write ("{} {} {}".format(9*' ', '-', '    '))
            else:
                ficheiro.write ("{} {}".format("%.15e" % d[cont], '   '))

        ficheiro.write ("\n\n")

        # Gráfico da função integranda
        # Cálculo da função entre tmin e tmax
        dt = (tmax-tmin) / 1000
        t = np.arange(tmin, tmax+dt, dt)
        # Cálculo da função
        y = []
        for p in t:
            y.append(fu(p))
        # Plot da função
        plt.plot(t, y, linestyle='solid')
        # Definição de legendas
        plt.xlabel('t', fontsize=15)
        axes = plt.gca()
        axes.set_xlim([0, 15])
        plt.ylabel('f(t)', fontsize=15)
        plt.title("Função integranda " r'f(t) = $\sqrt{1+e^{-\frac{t}{2}}{\left(1-\frac{t}{4}\right)}^2}$', fontsize=15)
        # Desenho do gráfico
        plt.show()

        # Contabilizar novo ciclo de cálculo realizado
        contador+=1

        print ("\n-=-=-=-=-")

    elif val=='quit':
        break

    else:
        print("\nDigitou algo inválido.")

if contador>0:
    # Fechar o ficheiro
    ficheiro.close()

    if contador==1:
        print ("\nA tabela foi escrita no ficheiro 'ProjetoMC_Grupo2_Exercicio2b.txt'.")
    if contador>1:
        print ("\nAs tabelas foram escritas no ficheiro 'ProjetoMC_Grupo2_Exercicio2b.txt'.")

print('\n')