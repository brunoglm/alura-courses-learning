#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  printf("******************************************\n");
  printf("* Bem vindo ao nosso jogo de adivinhação *\n");
  printf("******************************************\n");

  int segundos = time(0);
  srand(segundos);
  int numeroGrande = rand();

  int numSecret = numeroGrande % 100;

  int numChute;
  int tentativas = 1;

  double pontos = 1000;

  while (1) {
    printf("Tentativa %d\n", tentativas);

    printf("Qual é o seu chute? ");
    scanf("%d", &numChute);
    printf("Seu chute foi %d\n", numChute);

    if (numChute < 0) {
      printf("Você não pode chutar números negativos!\n");
      continue;
    }

    int isTheNumberSecret = (numChute == numSecret);
    int isTheNumberBigger = (numChute > numSecret);

    if (isTheNumberSecret) {
      printf("Parabéns, você acertou!\n");
      break;
    } else if (isTheNumberBigger) {
      printf("Seu chute foi maior que o número secreto.\n");
    } else {
      printf("Seu chute foi menor que o número secreto.\n");
    }

    tentativas++;

    double pontosPerdidos = abs(numChute - numSecret) / (double)2;
    pontos -= pontosPerdidos;
  }

  printf("Fim do jogo!\n");
  printf("Você acertou em %d tentativas!\n", tentativas);
  printf("Total de pontos: %.2f\n", pontos);
}
