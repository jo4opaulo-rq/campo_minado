#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "constantes.h"

#include "estruturas.h"
//Inicializa todas as estruturas do como com o valor 0
void inicializarCampo(Celula campo[TamL][TamC]){
    for(int i=0; i<TamL; i++){
        for(int j=0; j<TamC; j++){
            campo[i][j].eMina = 0;
            campo[i][j].vizinhos= 0;
            campo[i][j].posAberta = 0;
        }
    }
}
// Adiciona as minas ao campo
void gerarMinas(Celula campo[TamC][TamL]){
    srand(time(NULL));
    int linha;
    int coluna;

    for(int i=0; i<minas; i++){
        linha = rand() % 10; 
        coluna = rand() % 20; 
        if(campo[linha][coluna].eMina == 0)
            campo[linha][coluna].eMina = 1;
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
int quantMinasVizinhas(int l, int c, Celula campo[TamC][TamL]){
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

int verificaVitoria(Celula campo[TamC][TamL]){
    int n=0;

    for(int i=0; i<TamC; i++){
        for(int j=0; j<TamC; j++){
            if(campo[i][j].posAberta == 0 && campo[i][j].eMina == 0)
                n++;
        }
    }
    return n;
}

void exibirCampoAtual(int l, int c, Celula campo[l][c]){
    printf("\n\n\t   ");
    for(int i=0; i<c; i++)
        if(i < 10)
            printf(" %d  |", i);
        else if(i<19)   
            printf(" %d |", i);
        else        
            printf(" %d ", i);
    printf("\n");

    for(int i=0; i<l; i++){
        printf("\t  -----------------------------------------------------------------------------------------------------\n");
        printf("\t%d |", i);
        for(int j=0; j<c; j++){ 
            if(campo[i][j].posAberta){
                if(campo[i][j].eMina)
                    printf(" *  |");
                else if(campo[i][j].vizinhos)
                    printf(" %d  |", campo[i][j].vizinhos); 

            }
            else{
                printf("    |");
            }
        }
        printf("\n");
    }

    printf("\t  -----------------------------------------------------------------------------------------------------\n");
}

void jogar(Celula campo[TamL][TamC]){
    int linha, coluna;
    do{
        exibirCampoAtual(TamL, TamC, campo);
        do{
            printf("\nDigite o número da linha e da coluna: ");
            scanf("%d %d", &linha, &coluna);
            
            if(coordenaValida(linha, coluna) == 0){
                printf("\nCoordenada inválida\n");
            }
        }while(coordenaValida(linha, coluna) == 0 || campo[linha][coluna].posAberta == 1);

        abrirCoordenada(linha, coluna, campo);
    }while(verificaVitoria(campo) != 0 && campo[linha][coluna].eMina == 0);

    if(campo[linha][coluna].eMina == 1){
        exibirCampoAtual(TamL, TamC, campo);
        printf("\n\n\tRIPASTES!\n");
    }
    else{
        exibirCampoAtual(TamL, TamC, campo);
        printf("\n\n\tGANHASTES!\n");
    }
}