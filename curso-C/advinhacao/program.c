#include <stdio.h>

int main() {
  printf("******************************************\n");
  printf("* Bem vindo ao nosso jogo de adivinhação *\n");
  printf("******************************************\n");

  int numSecret = 42;
  int numChute;

  printf("Qual é o seu chute? ");
  scanf("%d", &numChute);
  printf("Seu chute foi %d\n", numChute);

  if (numChute == numSecret) {
    printf("Parabéns, você acertou!\n");
  } else {
    printf("Você errou!\n");
  }
}
