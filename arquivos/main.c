#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "constantes.h"

#include "funcoes.h"

#include "estruturas.h"

int main(){
    Celula campo[10][20];
    
    int minas = 40;
    int modoJogo;
    int opcao;

    printf("Escolha o modo de jogo:\n");
    printf("1- Modo clássico\n");
    printf("2- Modo autônomo\n");
    printf("Modo: ");
    scanf("%d", &modoJogo);
    if(modoJogo == 1){
        printf("\nDigite 1 para jogar: ");
        printf("\nDigite 2 para pedir ajuda:\n");
        scanf("%d", &opcao);
        while(opcao == 1){
            inicializarCampo(TamL, TamC, campo);
            gerarMinas(TamL, TamC, campo, minas);
            preencherVizinhos(campo);
            jogar(campo);

            printf("\nDigite 1 para jogar novamente: ");
            printf("\nDigite 2 para pedir ajuda: \n");
            scanf("%d", &opcao);
        }
    }
    
        

       

    return 0;
}