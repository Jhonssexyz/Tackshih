#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <locale.h>

#define LARGURA_TELA 160
#define tam 100

int jx, jy, l, c, chx, chy, pfx, pfy, vida_pers, atq_pers, dist_pers, T_atq, antx, anty, p_atqx, p_atqy, portalxx, portalyy, portalx, portaly, Bx, By, MAPA_SIZE;
int num_goblins;
int vida_goblin, atq_goblin, dist_goblin;
int **goblins;
char tecla;
char porta_char = 'D';
int i, tot;
int loop = 1;
int primeiraFaseConcluida = 0;

struct teste {
    char nome[50];
};

void menu() {
    system("cls");
    printf("\t\t\t\t\t\t d888888b   .d8b.   .o88b. db   dD .d8888. db   db d888888b db   db\n");
    printf("\t\t\t\t\t\t   `88'    d8' `8b d8P  Y8 88 ,8P' 88'  YP 88   88   `88'   88   88\n");
    printf("\t\t\t\t\t\t    88     88ooo88 8P      88,8P   `8bo.   88ooo88    88    88ooo88\n");
    printf("\t\t\t\t\t\t    88     88~~~88 8b      88`8b     `Y8b. 88~~~88    88    88~~~88 \n");
    printf("\t\t\t\t\t\t    88     88   88 Y8b  d8 88 `88. db   8D 88   88   .88.   88   88\n");
    printf("\t\t\t\t\t\t    YP     YP   YP  `Y88P' YP   YD `8888Y' YP   YP Y888888P YP   YP\n");
    printf("\n\n\n");
    printf("\t\t\t\t\t\t\t\t\t (1) Jogar\n");
    printf("\t\t\t\t\t\t\t\t\t (2) Tutorial\n");
    printf("\t\t\t\t\t\t\t\t\t (3) Sair\n");
}
void movimento_goblins() {
    int i;
    for (i = 0; i < num_goblins; i++) {
        int direcao = rand() % 4;

        switch (direcao) {
            case 0:
                if (goblins[i][1] > 1) {
                    goblins[i][1]--;
                }
                break;
            case 1:
                if (goblins[i][1] < MAPA_SIZE - 2) {
                    goblins[i][1]++;
                }
                break;
            case 2:
                if (goblins[i][0] > 1) {
                    goblins[i][0]--;
                }
                break;
            case 3:
                if (goblins[i][0] < MAPA_SIZE - 2) {
                    goblins[i][0]++;
                }
                break;
        }

        if (goblins[i][0] == jx && goblins[i][1] == jy) {
            vida_pers -= atq_goblin;
            if (vida_pers <= 0) {
                system("cls");
                printf("Você morreu!\n");
                exit(0);
            }
        }
    }
}

void adicionar_goblin() {
    int i;
    for (i = 0; i < num_goblins; i++) {
        if (goblins[i][0] == 0 && goblins[i][1] == 0) {
            goblins[i][0] = rand() % (MAPA_SIZE - 2) + 1;
            goblins[i][1] = rand() % (MAPA_SIZE - 2) + 1;
            break;
        }
    }
}

void status_G() {
    dist_pers = 2;
    vida_pers = 40;
    atq_pers = 15;
    T_atq = 1;
}

void status_A() {
    dist_pers = 5;
    vida_pers = 30;
    atq_pers = 10;
    T_atq = 2;
}

void status_M() {
    dist_pers = 5;
    vida_pers = 10;
    atq_pers = 25;
    T_atq = 3;
}

void selecionar_personagem() {
    system("cls");
    printf("Selecione seu personagem:\n");
    printf("1. Fácil\n");
    printf("2. Médio\n");
    printf("3. Inferno\n");
    int escolha;
    scanf("%d", &escolha);

    switch (escolha) {
        case 1:
            status_G();
            break;
        case 2:
            status_A();
            break;
        case 3:
            status_M();
            break;
        default:
            printf("Opção inválida. Por favor, escolha novamente.\n");
            selecionar_personagem();
            break;
    }
}

void botoes(char tecla) {
    int Ajx = jx;
    int Ajy = jy;

    switch (tecla) {
        case 'w':
        case 'W':
            Ajy--;
            break;
        case 's':
        case 'S':
            Ajy++;
            break;
        case 'a':
        case 'A':
            Ajx--;
            break;
        case 'd':
        case 'D':
            Ajx++;
            break;
        case 'q':
        case 'Q':
            exit(0);
            break;
        case 'i':
        case 'I':
            if (porta_char == '=') {
                printf("Parabéns! Você passou.\n");
                primeiraFaseConcluida = 1; // Marca que o jogador concluiu a primeira fase
            } else if (jx == chx && jy == chy) {
                porta_char = '='; // Altera o porta_char para '=' quando o jogador interage com a chave
            } else if (jx == portalxx && jy == portalyy) {
                jx = portalx;
                jy = portaly;
            } else if (jx == portalx && jy == portaly) {
                jx = portalxx;
                jy = portalyy;
            }
            break;
    }
    // Verificar se a nova posição está dentro dos limites do mapa
    if (Ajx > 0 && Ajx < MAPA_SIZE - 1 && Ajy > 0 && Ajy < MAPA_SIZE - 1) {
        antx = jx;
        anty = jy;
        jx = Ajx;
        jy = Ajy;
    }

    // Verificar se o personagem alcançou a porta e passar para a segunda fase
    if (Ajx == pfx && Ajy == pfy && porta_char == '=') {
        primeiraFaseConcluida = 1;
    }
}

void fase(int num_goblins) {
    MAPA_SIZE = 15;
    int i, LA;
    pfx = 7;
    pfy = 14;
    system("cls");
    for (c = 0; c < MAPA_SIZE; c++) {
        for (l = 0; l < MAPA_SIZE; l++) {
            if (l == 7 && c == 0) {
                printf("%c", porta_char);
            } else {
                int is_goblin = 0;
                for (i = 0; i < num_goblins; i++) {
                    if (goblins[i][0] == l && goblins[i][1] == c) {
                        printf("X");
                        is_goblin = 1;
                        break;
                    }
                }
                if (!is_goblin) {
                    if (jx == l && jy == c) {
                        printf("&");
                    } else if (l == chx && c == chy) {
                        printf("@");
                    } else if (l == chx && c == chy && porta_char == '=') {
                        printf("=");
                    } else if (l < 1 || l > 13 || c < 1 || c > 13) {
                        printf("*");
                    } else {
                        printf(" ");
                    }
                }
            }
        }
        printf("\n");
    }
    for (LA = 0; LA <= 7; LA++) {
        if (LA == 0) {
            printf("|");
        } else if (LA == 1) {
            printf("Vida: ");
        } else if (LA == 6) {
            printf("%d", vida_pers);
        } else if (LA == 7) {
            printf("|\n");
        }
    }
}
void terceiraFase() {
    system("cls");
    printf("Bem-vindo à terceira fase!\n");
    MAPA_SIZE = 40;
    jx = 1;
    jy = 38;
    pfx = 38;
    pfy = 0;
    chx = 30;
    chy = 30;
    portalxx = 34; 
	portalyy = 34;
	portalx = 10;
	portaly = 24;
    porta_char = 'D';
    int vampirox = 20; 
    int vampiroy = 20;
    int atq_vampiro = 20;
    int i, j;
    int labirinto[MAPA_SIZE][MAPA_SIZE]; // Matriz para representar o labirinto

    // Preencher o labirinto com espinhos
    for (i = 0; i < MAPA_SIZE; i++) {
        for ( j = 0; j < MAPA_SIZE; j++) {
            if (i == 0 || i == MAPA_SIZE - 1 || j == 0 || j == MAPA_SIZE - 1) {
                labirinto[i][j] = 1; // Preencher bordas com espinhos
            } else {
                labirinto[i][j] = 0; // Preencher espaços vazios
            }
        }
    }

    while (1) {
        system("cls");
        // Desenhar o mapa do labirinto
        for (c = 0; c < MAPA_SIZE; c++) {
            for (l = 0; l < MAPA_SIZE; l++) {
            	if (l == vampirox && c == vampiroy) {
                    printf("V");
                }else if (l == pfx && c == pfy) {
                    printf("%c", porta_char);
                } else if (labirinto[c][l] == 1) {
                    printf("*"); // Representar as paredes do labirinto como espinhos
                } else {
                    if (jx == l && jy == c) {
                        printf("&");
                    } else if (l == chx && c == chy) {
                        printf("@");
                    }else if(portalxx == l && portalyy == c){
                    	printf(">");
					}
					else if(portalx == l && portaly == c){
                    	printf("<");
					}
					 else if((l > 24 && l < 36) && (c == 25 || c == 35) || (c > 24 && c < 36) && (l == 25 || l == 35)){
                    	printf("#");
					} else if((jx > 24 && jx < 36) && (jy == 25 || jy == 35) || (jy > 24 && jy < 36) && (jx == 25 || jx == 35)){
						vida_pers = vida_pers - 40 ;
					}
					else {
                        printf(" ");
                    }
                }
            }
            printf("\n");
        }
        // Determinar a direção de movimento do vampiro (horizontal ou vertical)
        int direcao = rand() % 2; // 0 para movimento horizontal, 1 para movimento vertical

        // Movimentar o vampiro apenas na direção escolhida
        if (direcao == 0) { // Movimento horizontal
            int direcao_x = (jx > vampirox) ? 1 : -1; // Define a direção X do vampiro baseado na posição do jogador

            // Verifica se o movimento não ultrapassa os limites do labirinto e se não há obstáculos
            if (vampirox + direcao_x >= 1 && vampirox + direcao_x < MAPA_SIZE - 1 && labirinto[vampirox + direcao_x][vampiroy] != 1) {
                vampirox += direcao_x;
            }
        } else { // Movimento vertical
            int direcao_y = (jy > vampiroy) ? 1 : -1; // Define a direção Y do vampiro baseado na posição do jogador

            // Verifica se o movimento não ultrapassa os limites do labirinto e se não há obstáculos
            if (vampiroy + direcao_y >= 1 && vampiroy + direcao_y < MAPA_SIZE - 1 && labirinto[vampirox][vampiroy + direcao_y] != 1) {
                vampiroy += direcao_y;
            }
        }

        // Colisão entre o vampiro e o jogador
        if (jx == vampirox && jy == vampiroy) {
            vida_pers -= atq_vampiro;
            if (vida_pers <= 0) {
                system("cls");
                printf("Você foi morto pelo vampiro!\n");
                exit(0);
            }
        }
        // Mostrar o status do jogador
        printf("Vida: %d\n", vida_pers);

        // Capturar a tecla pressionada
        tecla = getch();
        botoes(tecla);
        if(jx == portalx && jy == portaly){
        	jx = portalxx;
        	jy = portalyy;
		}
		else if(jx == portalxx && jy == portalyy){
			jx = portalx;
        	jy = portaly;
		}
        // Verificar se o jogador interagiu com a porta para vencer o jogo
        if (jx == pfx && jy == pfy + 1 && porta_char == '=') {
            printf("Parabéns!\n");
			 printf("Você venceu o jogo!\n");
            exit(0);
            break;
        }
    }
}

void segundaFase() {
    system("cls");
    printf("Bem-vindo à segunda fase!\n");
    int i, j, k;
    MAPA_SIZE = 30;
    Bx = 14;
    By = 27;
    jx = 15;
    jy = 28;
    chx = 20;
    chy = 16;
    porta_char = 'D';
    pfx = 15;
    pfy = 0;
    int espinhosAtivados = 1; // Flag para controlar se os espinhos estão ativados ou desativados
    
    // Inicializar goblins
    for (i = 0; i < num_goblins; i++) {
        goblins[i][0] = rand() % (MAPA_SIZE - 2) + 1; // Randomizar posição X do goblin
        goblins[i][1] = rand() % (MAPA_SIZE - 3) + 1; // Randomizar posição Y do goblin
    }

    // Loop principal da segunda fase
    while (1) {
        // Inicializar o mapa da segunda fase
        for (i = 0; i < MAPA_SIZE; i++) {
            for (j = 0; j < MAPA_SIZE; j++) {
                if (pfx == j && pfy == i && porta_char == '=') {
                    printf("=");
                } else if(pfx == j && pfy == i && porta_char == 'D'){
                    printf("D");
                }
                else if (i == 0 || i == MAPA_SIZE - 1 || j == 0 || j == MAPA_SIZE - 1) {
                    printf("*");
                } else if (jx == j && jy == i) {
                    printf("&");
                } else if (chx == j && chy == i) {
                    printf("@");
                } else if (((j == 10 || j == 20) && i <= 29 && i > 24) || (j >= 10 && j <= 20 && i == 24)) {
                    if (espinhosAtivados) {
                        printf("#");
                        // Verificar se o jogador está na mesma posição que os espinhos
                        if (jx == j && jy == i) {
                            vida_pers = vida_pers - 40 ; // Reduzir a vida do jogador
                            if (vida_pers < 0) {
                                system("cls");
                                printf("Você morreu!\n");
                                exit(0);
                            }
                        }
                    } else {
                        printf(" ");
                    }
                } else if (Bx == j && By == i) {
                    printf("O");
                } else {
                    // Verificar se o jogador está na mesma posição que um goblin
                    int is_goblin = 0;
                    for (k = 0; k < num_goblins; k++) {
                        if (goblins[k][0] == j && goblins[k][1] == i) {
                            printf("X");
                            is_goblin = 1;
                            break;
                        }
                    }
                    if (!is_goblin) {
                        printf(" ");
                    }
                }
            }
            printf("\n");
        }
        
        
        printf("|vida %d|", vida_pers);
        // Capturar a tecla pressionada
        tecla = getch();
        // Lidar com o movimento do jogador
        int Ajx = jx;
        int Ajy = jy;

        switch (tecla) {
            case 'w':
            case 'W':
                Ajy--;
                break;
            case 's':
            case 'S':
                Ajy++;
                break;
            case 'a':
            case 'A':
                Ajx--;
                break;
            case 'd':
            case 'D':
                Ajx++;
                break;
            case 'q':
            case 'Q':
                exit(0);
                break;
            case 'i':
            case 'I':
                if (jx == chx && jy == chy && porta_char == '=') {
                    porta_char = '='; // Altera o porta_char para '=' quando o jogador interage com a chave
                } else if (jx == portalxx && jy == portalyy) {
                	jx = portalx;
                	 jy = portaly;
                } else if (jx == portalx && jy == portaly) {
                    jx = portalxx;
                    jy = portalyy;
                } else if (jx == chx && jy == chy) {
                    porta_char = '='; // Altera o porta_char para '=' quando o jogador estiver em cima da chave e pressionar 'i'
                } else if (jx == pfx && jy == pfy + 1 && porta_char == '=') {
                    terceiraFase(); // Chama a terceira fase quando o jogador estiver na posição correta e pressionar 'i'
                }
                break;
        }

        // Verificar se a nova posição está dentro dos limites do mapa
        if (Ajx > 0 && Ajx < MAPA_SIZE -1 && Ajy > 0 && Ajy < MAPA_SIZE -1) {
            jx = Ajx;
            jy = Ajy;
        }

        // Verificar se o jogador está na mesma posição que o botão
        if (jx == Bx && jy == By) {
            espinhosAtivados = 0; // Desativar os espinhos
        }
        
        // Verificar colisão com os espinhos
        if (espinhosAtivados && ((jx >= 10 && jx <= 20 && jy == 24) || (jx == 10 || jx == 20) && (jy <= 29 && jy > 24))) {
            vida_pers -= 40;
            if (vida_pers <= 0) {
                system("cls");
                printf("Você morreu!\n");
                exit(0);
            }
        }

        // Movimentar os goblins
        movimento_goblins();
        if (jx == pfx && jy == pfy && porta_char == '=') {
            terceiraFase(); // Chama a terceira fase quando o jogador alcança a porta na segunda fase
            break;
        }
        system("cls");
    }
}

void tutorial() {
    system("cls");
    printf("Comandos:\n\nW A S D - Movimento\nI - Interação com objetos do mapa\nQ - Quit\n\n ");
}

void jogar() {
    selecionar_personagem();
    clock_t start_time = clock();

    while (1) {
        fase(num_goblins);
        tecla = getch();
        botoes(tecla);
        movimento_goblins();
        if ((clock() - start_time) / CLOCKS_PER_SEC >= 5) {
            adicionar_goblin();
            start_time = clock();
        }

        if (primeiraFaseConcluida) {
            break; // Sai do loop quando a primeira fase for concluída
        }
    }

    // Se a primeira fase foi concluída, inicie a segunda fase
    if (primeiraFaseConcluida) {
        printf("Parabéns! Você concluiu a primeira fase!\n");
        printf("Pressione qualquer tecla para avançar para a segunda fase...\n");
        getch();
        segundaFase(); // Chama a função da segunda fase
    }
}

int main(void) {
    struct teste bb;
    printf("Digite o seu nome: ");
    scanf(" %[^\n]s", bb.nome);
    printf("Seja bem-vindo(a) ");
    puts(bb.nome);
    system("pause");

    setlocale(LC_ALL, "portuguese");
    srand(time(NULL));
    jx = 7;
    jy = 13;
    chx = 7;
    chy = 3;
    num_goblins = 15;
    goblins = (int **)malloc(num_goblins * sizeof(int *));
    for (i = 0; i < num_goblins; i++) {
        goblins[i] = (int *)malloc(2 * sizeof(int));
    }
    for (i = 0; i < num_goblins; i++) {
        goblins[i][0] = 0;
        goblins[i][1] = 0;
    }
    atq_goblin = 5;

    int escolha;
    do {
        system("cls");
        menu();
        scanf("%d", &escolha);
        switch (escolha) {
            case 1:
                jogar();
                break;
            case 2:
                tutorial();
                break;
            case 3:
                printf("Saindo...\n");
                loop = 0; // Definindo loop como 0 para sair completamente do jogo
                break;
            default:
                printf("Opção inválida. Por favor, escolha novamente.\n");
                break;
        }
        printf("\nPressione qualquer tecla para voltar ao menu.\n");
        getch();
    } while (loop); // Continuar enquanto loop for verdadeiro

    for (i = 0; i < num_goblins; i++) {
        free(goblins[i]);
    }
    free(goblins);

    return 0;
} 
