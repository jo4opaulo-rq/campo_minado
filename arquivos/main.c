#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "constantes.h"

#include "funcoes.h"

#include "estruturas.h"

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