/******************************************************
 *                Física Computacional                *
 *                    Exercício 11                    *
 *                                                    *
 *             Duarte Marques - ist196523             *
 *            Martim Ferreira - ist196554             *
 *****************************************************/

int main () {
  double sum = 0;
  
  for (double x=0; x!=5.5; x += 0.1) {
    sum += x;
  }
}

/* Resposta: O programa não realiza o que se pretende; não apresenta qualquer valor no terminal.
   Isto acontece porque o programa não atribui exatamente o valor 5.5 à variável x, havendo sempre um certo desvio quando se tratam de doubles.

   Possível correção:

   int main () {
   double sum = 0;
  
   for (double x=0; x < 5.6; x += 0.1) {
   sum += x;
   }
   }

Coloca-se um valor ligeiramente superior a 5.5 (neste caso, 5.6), de forma a garantir que x=5.5 é contabilizado, mas mais nenhum número superior o é.
*/
