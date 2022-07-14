#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int eMina;
    int vizinhos;
    int posVazia;
}Celula;


void inicializarCampo(int l, int c, int campo[10][20].eMina){
    for(int i=0; i<l; i++){
        for(int j=0; j<c; j++){
            campo[i][j].eMina = 0;
            campo[i][j].vizinhos = 0;
            campo[i][j].posVazia = 0;
        }
    }
}

void gerarMinas(){
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

void preencherVizinhos(){
    
}

void exibirCampoAtual(){
    printf("    0  | 1  | 2  | 3  | 4  | 5  | 6  | 7  | 8  | 9  | 10 | 11 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19\n");
    for(int i=0; i<l; i++){
        printf("  -----------------------------------------------------------------------------------------------------\n");
        printf("%d |", i);
        for(int j=0; j<c; j++){
            printf("  %d|", campo[i][j].eMina);
        }
        printf("\n");
    }
    printf("  -----------------------------------------------------------------------------------------------------\n");
}



int main(){
    Celula campo[10][20];
    int l = 10, c = 20;
    int minas = 40;

    inicializarCampo(l, c, campo[l][c].eMina);
    gerarMinas();
    exibirCampoAtual();
    
    return 0;
}