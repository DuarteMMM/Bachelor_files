/* ***************************************************************************
 *                                                                           *
 *              Série 8 (02/12/2019), exercício 4 - Programação              *
 *                      Duarte Marques - ist196523                           *
 *                      Rodrigo Simões - ist196564                           *
 *                                                                           *
 *************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>

// Menu explicativo

void menu ()
{
  printf ("\n*-*-*-*-* Directorias e ficheiros *-*-*-*-*\n");

  // Nota: não se impôs a necessidade de escrever 'ls' nem 'dir' para facilitar leituras do terminal, 'if's e 'else's
  
  printf ("\n (1) Para executar o comando ls ou dir, digite './4serie8.c' ;");
  printf ("\n (2) Para executar o comando ls/dir -l, digite './4serie8.c -l' ;");
  printf ("\n (3) Para procurar uma determinada pasta, digite './4serie8.c [nome da diretoria]' ;");
  printf ("\n (4) Para executar os dois comandos anteriores, digite './4serie8c -l [nome da diretoria]' .\n");
}

// Main

int main (int argc, char **argv)
{

  // Declaração das variáveis
   
  int            escolha   ; // Para decidir qual o comando a executar
  DIR            *d1       ; // Diretoria para leitura
  struct dirent  *dent     ; // Ponteiro para informação do membro da diretoria a ler
  int            teste     ; // Teste para 'lstat' ou 'stat'
  struct stat    stat1     ; // Para utilizar na função 'lstat' ou 'stat'
  struct tm      *time     ; // Ponteiro para a estrutura 'struct tm' (para a função localtime')
  char           data [13] ; // String para escrever informações horárias (com espaço  mínimo necessário para 'mês dia horas:minutos')
  char           *nome     ; // Vetor para o nome da pasta (opção 3)
  int            len       ; // Comprimento do vetor com o nome da diretiva "principal"

  // Decidir qual o comando a executar

  // Opção 1
 
  if (argc == 1)
    {
      menu ();
      printf ("\nO programa irá executar o comando ls/dir.\n\n");
      escolha = 1;
    }


  if (argc == 2)
    {
      // Opção 2
      
      if (strcmp (argv [1], "-l") == 0)
	{
	  menu ();
	  printf ("\nO programa irá executar o comando -l.\n\n");
	  escolha = 2;
	}

      // Opção 3
      
      else
	{
	  menu ();
	  printf ("\nO programa irá pesquisar a diretoria %s.\n\n", argv [1]);
	  escolha = 3;
	}
    }

  // Opção 4
  
  if ( (argc == 3) && (strcmp (argv [1], "-l") == 0) )
    {
      menu ();
      printf ("\nO programa irá executar os comandos 2 e 3.\n\n");
      escolha = 4;
    }

  // Digitado algo inválido

  if ( (argc > 3) || ( (argc == 3) && (strcmp (argv [1], "-l") != 0 ) ) )
    {
      printf ("\nERRO: Digitou algo inválido.\n\n");
      menu ();
      printf ("\n-FIM-\n\n");
      return 1;
    }

  // Execução de ls/dir
  
  if (escolha == 1) 
    {
      d1 = opendir (".") ; // Abrir a diretoria de leitura

      // Testar a abertura da diretoria de leitura
	
      if (d1 == NULL)
	{
	  printf ("\nERRO: A diretoria não abriu corretamente.\n\n");
	  return 2;
	}

      // Leituras sucessivas da diretoria
 
      while (1)
	{
	  dent = readdir (d1); // Membro da diretoria
	    
	  // Verificar se já se chegou ao fim
	    
	  if (dent  == NULL)
	    break;
	    
	  printf ("%s\n", dent->d_name);  // Escrever os nomes dos membros da diretoria
	}
	
      closedir (d1);  // Fechar a diretoria
    }

  // Execução de 'ls/dir -l'

  if (escolha == 2)
    {
      d1 = opendir (".");
	
      if (d1 == NULL)
	{
	  printf ("\nERRO: A diretoria não abriu corrretamente.\n\n");
	  return 3;
	}

      // Obter informação para cada ficheiro e escrevê-la no ecrã

      while (1)
	{
	  dent = readdir (d1);
	    
	  if (dent == NULL)
	    break;

	  // Dar informação referente ao ficheiro
	    
	  // Windows
	    
#ifdef _WIN32
	  teste = stat (dent->d_name, &stat1);

	  //Linux
	    
#else
	  teste = lstat (dent->d_name, &stat1);
#endif

	  // Testar a execução da função 'lstat' / 'stat'

	  if (teste != 0)
	    {
	      printf ("\nERRO: A função 'stat ou 'lstat', para o ficheiro %s, falhou.\n", dent->d_name);
	      break;
	    }

	  // Receber informações do tempo
	    
	  time = localtime (&stat1.st_mtime);

	  // Escrever informações de tempo numa string

	  strftime (data, 13, "%b %d %H:%M", time); // Mês Dia Horas:Minutos
	    
	  printf ("%5ld %s %s\n", stat1.st_size, data, dent->d_name);  // Escrever tamanho em bytes, informações de tempo e nome do ficheiro
	}

      closedir (d1); // Fechar a diretoria
    }

  // Informações sobre uma dada pasta
  
  if (escolha == 3)
    {
      nome = (char*) malloc ( (strlen (argv [1] + 3)) * sizeof (char) ); // Alocar espaço para o vetor do nome

      // Nota: Alocou-se um espaço de (comprimento_nome + espaço para '//' + terminador)

      // Testar a alocação de espaço
            
      if (nome == NULL)
	{
	  printf ("\nERRO: A alocação de memória não foi bem efetuada.\n\n");
	  return 4;
	}

      strcpy (nome, argv [1]);  // Adicionar a 'nome' o que se encontra em argv [1]

      // Adicionar no princípio de 'nome': '\\', em Windows, ou '/', em Unix
      
#ifdef _Win32
      strcat (nome, "\\");
#else
      strcat (nome, "/");
#endif
	
      d1 = opendir (nome);  // Abrir a diretiva com o nome criado

      // Testar a abertura da diretiva
      
      if (d1 == NULL)
	{
	  printf ("\nERRO: A diretiva '%s' não abriu corretamente.\n\n", nome);
	  free (nome);  // Libertar a memória do vetor
	  return 5;
	}

      // Escrever no terminal os nomes dos ficheiros na pasta

      while (1)
	{
	  dent = readdir (d1);
	    
	  if (dent == NULL)
	    break;
	    
	  printf ("%s\n", dent->d_name);
	}

      free (nome);  // Libertar a memória do vetor
      closedir (d1);   // Fechar a diretiva
    }

  // Executar os comandos 2 e 3
  
  if (escolha == 4)
    {
      nome = (char*) malloc ( ( strlen (argv [2] + 3) ) * sizeof (char) );
      
      if (nome == NULL)
	{
	  printf ("\nERRO: A alocação de memória para o vetor do nome da diretiva não se efetuou corretamente.\n\n");
	  return 6;
	}

      strcpy (nome, argv [2]);
      
#ifdef _Win32
      strcat (nome, "\\");
#else
      strcat (nome, "/");
#endif	
	
      d1 = opendir (nome);
	
      if (d1 == NULL)
	{
	  printf ("\nERRO: A diretiva '%s' não abriu corretamente.\n\n", nome);
	  free (nome);
	  return 7;
	}

      len = strlen (nome);
		    
      while (1)
	{
	  dent = readdir (d1);
	    
	  if (dent == NULL)
	    break;

	  nome = (char*) realloc (nome, (len + strlen (dent->d_name) + 3) * sizeof (char));  // Dar um novo tamanho ao vetor


	  strcpy (nome, argv [2]);  // Colocar nome da diretiva
	    
#ifdef _Win32
	  strcat (nome, "\\");
#else
	  strcat (nome, "/");
#endif

	  strcat (nome, dent->d_name);  // Colocar o nome de cada pasta depois
	  
	  if (nome == NULL)
	    {
	      printf ("\nERRO: A alocação de memória para um vetor de nome não foi efetuada corretamente.\n");
	      break;
	    }
	    
#ifdef _WIN32
	  teste = stat (nome, &stat1);
#else
	  teste = lstat (nome, &stat1);
#endif

	  if (teste != 0)
	    {
	      printf ("\nERRO: A função stat/lstat não funcionou corretamente para %s.\n\n", dent->d_name);
	      break;
	    }

	  time = localtime (&stat1.st_mtime);

	  strftime (data, 13, "%b %d %H:%M", time);
	    
	  printf ("%5ld %s %s\n", stat1.st_size, data, dent->d_name);
	}

      free (nome);
      closedir (d1);
    }

  // Finalizar Programa

  printf ("\n-FIM-\n\n");
  return 0;
}
