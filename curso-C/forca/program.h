#define TAMANHO_PALAVRA 20

void abertura();
void chuta(char palavrasecreta[TAMANHO_PALAVRA], char chutes[26],
           int *chutesdados);
void escolhepalavra(char palavrasecreta[TAMANHO_PALAVRA]);
void desenhaForca(char palavrasecreta[TAMANHO_PALAVRA], char chutes[26],
                  int chutesdados);
int ganhou(char palavrasecreta[TAMANHO_PALAVRA], char chutes[26],
           int chutesdados);
int enforcou(char palavrasecreta[TAMANHO_PALAVRA], char chutes[26],
             int chutesdados);
int jachutou(char letra, char chutes[26], int chutesdados);
void adicionapalavra();
int chuteserrados(char palavrasecreta[TAMANHO_PALAVRA], int chutesdados,
                  char chutes[26]);
int letraexiste(char palavrasecreta[TAMANHO_PALAVRA], char letra);
