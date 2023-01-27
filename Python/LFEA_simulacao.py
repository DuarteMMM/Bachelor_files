import numpy as np
from numpy import *
import math
import matplotlib.pyplot as plt

#Vetor
iteradas=[]
x_0=0.3
iteradas.append(x_0)
lambda_valor=0.7
lambda_vetor=[]
periodo=4
incremento=0.001

while(True):
    for i in range(0,1000):
        x=4*lambda_valor*x_0*(1-x_0)
        #print(x)
        iteradas.append(x)
        x_0=x
    if ((round(iteradas[999-int(periodo)],3)==round(iteradas[999],3)) and (round(iteradas[999-int(periodo/2)],3)!=round(iteradas[999],3))):
        lambda_vetor.append(lambda_valor)
        
        print(round(iteradas[999-int(periodo/2)],1))
        print(round(iteradas[999-int(periodo)],1))
        print(round(iteradas[999],1))
        periodo*=2
        incremento/=10
    if periodo==512:
        break
    else:
        lambda_valor+=incremento
        iteradas=[]
        x_0=0.3

print(iteradas[999-int(periodo/2)])
print(iteradas[999-int(periodo)])
print(iteradas[999])

feigenbaum_1=(lambda_vetor[1]-lambda_vetor[0])/(lambda_vetor[2]-lambda_vetor[1])
print("Feigenbaum 1: ", feigenbaum_1)
feigenbaum_2=(lambda_vetor[2]-lambda_vetor[1])/(lambda_vetor[3]-lambda_vetor[2])
print("Feigenbaum 2: ", feigenbaum_2)
feigenbaum_3=(lambda_vetor[3]-lambda_vetor[2])/(lambda_vetor[4]-lambda_vetor[3])
print("Feigenbaum 3: ", feigenbaum_3)
feigenbaum_4=(lambda_vetor[4]-lambda_vetor[3])/(lambda_vetor[5]-lambda_vetor[4])
print("Feigenbaum 4: ", feigenbaum_4)
feigenbaum_5=(lambda_vetor[5]-lambda_vetor[4])/(lambda_vetor[6]-lambda_vetor[5])
print("Feigenbaum 5: ", feigenbaum_5)

print(lambda_vetor)
