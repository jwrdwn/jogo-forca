#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#define TAMANHO_PALAVRA 20
#define N 49

#include "forca.h"

char palavra[TAMANHO_PALAVRA], chutes[26];
int chutesDados = 0;

int main() {

    escolhePalavra();

    do{

        desenhaForca();
        leChute();

    } while(!acertou() && !validaTentativas());

    exibeResultado();

    return 0;
}

void linha() {
    for(int i = 0; i < N; i++) {
        printf(":");
    }
    printf("\n");
}

void titulo(char titulo[]){
    int tamanhoTitulo = strlen(titulo) + 2;
    for(int t = 0; t < (N - tamanhoTitulo) / 2; t++)
        printf("-");
        if(tamanhoTitulo % 2 == 0){
            printf("- %s ", titulo);
        } else{
            printf(" %s ", titulo);
        }
    for(int t = 0; t < (N - tamanhoTitulo) / 2; t++){
        printf("-");
    } printf("\n");
}

void abertura() {
    system("clear");
    linha();
    titulo("Jogo da Forca");
    linha();
}

void inserirPalavra() {
    char respostaAdicionaPalavra;

    linha();
    printf("Você deseja adicionar uma nova palavra ao jogo? (s/n) ");
    scanf(" %c", &respostaAdicionaPalavra);

    if(respostaAdicionaPalavra == 's') {
        
        FILE *f;
        f = fopen("palavras.txt", "r+");
        erro(f);
        
        char novaPalavra[TAMANHO_PALAVRA];

        linha();
        titulo("! ATENÇÃO !");
        titulo("Digite apenas palavras SEM acentos ");
        titulo("e escreva tudo em letras minuculas ");
        linha();
        printf("\nDigite a palavra que deseja inserir: ");
            scanf("%s", &novaPalavra);

        int quantidadeDePalavras;
        fscanf(f, "%d", &quantidadeDePalavras);
        quantidadeDePalavras++;

        fseek(f, 0, SEEK_SET);
        fprintf(f, "%d", quantidadeDePalavras);

        fseek(f, 0, SEEK_END);
        fprintf(f, "\n%s", novaPalavra);

        fclose(f);
    }
}

void escolhePalavra() {
    FILE *f;
    f = fopen("palavras.txt", "r");

    erro(f);
    
    int quantidadeDePalavras;
    fscanf(f, "%d", &quantidadeDePalavras);

    srand(time(0));
    int numeroAleatorio = rand() % quantidadeDePalavras;

    for(int i = 0; i <= numeroAleatorio; i++) {
        fscanf(f, "%s", palavra);
    }

    fclose(f);
}

void leChute() {
    char chute;
    scanf(" %c", &chute);

    chutes[chutesDados] = chute;
    chutesDados++;
}

int testaChute(char letra) {
    int achou = 0;

    for(int j = 0; j < chutesDados; j++) {
        if(chutes[j] == letra) {
            achou = 1;
            break;
        }

    }
    return achou;
}

void desenhaBoneco() {
    
    int erros = chutesErrados();

    abertura();

    printf("  _______                     \n");
    printf(" | /    |                     \n");
    printf(" |/    %c%c%c  \n", (erros >= 1 ? '(' : ' '),
                                (erros >= 1 ? '_' : ' '),
                                (erros >= 1 ? ')' : ' '));

    printf(" |     %c%c%c \n", (erros >= 3 ? '\\' : ' '),
                                (erros >= 2 ? '|' : ' '),
                                (erros >= 3 ? '/' : ' '));

    printf(" |      %c               \n", (erros >= 2 ? '|' : ' '));

    printf(" |     %c %c       \n", (erros >= 4 ? '/' : ' '),
                                    (erros >= 4 ? '\\' : ' '));

    printf(" |                            \n");
    printf("_|___                         \n");
    printf("\n\n");
}

void desenhaForca() {
    
    system("clear");
    desenhaBoneco();
    
    for(int i = 0; i <= strlen(palavra); i++) {

        int achou = testaChute(palavra[i]);
        
        if(achou) {
            printf("%c ", toupper(palavra[i]));
        } else {
            printf("_ ");
        }
    }
    printf("\n");
}

int acertou() {
    for(int i = 0; i < strlen(palavra); i++) {
        if(!testaChute(palavra[i])) {
            return 0;
        }
    }
    return 1;
}

int chutesErrados() {
    int erros = 0;
    for(int i = 0; i < chutesDados; i++) {
        int existe = 0;
        for(int j = 0; j < strlen(palavra); j++) {
            if(chutes[i] == palavra[j]) {
                existe = 1;
                break;
            }
        }
        if(!existe) {
            erros++;
        }
    }
    return erros;
}

int validaTentativas() {
    return chutesErrados() >= 5;
}

void erro(FILE *f) {
    if(f == 0) {
        printf("\nDesculpe, o banco de palavras está indisponível... :(\n\n");
        exit(1);
    }
}

void exibeResultado() {
    system("clear");
    if(acertou()) {
        linha();
        titulo("Parabéns, você ganhou!!!");
        linha();
        printf("       __________      \n");
        printf("     .-\\:       /-.    \n");
        printf("     |(|:.      |)|    \n");
        printf("     '-|:.      |-'     \n");
        printf("        \\::.    /      \n");
        printf("         '::. .'        \n");
        printf("           ) (          \n");
        printf("         .'   '.        \n");
        printf("        '-------'       \n\n");
    } else {
        linha();
        titulo("Você foi enforcado!!!");
        titulo("A palavra era: ");
        linha();
        titulo(palavra);
        linha();
        printf("   _________________         \n");
        printf("  /                 \\       \n"); 
        printf(" /                   \\     \n");
        printf(" |   XXXX     XXXX   |      \n");
        printf(" /  XXXXX     XXXXX  \\      \n");
        printf(" \\   XXX       XXX   /      \n");
        printf(" |         X         |      \n");
        printf(" \\__      XXX      __/     \n");
        printf("    \\     X X     /       \n");
        printf("     |           |         \n");
        printf("     \\_I_I_I_I_I_/         \n");
    }
}
