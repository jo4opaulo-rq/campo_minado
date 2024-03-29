#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "constantes.h"

#include "funcoes.h"

#include "estruturas.h"

int main()
{
    Celula campo[10][20];
    time_t inicio;
    time_t meio;
    time_t fim;

    char nome[50];
    int modoJogo;
    int opcao;
    float total;

    do
    {
        printf("\n\nEscolha o modo de jogo:\n");
        printf("1- Modo clássico\n");
        printf("2- Modo autônomo\n");
        printf("\nModo: ");
        scanf("%d", &modoJogo);
        if (modoJogo == 1)
        {
            do
            {
                inicializarCampo(campo);
                gerarMinas(campo);
                preencherVizinhos(campo);
                jogar(campo, &inicio, &meio, &fim, total);
                
                do
                {
                    printf("\n1- Jogar Novamente: ");
                    printf("\n2- Mostrar Tempos\n");
                    printf("3- Trocar Modo\n");
                    printf("4- Sair\n");
                    printf("\nOpção: ");
                    scanf("%d", &opcao);
                    if (opcao == 2)
                    {
                        printf("\nSeus tempo:\n");
                        imprimir_registro();
                    }
                    if (opcao == 4)
                    {
                        printf("\n\t\t------Obrigado por jogar------\n\n");
                    }
                } while (opcao == 2);
            } while (opcao != 4 && opcao != 3);
        }
        if (modoJogo == 2)
        {
            inicializarCampo(campo);
            gerarMinas(campo);
            preencherVizinhos(campo);
            modoAutonomo(campo);
        }

    } while (opcao != 4 && (opcao > 1 && opcao < 5) );

    // gcc -o main main.c funcoes.c constantes.c
    return 0;
}