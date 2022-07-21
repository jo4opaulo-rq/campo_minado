#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "constantes.h"

#include "funcoes.h"

#include "estruturas.h"

int main(){
    Celula campo[10][20];
    
    int modoJogo;
    int opcao;

    printf("Escolha o modo de jogo:\n");
    printf("1- Modo clássico\n");
    printf("2- Modo autônomo\n");
    printf("Modo: ");
    scanf("%d", &modoJogo);
    if(modoJogo == 1){
        do{
            inicializarCampo(campo);
            gerarMinas(campo);
            preencherVizinhos(campo);
            jogar(campo);

            printf("\nDigite 1 para jogar novamente: ");
            printf("\nDigite 2 para pedir ajuda: \n");
            printf("\nDigite 2 para pedir ajuda: \n");
            scanf("%d", &opcao);
        }while(opcao == 1);
          
    }
           
    
    // gcc -o main main.c funcoes.c constantes.c
    return 0;
}