#include <stdio.h>
#include <string.h>

void abertura() {
  printf("************************************\n");
  printf("* Bem-vindo ao jogo da forca!     *\n");
  printf("************************************\n");
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

void chuta(char chutes[26], int *chutesdados) {
  char chute;
  scanf(" %c", &chute);

  chutes[(*chutesdados)] = chute;
  (*chutesdados)++;
}

void escolhepalavra(char palavrasecreta[20]) {
  sprintf(palavrasecreta, "MELANCIA");
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

int ganhou(char palavrasecreta[20], char chutes[26], int chutesdados) {
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

int main() {
  char palavrasecreta[20];

  char chutes[26];
  int chutesdados = 0;

  escolhepalavra(palavrasecreta);
  abertura();

  do {
    desenhaForca(palavrasecreta, chutes, chutesdados);
    chuta(chutes, &chutesdados);
  } while (!ganhou(palavrasecreta, chutes, chutesdados) &&
           !enforcou(palavrasecreta, chutes, chutesdados));
}
