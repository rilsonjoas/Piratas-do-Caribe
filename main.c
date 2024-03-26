#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
  int arma;
  int balas;
  int pos_x, pos_y;
} Jack;

void zerar_cenario(int tam, char cenario[tam][tam]) {
  for (int i = 0; i < tam; i++) {
    for (int j = 0; j < tam; j++) {
      cenario[i][j] = '_';
    }
  }
}

void imprimir_cenario(int tam, char cenario[tam][tam]) {
  for (int i = 0; i < tam; i++) {
    for (int j = 0; j < tam; j++) {
      if (cenario[i][j] != 'K') {
        printf("%c ", cenario[i][j]);
      } else {
        printf("_");
      }
    }
    printf("\n");
  }
}

void imprimir_jack(int tam, char cenario[tam][tam]) {
  for (int i = 0; i < tam; i++) {
    for (int j = 0; j < tam; j++) {
      if (cenario[i][j] != 'S') {
        printf("%c ", cenario[i][j]);
      } else {
        printf("_ ");
      }
    }
    printf("\n");
  }
}

void imprimir_salazar(int tam, char cenario[tam][tam]) {
  for (int i = 0; i < tam; i++) {
    for (int j = 0; j < tam; j++) {
      if (cenario[i][j] != 'J') {
        printf("%c ", cenario[i][j]);
      } else {
        printf("_ ");
      }
    }
    printf("\n");
  }
}

void inicializar_item(int tam, char cenario[tam][tam], char item, int qtd) {
  for (int i = 1; i <= qtd;) {
    int pos_x = rand() % tam;
    int pos_y = rand() % tam;

    if (cenario[pos_x][pos_y] == '_') {
      cenario[pos_x][pos_y] = item;
      i++;
    }
  }
}

void inicializar_guarda(int tam, char cenario[tam][tam], char item, int qtd) {
  for (int i = 1; i <= qtd;) {
    int pos_x = ((rand() % tam) + 16);
    int pos_y = ((rand() % tam) + 16);

    if (cenario[pos_x][pos_y] == '_') {
      cenario[pos_x][pos_y] = item;
      i++;
    }
  }
}

void inicializar_jack(int tam, char cenario[tam][tam], char item[], int qtd) {
  for (int i = 1; i <= qtd;) {
    int pos_x = (rand() % tam);
    int pos_y = (rand() % tam);

    if (cenario[pos_x][pos_y] == '_') {
      cenario[pos_x][pos_y] = *item;
      i++;
    }
  }
}

void inicializar_salazar(int tam, char cenario[tam][tam], char item[],
                         int qtd) {
  for (int i = 1; i <= qtd;) {
    int pos_x = rand() % tam;
    int pos_y = rand() % tam;

    if (cenario[pos_x][pos_y] == '_') {
      cenario[pos_x][pos_y] = *item;
      cenario[pos_x][pos_y + 1] = *item;
      i++;
    }
  }
}

int main(void) {
  srand(time(NULL));

  int tam_area = 20;
  char area[tam_area][tam_area];

  zerar_cenario(tam_area, area);

  Jack jack;
  jack.arma = 0;
  jack.balas = 0;
  jack.pos_x = 0;
  jack.pos_y = 0;

  // Posicionando Jack
  area[jack.pos_x][jack.pos_y] = 'J';

  // Posicionando navio
  area[jack.pos_x + 18][jack.pos_y + 18] = 'N';

  // // Estagio cidade
  do {
    inicializar_item(tam_area, area, 'P', 50);   // Piratas
    inicializar_item(tam_area, area, 'O', 50);   // Obstáculos
    inicializar_item(tam_area, area, 'A', 1);    // Armas
    inicializar_item(tam_area, area, 'B', 20);   // Balas
    inicializar_guarda(tam_area, area, 'G', 10); // Piratas da Guarda

    break;
  } while (jack.pos_x || jack.pos_y != "N"); // TESTAR

  // Navegação jack na cidade
  printf("\n");
  int sair_area = 0;
  do {
    imprimir_cenario(tam_area, area);

    char movimento;

    printf("\nMovimento: ");
    scanf("%c", &movimento);
    getchar();

    switch (movimento) {

    case 'w':
      if (jack.pos_x - 1 >= 0) {
        if (area[jack.pos_x - 1][jack.pos_y] == 'N') {
          sair_area = 1;
          printf("\n\nBatalha naval.\n\n");
        } else if (area[jack.pos_x - 1][jack.pos_y] == 'P' ||
                   area[jack.pos_x - 1][jack.pos_y] == 'G') {
          if (jack.arma == 0 && jack.balas == 0) {

            printf("\n\nVocê foi capturado por piratas. Fim de jogo.\n");
            sair_area = 1;
          } else {
            area[jack.pos_x][jack.pos_y] = '_';
            jack.pos_x--;
            area[jack.pos_x][jack.pos_y] = 'J';
            printf("\n\nVocê matou um pirata.\n\n");
            jack.balas--;
          }
        } else if (area[jack.pos_x - 1][jack.pos_y] == 'A') {
          area[jack.pos_x][jack.pos_y] = '_';
          jack.pos_x--;
          area[jack.pos_x][jack.pos_y] = 'J';
          jack.arma++;
          printf("\n\nAgora você tem %i arma e pode matar os piratas\n\n",
                 jack.arma);
        } else if (area[jack.pos_x - 1][jack.pos_y] == 'B') {
          area[jack.pos_x][jack.pos_y] = '_';
          jack.pos_x--;
          area[jack.pos_x][jack.pos_y] = 'J';
          jack.balas++;
          printf("\n\nAgora você tem %i balas\n\n", jack.balas);
        } else if (area[jack.pos_x - 1][jack.pos_y] == 'O') {
          printf("\n\nVocê caiu em um obstáculo. Tente novamente\n\n");
        } else {
          area[jack.pos_x][jack.pos_y] = '_';
          jack.pos_x--;
          area[jack.pos_x][jack.pos_y] = 'J';
        }
      }
      break;

    case 's':
      if (jack.pos_x + 1 <= tam_area - 1) {
        if (area[jack.pos_x + 1][jack.pos_y] == 'N') {
          sair_area = 1;
          printf(
              "\n\nBatalha naval.\n\n");
        } else if (area[jack.pos_x + 1][jack.pos_y] == 'P' ||
                   area[jack.pos_x + 1][jack.pos_y] == 'G') {
          if (jack.arma == 0 && jack.balas == 0) {
            printf("\n\nVocê foi capturado por piratas. Fim de jogo.\n");
            sair_area = 1;
          } else {
            area[jack.pos_x][jack.pos_y] = '_';
            jack.pos_x++;
            area[jack.pos_x][jack.pos_y] = 'J';
            printf("\n\nVocê matou um pirata.\n\n");
            jack.balas--;
          }
        } else if (area[jack.pos_x + 1][jack.pos_y] == 'A') {
          area[jack.pos_x][jack.pos_y] = '_';
          jack.pos_x++;
          area[jack.pos_x][jack.pos_y] = 'J';
          jack.arma++;
          printf("\n\nAgora você tem %i arma e pode matar os piratas\n\n",
                 jack.arma);
        } else if (area[jack.pos_x + 1][jack.pos_y] == 'B') {
          area[jack.pos_x][jack.pos_y] = '_';
          jack.pos_x++;
          area[jack.pos_x][jack.pos_y] = 'J';
          jack.balas++;
          printf("\n\nAgora você tem %i balas\n\n", jack.balas);
        } else if (area[jack.pos_x + 1][jack.pos_y] == 'O') {
          printf("\n\nVocê caiu em um obstáculo. Tente novamente\n\n");
        } else {
          area[jack.pos_x][jack.pos_y] = '_';
          jack.pos_x++;
          area[jack.pos_x][jack.pos_y] = 'J';
        }
      }
      break;

    case 'a':
      if (jack.pos_y - 1 >= 0) {
        if (area[jack.pos_x][jack.pos_y - 1] == 'N') {
          printf(
              "\n\nBatalha naval.\n\n");
          sair_area = 1;
        } else if (area[jack.pos_x][jack.pos_y - 1] == 'P' ||
                   area[jack.pos_x][jack.pos_y - 1] == 'G') {
          if (jack.arma == 0 && jack.balas == 0) {
            sair_area = 1;
            printf("\n\nVocê foi capturado por piratas. Fim de jogo.\n");
          } else {
            area[jack.pos_x][jack.pos_y] = '_';
            jack.pos_y--;
            area[jack.pos_x][jack.pos_y] = 'J';
            printf("\n\nVocê matou um pirata.\n\n");
            jack.balas--;
          }
        } else if (area[jack.pos_x][jack.pos_y - 1] == 'A') {
          area[jack.pos_x][jack.pos_y] = '_';
          jack.pos_y--;
          area[jack.pos_x][jack.pos_y] = 'J';
          jack.arma++;
          printf("\n\nAgora você tem %i arma e pode matar os piratas\n\n",
                 jack.arma);
        } else if (area[jack.pos_x][jack.pos_y - 1] == 'B') {
          area[jack.pos_x][jack.pos_y] = '_';
          jack.pos_y--;
          area[jack.pos_x][jack.pos_y] = 'J';
          jack.balas++;
          printf("\n\nAgora você tem %i balas\n\n", jack.balas);
        } else if (area[jack.pos_x][jack.pos_y - 1] == 'O') {
          printf("\n\nVocê caiu em um obstáculo. Tente novamente\n\n");
        } else {
          area[jack.pos_x][jack.pos_y] = '_';
          jack.pos_y--;
          area[jack.pos_x][jack.pos_y] = 'J';
        }
      }
      break;

    case 'd':
      if (jack.pos_y + 1 <= tam_area - 1) {
        if (area[jack.pos_x][jack.pos_y + 1] == 'N') {

          printf(
              "\n\nBatalha naval.\n\n");
          sair_area = 1;
        } else if (area[jack.pos_x][jack.pos_y + 1] == 'P' ||
                   area[jack.pos_x][jack.pos_y + 1] == 'G') {
          if (jack.arma == 0 || jack.balas == 0) {
            sair_area = 1;
            printf("\n\nVocê foi capturado por piratas. Fim de jogo.\n");
          } else {
            area[jack.pos_x][jack.pos_y] = '_';
            jack.pos_y++;
            area[jack.pos_x][jack.pos_y] = 'J';
            printf("\n\nVocê matou um pirata.\n\n");
            jack.balas--;
          }
        } else if (area[jack.pos_x][jack.pos_y + 1] == 'A') {
          jack.arma++;
          printf("\n\nAgora você tem %i arma e pode matar os piratas\n\n",
                 jack.arma);
          area[jack.pos_x][jack.pos_y] = '_';
          jack.pos_y++;
          area[jack.pos_x][jack.pos_y] = 'J';

        } else if (area[jack.pos_x][jack.pos_y + 1] == 'B') {
          area[jack.pos_x][jack.pos_y] = '_';
          jack.pos_y++;
          area[jack.pos_x][jack.pos_y] = 'J';
          jack.balas++;
          printf("\n\nAgora você tem %i balas\n\n", jack.balas);
        } else if (area[jack.pos_x][jack.pos_y + 1] == 'O') {
          printf("\n\nVocê caiu em um obstáculo. Tente novamente\n\n");
        } else {
          area[jack.pos_x][jack.pos_y] = '_';
          jack.pos_y++;
          area[jack.pos_x][jack.pos_y] = 'J';
        }
        break;
      }
    }
    printf("\n");
  } while (sair_area == 0);

  // Batalha naval

  int tam_batalha = 20;
  char batalha[tam_batalha][tam_batalha];

  int linha = 0;
  int coluna = 0;
  int navios = 5;
  int turno = 2;
  zerar_cenario(tam_batalha, batalha);
  inicializar_jack(tam_batalha, batalha, "J", 1);
  inicializar_salazar(tam_batalha, batalha, "S", navios);

  while (turno != 0) {

    if (turno % 2 == 0) {
      printf("É a vez do Jack.\n\n");
      imprimir_jack(tam_batalha, batalha);

      printf("\nQual linha você deseja atacar (1-20):");
      scanf("%i", &linha);

      printf("\nQual coluna você deseja atacar (1-20):");
      scanf("%i", &coluna);

      if (batalha[linha - 1][coluna - 1] == 'S') {
        batalha[linha - 1][coluna - 2] = '_';
        batalha[linha - 1][coluna - 1] = '_';
        batalha[linha - 1][coluna] = '_';

        printf("\n\nVocê acertou um navio!\n\n");
        navios--;

        if (navios <= 0) {
          printf("\nJack venceu o jogo!\n\n");
          turno = 0;
        } else {
          turno++;
        }

      } else {
        printf("\n\nVocê errou o tiro.\n\n");
        turno++;
      }

    } else if (turno % 2 != 0) {
      printf("É a vez do Salazar.\n\n");
      imprimir_salazar(tam_batalha, batalha);

      printf("\nQual linha você deseja atacar (1-20):");
      scanf("%i", &linha);

      printf("\nQual coluna você deseja atacar (1-20):");
      scanf("%i", &coluna);

      if (batalha[linha - 1][coluna - 1] == 'J') {
        printf("\nSalazar venceu o jogo!\n\n");
        turno = 0;
      } else {
        printf("\n\nVocê errou o tiro.\n\n");
        turno++;
      }
    } else {
      printf("Fim de jogo.");
    }
  }
  return 0;
}