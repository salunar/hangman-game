#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include "forca.h"

char palavrasecreta[tamanho_palavra];
char chutes[tamanho_chute];
int chutesdados = 0;

void abertura() {
     printf("*******************************\n");
     printf("***        F O R C A        ***\n");
     printf("*******************************\n\n");
}

void chuta (int* tent){
    char chute;
    scanf(" %c", &chute);

    chutes[(*tent)] = chute;
    (*tent)++;
}

int jachutou(char letra){
    int achou = 0;

    for(int j = 0; j < chutesdados; j++){
        if(chutes[j] == letra){
            achou = 1;
            break;
        }
    }
    return achou;
}

void desenhaforca(){

    int erros = chuteserrados();
        printf("_________     \n");
        printf(" |/     |     \n");
        printf(" |     %c%c%c    \n", (erros >= 1 ? '(' : ' '),
               (erros >=1 ? '_' : ' '), (erros >= 1 ? ')' : ' '));
        printf(" |    %c%c%c%c%c   \n", (erros >= 3 ? '-' : ' '), (erros >= 3 ? '-' : ' '),
               (erros >= 2 ? '|' : ' '), (erros >= 4 ? '-' : ' '), (erros >= 4 ? '-' : ' '));
        printf(" |      %c     \n", (erros >= 2 ? '|' : ' '));
        printf(" |     %c %c%c    \n", (erros >= 5 ? '/' : ' '), (erros >= 6 ? '\\' : ' '));
        printf(" |            \n");
        printf("_|__          \n");
        printf("\n\n");

    for(int i = 0; i < strlen(palavrasecreta); i++){

        int achou = jachutou(palavrasecreta[i]);
        if(achou){
            printf("%c ", palavrasecreta[i]);
        }
        else{
            printf("_ ");
        }
    }
    printf("\n");
}

void escolhepalavra(){
    FILE* f;

    f = fopen("palavras.txt", "r");

    if(f == 0){
        printf("Desculpe, banco de dados indisponivel");
        exit(1);
    }

    int qtddepalavras;
    fscanf(f, "%d", &qtddepalavras);

    srand(time(0));
    int randomico = rand() % qtddepalavras;

    for(int i = 0; i <= randomico; i++){
        fscanf(f, "%s" , palavrasecreta);
    }
    fclose(f);
}

int acertou(){
    for(int i = 0; i < strlen(palavrasecreta); i++){
        if(!jachutou(palavrasecreta[i])){
            return 0;
        }
    }
    return 1;
}

int chuteserrados(){
    int erros = 0;

    for(int i = 0; i < chutesdados; i++){
        int existe = 0;

        for(int j = 0; j < strlen(palavrasecreta); j++){
            if(chutes[i] == palavrasecreta[j]){
                existe = 1;
                break;
            }
        }
        if(!existe) erros++;
    }
    return erros;
}

int enforcou(){

    return chuteserrados() >= 6;
}

void adicionapalavra(){
    char quer;

    printf("Voc� deja aicionar uma nova palavra ao jogo? (S/N)");
    scanf(" %c", &quer);

    if(quer == 'S' || quer == 's'){
        char novapalavra[30];
        printf("Qual a nova palavra?\n");
        scanf("%s", &novapalavra);

        FILE* f;

        f = fopen("palavras.txt", "r+");

        if(f == 0){
        printf("Desculpe, banco de dados indisponivel");
        exit(1);
        }

        int quantidade;
        fscanf(f,"%d", &quantidade);
        quantidade++;

        fseek(f, 0, SEEK_SET);
        fprintf(f,"%d", quantidade);

        fseek(f, 0, SEEK_END);
        fprintf(f,"\n%s", &novapalavra);

        fclose(f);
    }
    else{
        exit(1);
    }
}

int main() {
    setlocale(LC_ALL, "");

    escolhepalavra(palavrasecreta);
    abertura();

    do{
        desenhaforca(palavrasecreta, chutes, chutesdados);
        chuta(&chutesdados);

    }while(!acertou()  && !enforcou());

    if(acertou()){
         printf("********* PARAB�NS VOC� GANHOU! *********\n\n");
         printf("             .-=========-. \n");
         printf("             \\'-=======-'/ \n");
         printf("             _|   .=.   |_ \n");
         printf("            ((|  {{1}}  |))\n");
         printf("             \\|   /|\\   |/ \n");
         printf("              \\__ '`' __/  \n");
         printf("                _`) (`_    \n");
         printf("              _/_______\\_  \n");
         printf("             /___________\\ \n\n\n");
    }
    else{
        printf("=====================\n");
        printf("     VOC� PERDEU!\n");
        printf("=====================\n\n");
        printf("A palavra correta era %s\n\n" ,palavrasecreta);
    }
    adicionapalavra();
}
