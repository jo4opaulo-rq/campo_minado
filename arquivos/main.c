#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "constantes.h"

#include "funcoes.h"

#include "estruturas.h"

int main(){
    Celula campo[10][20];
    
    int minas = 40;

    inicializarCampo(TamL, TamC, campo);
    gerarMinas(TamL, TamC, campo, minas);
    preencherVizinhos(campo);
    exibirCampoAtual(TamL, TamC, campo);
    jogar(campo);
    return 0;
}