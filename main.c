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

    do{
        printf("\n\nEscolha o modo de jogo:\n");
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

                printf("\n1- Jogar Novamente: ");
                printf("\n2- Mostrar Ranking\n");
                printf("3- Trocar Modo\n");
                printf("4- Sair\n");
                printf("Opção: ");
                scanf("%d", &opcao);

            }while(opcao != 4 && opcao !=3);
            
        }
        if(modoJogo == 2){
        }

    }while(opcao != 4 && (opcao > 1 && opcao < 5));
           
    
    // gcc -o main main.c funcoes.c constantes.c
    return 0;
}