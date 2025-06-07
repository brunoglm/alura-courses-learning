#include <stdio.h>

#define MAX_TENTATIVAS 3

int main() {
  printf("******************************************\n");
  printf("* Bem vindo ao nosso jogo de adivinhação *\n");
  printf("******************************************\n");

  int numSecret = 42;
  int numChute;

  for (int i = 1; i <= MAX_TENTATIVAS; i++) {
    printf("Tentativa %d de %d\n", i, MAX_TENTATIVAS);
    printf("Qual é o seu chute? ");
    scanf("%d", &numChute);
    printf("Seu chute foi %d\n", numChute);

    int isTheNumberSecret = (numChute == numSecret);
    int isTheNumberBigger = (numChute > numSecret);

    if (isTheNumberSecret) {
      printf("Parabéns, você acertou!\n");
      break;
    } else if (isTheNumberBigger) {
      printf("Seu chute foi menor que o número secreto.\n");
    } else {
      printf("Seu chute foi maior que o número secreto.\n");
    }
  }

  printf("Fim do jogo!\n");
}
