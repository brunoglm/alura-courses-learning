#include "program.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int letraexiste(char palavrasecreta[TAMANHO_PALAVRA], char letra) {
  for (int j = 0; j < strlen(palavrasecreta); j++) {
    if (letra == palavrasecreta[j]) {
      return 1;
    }
  }

  return 0;
}

int chuteserrados(char palavrasecreta[TAMANHO_PALAVRA], int chutesdados,
                  char chutes[26]) {
  int erros = 0;

  for (int i = 0; i < chutesdados; i++) {

    if (!letraexiste(palavrasecreta, chutes[i])) {
      erros++;
    }
  }

  return erros;
}

int enforcou(char palavrasecreta[TAMANHO_PALAVRA], char chutes[26],
             int chutesdados) {
  return chuteserrados(palavrasecreta, chutesdados, chutes) >= 5;
}

int ganhou(char palavrasecreta[TAMANHO_PALAVRA], char chutes[26],
           int chutesdados) {
  for (int i = 0; i < strlen(palavrasecreta); i++) {
    if (!jachutou(palavrasecreta[i], chutes, chutesdados)) {
      return 0;
    }
  }
  return 1;
}

void abertura() {
  printf("/****************/\n");
  printf("/ Jogo de Forca */\n");
  printf("/****************/\n\n");
}

void chuta(char palavrasecreta[TAMANHO_PALAVRA], char chutes[26],
           int *chutesdados) {
  char chute;
  printf("Qual letra? ");
  scanf(" %c", &chute);

  if (letraexiste(palavrasecreta, chute)) {
    printf("Você acertou: a palavra tem a letra %c\n\n", chute);
  } else {
    printf("\nVocê errou: a palavra NÃO tem a letra %c\n\n", chute);
  }

  chutes[(*chutesdados)] = chute;
  (*chutesdados)++;
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

void desenhaForca(char palavrasecreta[TAMANHO_PALAVRA], char chutes[26],
                  int chutesdados) {
  int erros = chuteserrados(palavrasecreta, chutesdados, chutes);

  printf("  _______       \n");
  printf(" |/      |      \n");
  printf(" |      %c%c%c  \n", (erros >= 1 ? '(' : ' '),
         (erros >= 1 ? '_' : ' '), (erros >= 1 ? ')' : ' '));
  printf(" |      %c%c%c  \n", (erros >= 3 ? '\\' : ' '),
         (erros >= 2 ? '|' : ' '), (erros >= 3 ? '/' : ' '));
  printf(" |       %c     \n", (erros >= 2 ? '|' : ' '));
  printf(" |      %c %c   \n", (erros >= 4 ? '/' : ' '),
         (erros >= 4 ? '\\' : ' '));
  printf(" |              \n");
  printf("_|___           \n");
  printf("\n\n");

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

void escolhepalavra(char palavrasecreta[TAMANHO_PALAVRA]) {
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

void adicionapalavra() {
  char quer;

  printf("Você deseja adicionar uma nova palavra ao jogo? (S/N)\n");
  scanf(" %c", &quer);

  if (quer == 'S') {
    printf("Digite a nova palavra:\n");
    char novapalavra[TAMANHO_PALAVRA];
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

int main() {
  char palavrasecreta[TAMANHO_PALAVRA];

  char chutes[26];
  int chutesdados = 0;

  escolhepalavra(palavrasecreta);
  abertura();

  do {
    desenhaForca(palavrasecreta, chutes, chutesdados);
    chuta(palavrasecreta, chutes, &chutesdados);
  } while (!ganhou(palavrasecreta, chutes, chutesdados) &&
           !enforcou(palavrasecreta, chutes, chutesdados));

  if (ganhou(palavrasecreta, chutes, chutesdados)) {
    printf("\nParabéns, você ganhou!\n\n");

    printf("       ___________      \n");
    printf("      '._==_==_=_.'     \n");
    printf("      .-\\:      /-.    \n");
    printf("     | (|:.     |) |    \n");
    printf("      '-|:.     |-'     \n");
    printf("        \\::.    /      \n");
    printf("         '::. .'        \n");
    printf("           ) (          \n");
    printf("         _.' '._        \n");
    printf("        '-------'       \n\n");
  } else {
    printf("\nPuxa, você foi enforcado!\n");
    printf("A palavra era **%s**\n\n", palavrasecreta);

    printf("    _______________         \n");
    printf("   /               \\       \n");
    printf("  /                 \\      \n");
    printf("//                   \\/\\  \n");
    printf("\\|   XXXX     XXXX   | /   \n");
    printf(" |   XXXX     XXXX   |/     \n");
    printf(" |   XXX       XXX   |      \n");
    printf(" |                   |      \n");
    printf(" \\__      XXX      __/     \n");
    printf("   |\\     XXX     /|       \n");
    printf("   | |           | |        \n");
    printf("   | I I I I I I I |        \n");
    printf("   |  I I I I I I  |        \n");
    printf("   \\_             _/       \n");
    printf("     \\_         _/         \n");
    printf("       \\_______/           \n");
  }

  adicionapalavra();
}
