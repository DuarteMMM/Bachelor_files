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

# Definição das constantes específicas para a quadratura de Gauss
a1 = 5/9
a2 = 8/9
a3 = 5/9

# Definição da função
def fu(t):
    return sqrt(16+exp(-t/2)*(16+t*(t-8)))/4

# Cálculo dos nodos utilizados para Gauss
def node1(i): return i + h*((1-sqrt(3/5))/2)
def node3(i): return i + h*((1+sqrt(3/5))/2)
def node2(i): return i + h/2

print("\n\nMatemática Computacional")
print("Determinar espaço percorrido por corpo em movimento com diferentes quadraturas")

# Valores específicos para estas alíneas
tmin=0
tmax=15

# Função que fornece valor do integral (TrueValue[0]) e erro associado(TrueValue[1])
TrueValue = scipy.integrate.quad(fu, 0, 15)
print ("\nValor verdadeiro do integral: %0.15f" % TrueValue[0])
print ("Erro associado: %0.15f" % TrueValue[1])

# Número de tabelas obtidas
contador = 0

while (True):

    val = input("\nInsira uma das seguintes opções:\n->'quit' se deseja sair do programa;\n-> n, número de passos inicial (inteiro superior ou igual a 1).\n\n")

    if val.isdigit() :

        # Obtenção do valor de n
        n = int(val)
        if (n < 1):
            print("Erro: O número de passos inicial deve ser um número inteiro superior ou igual a 1.\n")
            exit()

        # Obtenção do número de iteradas (linhas da tabela)
        iter = input("\nQuantas iteradas deseja realizar? ")
        if (iter.isdigit()==False or int(iter) < 1):
            print("\nErro: Deve digitar um número inteiro igual ou superior a 1.\n")
            exit()
        else:
            iter = int(iter)

        # Guardar o valor inicial de n
        n_copia = n

        # Perguntar quais as regras de quadratura a aplicar
        print("\n->Seleção de regras de quadratura")
        print("Digite 'Enter' para 'Sim', ou qualquer outro input para 'Não'.")
        val1 = input("Deseja aplicar a regra de quadratura de Gauss composta? ")
        if val1 == "":
            Gauss = 1
            b=[]
        else:
            Gauss = 0
        val2 = input("Deseja aplicar a regra dos trapézios composta? ")
        if val2 == "":
            Trapezios = 1
            c=[]
        else:
            Trapezios = 0
        val3 = input("Deseja aplicar a regra de Simpson composta? ")
        if val3 == "":
            Simpson = 1
            d=[]
        else:
            Simpson = 0
        val4 = input("Deseja aplicar a regra do ponto médio composta? ")
        if val4 == "":
            Retangulos = 1
            e=[]
        else:
            Retangulos = 0

        a=[]

        # Cálculo das várias iteradas
        for cont in range(0, iter):

            # Adicionar valor de n ao vetor a
            a.append(n)

            # Definição do step size (h)
            h = (tmax-tmin)/n

            #Gauss
            if Gauss==1:
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

            #Trapézios
            if Trapezios==1:
                sum1 = 0
                i = 0
                while i<n:
                    sum1 += fu(tmin+i*h) + fu(tmin+(i+1)*h)
                    i += 1
                sum1 *= (h/2)
                c.append(sum1)

            #Simpson
            if Simpson==1:
                sum1 = 0
                sum1 += fu(tmin) + fu(tmax)
                i = 1
                sum2 = 0
                while i<=n/2:
                    sum2 += fu(tmin + (2*i-1)*h)
                    i += 1
                sum2 *= 4
                i = 1
                sum3 = 0
                while i<=n/2-1:
                    sum3 += fu(tmin + 2*i*h)
                    i += 1
                sum3 *= 2
                sum1 += sum2 + sum3
                sum1 *= (h/3)
                d.append(sum1)

            #Ponto médio/retângulos
            if Retangulos==1:
                sum1 = 0
                i = 0
                while i<n:
                    sum1 += fu(tmin + h/2 + i*h)
                    i += 1
                sum1 *= h
                e.append(sum1)

            # Alterar o valor de n
            n *= 2

        # Tabela
        if contador==0:
            ficheiro=open(r"ProjetoMC_Grupo2_Exercicio2c.txt", "w")

        if Gauss==1:
            # Criar vetores com as linhas da tabela
            Gauss_col3=[]
            Gauss_col4=[]

            # Calcular elementos da terceira e quarta colunas
            if iter>1:
                col3 = abs(b[1] - b[0])
                Gauss_col3.append(col3)
                Gauss_col4.append(-1)
            if iter>2:
                for cont in range (1, iter-1):
                    col3 = abs(b[cont+1] - b[cont])
                    col4 = col3 / (abs(b[cont] - b[cont-1]))
                    Gauss_col3.append(col3)
                    Gauss_col4.append(col4)

            Gauss_col3.append(-1)
            Gauss_col4.append(-1)

            # Print da tabela
            ficheiro.write ("\nEis a tabela final para a quadratura de Gauss composta, número de passos inicial n=%d e %d iterações:\n" % (n_copia, iter))
            ficheiro.write ("{} {} {} {} {} {} {} {}".format (4*' ', "n", 11*' ', "Q_n", 14*' ', "|Q_2n - Q_n|", 4*' ', "|(Q_2n - Q_n)/(Q_n-Q_n/2)|"))
            for cont in range(iter):
                ficheiro.write ('\n')
                ficheiro.write ("{} {}".format("%7.0f" % a[cont], '   '))
                ficheiro.write ("{} {}".format("%.15f" % b[cont], '   '))
                if Gauss_col3[cont]==-1:
                    ficheiro.write ("{} {} {} {}".format(9*' ', '-', 9*' ', '    '))
                else:
                    ficheiro.write ("{} {}".format("%.15e" % Gauss_col3[cont], '    '))
                if Gauss_col4[cont]==-1:
                    ficheiro.write ("{} {} {}".format(9*' ', '-', '    '))
                else:
                    ficheiro.write ("{} {}".format("%.15e" % Gauss_col4[cont], '   '))
            ficheiro.write ('\n')
            contador+=1

        if Trapezios==1:
            # Criar vetor com as linhas da tabela
            Trap_col3=[]
            Trap_col4=[]

            # Calcular elementos das terceira e quarta colunas
            if iter>1:
                col3 = abs(c[1] - c[0])
                Trap_col3.append(col3)
                Trap_col4.append(-1)
            if iter>2:
                for cont in range (1, iter-1):
                    col3 = abs(c[cont+1] - c[cont])
                    col4 = col3 / (abs(c[cont] - c[cont-1]))
                    Trap_col3.append(col3)
                    Trap_col4.append(col4)

            Trap_col3.append(-1)
            Trap_col4.append(-1)

            # Print da tabela
            ficheiro.write ("\nEis a tabela final para a regra dos trapézios composta, número de passos inicial n=%d e %d iterações:\n" % (n_copia, iter))
            ficheiro.write ("{} {} {} {} {} {} {} {}".format (4*' ', "n", 11*' ', "Q_n", 14*' ', "|Q_2n - Q_n|", 4*' ', "|(Q_2n - Q_n)/(Q_n-Q_n/2)|"))
            for cont in range(iter):
                ficheiro.write ('\n')
                ficheiro.write ("{} {}".format("%7.0f" % a[cont], '   '))
                ficheiro.write ("{} {}".format("%.15f" % c[cont], '   '))
                if Trap_col3[cont]==-1:
                    ficheiro.write ("{} {} {} {}".format(9*' ', '-', 9*' ', '    '))
                else:
                    ficheiro.write ("{} {}".format("%.15e" % Trap_col3[cont], '    '))
                if Trap_col4[cont]==-1:
                    ficheiro.write ("{} {} {}".format(9*' ', '-', '    '))
                else:
                    ficheiro.write ("{} {}".format("%.15e" % Trap_col4[cont], '   ')) 
            ficheiro.write ('\n')
            contador+=1

        if Simpson==1:
            # Criar vetor com as linhas da tabela
            Simp_col3=[]
            Simp_col4=[]

            # Calcular elementos das terceira e quarta colunas
            if iter>1:
                col3 = abs(d[1] - d[0])
                Simp_col3.append(col3)
                Simp_col4.append(-1)
            if iter>2:
                for cont in range (1, iter-1):
                    col3 = abs(d[cont+1] - d[cont])
                    col4 = col3 / (abs(d[cont] - d[cont-1]))
                    Simp_col3.append(col3)
                    Simp_col4.append(col4)

            Simp_col3.append(-1)
            Simp_col4.append(-1)

            # Print da tabela
            ficheiro.write ("\nEis a tabela final para a regra de Simpson composta, número de passos inicial n=%d e %d iterações:\n" % (n_copia, iter))
            ficheiro.write ("{} {} {} {} {} {} {} {}".format (4*' ', "n", 11*' ', "Q_n", 14*' ', "|Q_2n - Q_n|", 4*' ', "|(Q_2n - Q_n)/(Q_n-Q_n/2)|"))
            for cont in range(iter):
                ficheiro.write ('\n')
                ficheiro.write ("{} {}".format("%7.0f" % a[cont], '   '))
                ficheiro.write ("{} {}".format("%.15f" % d[cont], '   '))
                if Simp_col3[cont]==-1:
                    ficheiro.write ("{} {} {} {}".format(9*' ', '-', 9*' ', '    '))
                else:
                    ficheiro.write ("{} {}".format("%.15e" % Simp_col3[cont], '    '))
                if Simp_col4[cont]==-1:
                    ficheiro.write ("{} {} {}".format(9*' ', '-', '    '))
                else:
                    ficheiro.write ("{} {}".format("%.15e" % Simp_col4[cont], '   '))
            ficheiro.write ('\n')
            contador+=1

        if Retangulos==1:
            # Criar vetor com as linhas da tabela
            Ret_col3=[]
            Ret_col4=[]

            # Calcular elementos das terceira e quarta colunas
            if iter>1:
                col3 = abs(e[1] - e[0])
                Ret_col3.append(col3)
                Ret_col4.append(-1)
            if iter>2:
                for cont in range (1, iter-1):
                    col3 = abs(e[cont+1] - e[cont])
                    col4 = col3 / (abs(e[cont] - e[cont-1]))
                    Ret_col3.append(col3)
                    Ret_col4.append(col4)

            Ret_col3.append(-1)
            Ret_col4.append(-1)

            # Print da tabela
            ficheiro.write ("\nEis a tabela final para a regra dos retângulos, número de passos inicial n=%d e %d iterações:\n" % (n_copia, iter))
            ficheiro.write ("{} {} {} {} {} {} {} {}".format (4*' ', "n", 11*' ', "Q_n", 14*' ', "|Q_2n - Q_n|", 4*' ', "|(Q_2n - Q_n)/(Q_n-Q_n/2)|"))

            for cont in range(iter):
                ficheiro.write ('\n')
                ficheiro.write ("{} {}".format("%7.0f" % a[cont], '   '))
                ficheiro.write ("{} {}".format("%.15f" % e[cont], '   '))
                if Ret_col3[cont]==-1:
                    ficheiro.write ("{} {} {} {}".format(9*' ', '-', 9*' ', '    '))
                else:
                    ficheiro.write ("{} {}".format("%.15e" % Ret_col3[cont], '    '))
                if Ret_col4[cont]==-1:
                    ficheiro.write ("{} {} {}".format(9*' ', '-', '    '))
                else:
                    ficheiro.write ("{} {}".format("%.15e" % Ret_col4[cont], '   '))
            ficheiro.write ('\n')
            contador+=1

        # Gráficos
        grafico = input("\nDigite:\n->'i' se desejar obter gráficos das sucessivas iteradas;\n->'e' se desejar obter gráficos dos módulos dos respetivos erros;\n-> algo sem 'i' nem 'e', se não desejar obter qualquer gráfico.\n\n")

        if 'i' in grafico:
            plt.figure(0)
            # Gráfico(s) das sucessivas iteradas
            # Plot da linha horizontal com o valor verdadeiro
            vec1 = [n_copia-5, n_copia*pow(2,iter-1)+5]
            vec2 = [TrueValue[0], TrueValue[0]]
            axes = plt.gca()
            axes.set_xlim([n_copia-5, n_copia*pow(2,iter-1)+5])
            plt.xticks(a)
            plt.plot(vec1, vec2, color='black', linestyle='solid', linewidth=0.5, label="Valor verdadeiro")

            # Plot dos pontos das diferentes quadraturas
            if Gauss==1:
                plt.plot(a, b, color='lightskyblue', linestyle='dashed', marker='o', linewidth=1, label='Gauss')
            if Trapezios==1:
                plt.plot(a, c, color='darkorange', linestyle='dashed', marker='v', linewidth=1, label='Trapézios')
            if Simpson==1:
                plt.plot(a, d, color='indigo', linestyle='dashed', marker='s', linewidth=1, label='Simpson')
            if Retangulos==1:
                plt.plot(a, e, color='maroon', linestyle='dashed', marker='*', linewidth=1, label='Retângulos')
                
            plt.xlabel("n", fontsize=15)
            plt.ylabel("$Q_{n}(f)$", fontsize=15)
            plt.title("Convergência para diferentes regras de quadratura compostas", fontsize=15)
            plt.legend(loc='best', shadow=False, fontsize='large')
            if 'e' not in grafico:
                plt.show()

        if 'e' in grafico:
            plt.figure(1)
            # Gráfico dos módulos dos erros das sucessivas iteradas
            # Plot da linha horizontal com o valor verdadeiro
            vec1=[n_copia-5, n_copia*pow(2,iter-1)+5]
            vec2=[0, 0]
            axes = plt.gca()
            axes.set_xlim([n_copia-5, n_copia*pow(2,iter-1)+5])
            plt.xticks(a)
            plt.plot(vec1, vec2, color='black', linestyle='solid', linewidth=0.5, label="Valor verdadeiro")

            # Plot dos pontos das diferentes quadraturas
            if Gauss==1:
                b_copia = []
                for j in b:
                    b_copia.append(abs(TrueValue[0]-j))
                plt.plot(a, b_copia, color='lightskyblue', linestyle='dashed', marker='o', linewidth=1, label='Gauss')
            if Trapezios==1:
                c_copia=[]
                for j in c:
                    c_copia.append(abs(TrueValue[0]-j))
                plt.plot(a, c_copia, color='darkorange', linestyle='dashed', marker='v', linewidth=1, label='Trapézios')
            if Simpson==1:
                d_copia=[]
                for j in d:
                    d_copia.append(abs(TrueValue[0]-j))
                plt.plot(a, d_copia, color='indigo', linestyle='dashed', marker='s', linewidth=1, label='Simpson')
            if Retangulos==1:
                e_copia=[]
                for j in e:
                    e_copia.append(abs(TrueValue[0]-j))
                plt.plot(a, e_copia, color='maroon', linestyle='dashed', marker='*', linewidth=1, label='Retângulos')
                
            plt.xlabel("n", fontsize=15)
            plt.ylabel("$|L(15)-Q_{n}(f)|$", fontsize=15)
            plt.title("Erros associados às diferentes fórmulas de quadratura compostas", fontsize=15)
            plt.legend(loc='best', shadow=False, fontsize='large')
            plt.show()

        print ("\n-=-=-=-=-")

    elif val=='quit':
        break

    else:
        print("\nDigitou algo inválido.")

if contador>0:
    # Fechar o ficheiro
    ficheiro.close()

    if contador==1:
        print ("\nA tabela foi escrita no ficheiro 'ProjetoMC_Grupo2_Exercicio2c.txt'.")
    if contador>1:
        print ("\nAs tabelas foram escritas no ficheiro 'ProjetoMC_Grupo2_Exercicio2c.txt'.")

print('\n')