#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// Tamanho fixo de linha e coluna
#define TamL 10
#define TamC 20
typedef struct {
    int eMina;
    int vizinhos;
    int posAberta;
}Celula;


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



// não sei se é a função correta
void preencherVizinhos(Celula campo[TamL][TamC]){
    for(int l = 0; l < TamL; l++){
        for (int c = 0; c < TamC; c++)
            campo[l][c].vizinhos = quantMinasVizinhas(l, c, campo);

        
    }
}

void exibirCampoAtual(int l, int c, Celula campo[l][c]){
    printf("    0  | 1  | 2  | 3  | 4  | 5  | 6  | 7  | 8  | 9  | 10 | 11 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19\n");
    for(int i=0; i<l; i++){
        printf("  -----------------------------------------------------------------------------------------------------\n");
        printf("%d |", i);
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
    printf("  -----------------------------------------------------------------------------------------------------\n");
}



int main(){
    int l = 10, c = 20;
    Celula campo[l][c];
    
    int minas = 40;

    inicializarCampo(l, c, campo);
    gerarMinas(l, c, campo, minas);
    preencherVizinhos(campo);
    exibirCampoAtual(l, c, campo);
    return 0;
}