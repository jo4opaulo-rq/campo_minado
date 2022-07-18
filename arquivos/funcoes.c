#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "constantes.h"

#include "estruturas.h"

void inicializarCampo(int l, int c, Celula campo[l][c]){
    for(int i=0; i<l; i++){
        for(int j=0; j<c; j++){
            campo[i][j].eMina = 0;
            campo[i][j].vizinhos= 0;
            campo[i][j].posAberta = 0;
        }
    }
}

void gerarMinas(int l, int c, Celula campo[l][c], int minas){
    srand(time(NULL));
    int vetL;
    int vetC;

    for(int i=0; i<minas; i++){
        vetL = rand() % 10; 
        vetC = rand() % 20; 
        if(campo[vetL][vetC].eMina == 0)
            campo[vetL][vetC].eMina = 1;
        else
            i--;
    }
}
// Verificar se a coordena é válida ou não
int coordenaValida(int l, int c){
    if(l >= 0 && l < TamL && c >= 0 && c < TamC){
        return 1;
    }
    else{
        return 0;
    }
}
int quantMinasVizinhas(int l, int c, Celula campo[l][c]){
    int quantMina = 0;
    if(coordenaValida(l - 1, c) && campo[l-1][c].eMina){
        quantMina ++;
    }
    if(coordenaValida(l + 1, c) && campo[l+1][c].eMina){
        quantMina ++;
    }
    if(coordenaValida(l, c + 1) && campo[l][c+1].eMina){
        quantMina ++;
    }
    if(coordenaValida(l, c - 1) && campo[l][c-1].eMina){
        quantMina ++;
    }
    return quantMina;
}

void preencherVizinhos(Celula campo[TamL][TamC]){
    for(int l = 0; l < TamL; l++){
        for (int c = 0; c < TamC; c++)
            campo[l][c].vizinhos = quantMinasVizinhas(l, c, campo);

        
    }
}

void abrirCoordenada(int l, int c, Celula campo[TamL][TamC]){
    if(coordenaValida(l, c) == 1 && campo[l][c].posAberta == 0){
        campo[l][c].posAberta = 1;
        if(campo[l][c].vizinhos == 0){
            abrirCoordenada(l-1, c, campo);
            abrirCoordenada(l+1, c, campo);
            abrirCoordenada(l, c-1, campo);
            abrirCoordenada(l, c+1, campo);
        }
    }
}   


void jogar(Celula campo[TamL][TamC]){
    int linha, coluna;

    do{
        printf("\nDigite o número da linha e da coluna: ");
        scanf("%d %d", &linha, &coluna);
        
        if(coordenaValida(linha, coluna) == 0){
            printf("\nCoordenada inválida");
        }
    }while(coordenaValida(linha, coluna) == 0 || campo[linha][coluna].posAberta == 1);

    abrirCoordenada(linha, coluna, campo);
        
}

void exibirCampoAtual(int l, int c, Celula campo[l][c]){
    printf("\n\n\t  |");
    for(int i=0; i<c; i++)
        if(i < 10)
            printf(" %d  |", i);
        else    
            printf(" %d |", i);
    printf("\n");

    for(int i=0; i<l; i++){
        printf("\t-------------------------------------------------------------------------------------------------------\n");
        printf("\t%d |", i);
        for(int j=0; j<c; j++){ 
            if(campo[i][j].posAberta){
                if(campo[i][j].eMina)
                    printf(" *  |");
                else   
                    printf(" %d  |", campo[i][j].vizinhos); 

            }
            else{
                printf("    |");
            }
        }
        printf("\n");
    }

    printf("\t-------------------------------------------------------------------------------------------------------\n");
}