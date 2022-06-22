#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// verifica o mdc
int mdc(long long int numero1, long long int numero2)
{
  if (numero2 == 0)
  {
    return numero1;
  }
  else
  {
    return mdc(numero2, numero1 % numero2);
  }
}

// verifica se o valor é primo
int primo(long long int numero)
{
  int primo = 2, i;
  if (numero == 1 || numero == 0)
  {
    primo = 1;
  }
  else
  {
    for (i = 2; i < numero; i++)
    {
      if (numero % i == 0)
      {
        primo = 1;
        break;
      }
    }
  }
  return primo;
}

// calcula fi(n) p/ totiente de Euler
long long int fi(long long int p, long long int q)
{
  long long int fin;
  fin = (p - 1) * (q - 1);
  return fin;
}

// calcula a chave pública n
long long int chave_pub(long long int p, long long int q)
{
  long long int chave;
  chave = p * q;
  return chave;
}

// resolve exponenciação modular
long long int funcao(long long int base, long long int expoente, long long int modulo)
{
  long long int t = 1, i;
  for (i = 0; i < expoente; i++)
  {
    t = t * base % modulo;
  }
  return t;
}

// calcula o inverso
long long int inverso(long long int chave, long long int modulo)
{
  long long int i = 1, j;
  while (i <= modulo)
  {
    j = (chave * i) % modulo;
    i++;
    if (j == 1)
    {
      break;
    }
  }
  return i - 1;
}
// desencripta o caractere
char descripto(long long int base, long long int expoente, long long int mod)
{
  return (char)funcao(base, expoente, mod);
}

// onde tudo acontece
int main()
{
  long long int escolha, primo_p, primo_q, coprimo_e, chave_n, chave_d, z, i, j, k, l;

  FILE *file1;                   // arquivo que recebe a chave pública
  FILE *file2;                   // arquivo que recebe mensagem criptografada
  FILE *file3;                   // arquivo que rece mensagem descriptografada
  FILE *file4;                   // arquivo que recebe mensagem criptografada externa
  char mensagem[10000];          // recebe a mensagem
  char descript[10000];          // recebe a mensagem descriptografada
  long long int numero_c[10000]; // recebe o valor inteiro do char depois que foi encriptado
  long long int numero[10000];   // recebe o valor inteiro do char antes de ser criptado

  // menu onde o usuario vai escolher a opcao desejada
  printf("Escolha uma tarefa valida:\n");
  printf("1-Gerar chave publica\n");
  printf("2-Criptografar\n");
  printf("3-Descriptografar\n");
  printf("0-Fechar o programa \n");

  scanf("%lld", &escolha);

  // programa fica em loop até o usuário digitar 0
  while (escolha != 0)
  {
    while (escolha < 1 || escolha > 3)
    {
      printf("Escolha uma tarefa valida\n");
      scanf("%lld", &escolha);
    }

    // gera a chave pública
    if (escolha == 1)
    {
      printf("escolha um primo 'p':\n");
      scanf("%lld", &primo_p); // atribui valor para o primo p
      while (primo(primo_p) == 1)
      {
        printf("Numero invalido\n");
        scanf("%lld", &primo_p);
      }

      printf("escolha um primo 'q':\n");
      scanf("%lld", &primo_q); ////atribui valor para o primo q
      while (primo(primo_q) == 1)
      {
        printf("Numero invalido\n");
        scanf("%lld", &primo_q);
      }

      // solicita um numero relativamente primo, o "e"
      printf("escolha um expoente 'e' coprimo a %lld:\n", fi(primo_p, primo_q));
      scanf("%lld", &coprimo_e);
      while (mdc(coprimo_e, fi(primo_p, primo_q)) != 1) // fica em loop até o usuário digitar um valor válido
      {
        printf("Numero invalido\n");
        scanf("%lld", &coprimo_e);
      }

      // abre aquivo e salva a chave publica
      file1 = fopen("Chave publica.txt", "a");
      fprintf(file1, "n=%lld\n", chave_pub(primo_p, primo_q));
      fprintf(file1, "e=%lld", coprimo_e);
      fclose(file1);

      printf("Arquivo com a chave publica salvo no diretorio de execucao\n");
    }

    // criptografa a mensagem
    if (escolha == 2)
    {
      printf("Digite a mensagem para ser encriptada:\n");

      getchar();
      fgets(mensagem, 10000, stdin); // salva a string

      z = strlen(mensagem); // salva o tamanho da string

      for (i = 0; i < z; i++) // converte o char para um valor inteiro
      {
        numero[i] = mensagem[i];
      }

      // solicita chave publica
      printf("Digite a chave publica recebida previamente,'n' e 'e' respectivamente:\n");
      scanf("%lld", &chave_n);
      scanf("%lld", &coprimo_e);

      // abre  o arquivo e salva a mensagem encriptada
      file2 = fopen("Mensagem encriptada.txt", "a");

      // mensagem criptografada com o valor inteiro e salva no arquivo com separador
      for (i = 0; i < z; i++)
      {
        j = numero[i];
        numero_c[i] = funcao(j, coprimo_e, chave_n);
        if (i != z - 1)
        {
          fprintf(file2, "%lld ", funcao(j, coprimo_e, chave_n));
        }
        else
        {
          fprintf(file2, "%lld", funcao(j, coprimo_e, chave_n));
        }
      }

      fclose(file2);
      printf("Arquivo com mensagem encriptada salva no diretorio de execucao\n");
    }

    // descriptar a mensagem
    // solicitando a chave privada, valores de p, q, e
    if (escolha == 3) // gera o arquivo descriptografado
    {
      printf("Digite o valor de 'p':\n"); // atribui valor ao primo p
      scanf("%lld", &primo_p);

      printf("Digite o valor de 'q':\n"); // atribui valor ao primo q
      scanf("%lld", &primo_q);

      printf("Digite o valor de 'e':\n"); // atribui valor ao corpimo e
      scanf("%lld", &coprimo_e);

      chave_n = chave_pub(primo_p, primo_q); // atribui valor o n
      k = fi(primo_p, primo_q);              // k recebe o valor de (p-1)*(q-1)
      chave_d = inverso(coprimo_e, k);       // atribui valor ao inverso d

      file3 = fopen("Mensagem original.txt", "a");   // abre o arquivo
      file4 = fopen("Mensagem encriptada.txt", "r"); // abre o arquivo com a mensagem externa

      fscanf(file4, "%lld", &l);

      descript[0] = descripto(l, chave_d, chave_n);

      for (i = 1; descript[i - 1] != '\n'; i++)
      {
        fscanf(file4, "%lld", &l);
        descript[i] = descripto(l, chave_d, chave_n);
      }

      fprintf(file3, "%s\n", descript); // grava a mensagem no arquivo

      fclose(file3); // fecha o arquivo
      fclose(file4); // fecha o arquivo
      printf("Mesagem salva no diretório de execução\n");
    }

    // apresenta o menú mais uma vez
    // para finalizar o usuario deve digitar 0
    printf("Escolha uma nova tarefa:\n");
    printf("1-Gerar chave publica\n");
    printf("2-Criptografar\n");
    printf("3-Descriptografar\n");
    printf("0-Fechar o programa \n");

    scanf("%lld", &escolha);
  }
  return 0;
}