#include "program.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void abertura() {
  printf("************************************\n");
  printf("* Bem-vindo ao jogo da forca!     *\n");
  printf("************************************\n");
}

void chuta(char chutes[26], int *chutesdados) {
  char chute;
  scanf(" %c", &chute);

  chutes[(*chutesdados)] = chute;
  (*chutesdados)++;
}

void adicionapalavra() {
  char quer;

  printf("Você deseja adicionar uma nova palavra ao jogo? (S/N)\n");
  scanf(" %c", &quer);

  if (quer == 'S') {
    printf("Digite a nova palavra:\n");
    char novapalavra[20];
    scanf("%s", novapalavra);

    FILE *f;
    f = fopen("palavras.txt", "r+");
    if (f == 0) {
      printf("Desculpe, banco de palavras não disponível.\n\n");
      exit(1);
    }

    int qtd;
    fscanf(f, "%d", &qtd);
    qtd++;

    fseek(f, 0, SEEK_SET);
    fprintf(f, "%d", qtd);

    fseek(f, 0, SEEK_END);
    fprintf(f, "\n%s", novapalavra);

    fclose(f);
  }
}

void escolhepalavra(char palavrasecreta[20]) {
  FILE *f;
  f = fopen("palavras.txt", "r");
  if (f == 0) {
    printf("Desculpe, banco de palavras não disponível.\n\n");
    exit(1);
  }

  int qtddepalavras;
  fscanf(f, "%d", &qtddepalavras);

  srand(time(0));
  int randomico = rand() % qtddepalavras;

  for (int i = 0; i <= randomico; i++) {
    fscanf(f, "%s", palavrasecreta);
  }

  fclose(f);
}

void desenhaForca(char palavrasecreta[20], char chutes[26], int chutesdados) {
  for (int i = 0; i < strlen(palavrasecreta); i++) {

    int achou = jachutou(palavrasecreta[i], chutes, chutesdados);

    if (achou) {
      printf("%c ", palavrasecreta[i]);
    } else {
      printf("_ ");
    }
  }
  printf("\n");
}

int acertou(char palavrasecreta[20], char chutes[26], int chutesdados) {
  for (int i = 0; i < strlen(palavrasecreta); i++) {
    if (!jachutou(palavrasecreta[i], chutes, chutesdados)) {
      return 0;
    }
  }
  return 1;
}

int enforcou(char palavrasecreta[20], char chutes[26], int chutesdados) {
  int erros = 0;
  for (int i = 0; i < chutesdados; i++) {
    int existe = 0;
    for (int j = 0; j < strlen(palavrasecreta); j++) {
      if (chutes[i] == palavrasecreta[j]) {
        existe = 1;
        break;
      }
    }

    if (!existe)
      erros++;
  }

  return erros >= 5;
}

int jachutou(char letra, char chutes[26], int chutesdados) {
  int achou = 0;

  for (int j = 0; j < chutesdados; j++) {
    if (chutes[j] == letra) {
      achou = 1;
      break;
    }
  }

  return achou;
}

int main() {
  char palavrasecreta[20];

  char chutes[26];
  int chutesdados = 0;

  escolhepalavra(palavrasecreta);
  abertura();

  do {
    desenhaForca(palavrasecreta, chutes, chutesdados);
    chuta(chutes, &chutesdados);
  } while (!acertou(palavrasecreta, chutes, chutesdados) &&
           !enforcou(palavrasecreta, chutes, chutesdados));
}
