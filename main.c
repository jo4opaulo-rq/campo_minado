#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "constantes.h"

#include "funcoes.h"

#include "estruturas.h"

int main(){
    Celula campo[10][20];
    time_t inicio;
    time_t meio;
    time_t fim;
    time_t total;
    
    int modoJogo;
    int opcao;
    

    do{
        printf("\n\nEscolha o modo de jogo:\n");
        printf("1- Modo clássico\n");
        printf("2- Modo autônomo\n");
        printf("\nModo: ");
        scanf("%d", &modoJogo);
        if(modoJogo == 1){
            do{
                inicializarCampo(campo);
                gerarMinas(campo);
                preencherVizinhos(campo);
                jogar(campo, &inicio, &meio, &fim);

                do{
                    printf("\n1- Jogar Novamente: ");
                    printf("\n2- Mostrar Tempos\n");
                    printf("3- Trocar Modo\n");
                    printf("4- Sair\n");
                    printf("\nOpção: ");
                    scanf("%d", &opcao);
                    if(opcao == 2){
                        printf("\nSeus tempo:\n");
                        printf("Under construction\n");
                    }
                    if(opcao == 4){
                        printf("\nObrigado por jogar\n");
                    }
                }while(opcao == 2);
            }while(opcao != 4 && opcao != 3);
            
        }
        if(modoJogo == 2){
        }

    }while(opcao != 4 && (opcao > 1 && opcao < 5));
           
    
    // gcc -o main main.c funcoes.c constantes.c
    return 0;
}