#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "constantes.h"

#include "estruturas.h"
// Inicializa todas as estruturas do como com o valor 0
void inicializarCampo(Celula campo[TamL][TamC])
{
    for (int i = 0; i < TamL; i++)
    {
        for (int j = 0; j < TamC; j++)
        {
            campo[i][j].eMina = 0;
            campo[i][j].vizinhos = 0;
            campo[i][j].posAberta = 0;
        }
    }
}

void gerarMinas(Celula campo[TamL][TamC])
{
    srand(time(NULL));
    int linha;
    int coluna;

    for (int i = 0; i < minas; i++)
    {
        linha = rand() % 10;
        coluna = rand() % 20;
        if (campo[linha][coluna].eMina == 0)
        {
            campo[linha][coluna].eMina = 1;
        }
        else
            i--;
    }
}
// Verificar se a coordena é válida ou não
int coordenaValida(int l, int c)
{
    if (l >= 0 && l < TamL && c >= 0 && c < TamC)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int quantMinasVizinhas(int l, int c, Celula campo[TamL][TamC])
{
    int quantMina = 0;
    if (coordenaValida(l - 1, c) && campo[l - 1][c].eMina)
    { // vertical
        quantMina++;
    }
    if (coordenaValida(l + 1, c) && campo[l + 1][c].eMina)
    { // vertical
        quantMina++;
    }
    if (coordenaValida(l, c + 1) && campo[l][c + 1].eMina)
    { // horizontal
        quantMina++;
    }
    if (coordenaValida(l, c - 1) && campo[l][c - 1].eMina)
    { // horizontal
        quantMina++;
    }
    if (coordenaValida(l - 1, c - 1) && campo[l - 1][c - 1].eMina)
    { // Diagonal
        quantMina++;
    }
    if (coordenaValida(l - 1, c + 1) && campo[l - 1][c + 1].eMina)
    { // Diagonal
        quantMina++;
    }
    if (coordenaValida(l + 1, c - 1) && campo[l + 1][c - 1].eMina)
    { // Diagonal
        quantMina++;
    }
    if (coordenaValida(l + 1, c + 1) && campo[l + 1][c + 1].eMina)
    { // Diagonal
        quantMina++;
    }
    return quantMina;
}

// não sei se é a função correta
void preencherVizinhos(Celula campo[TamL][TamC])
{
    for (int l = 0; l < TamL; l++)
    {
        for (int c = 0; c < TamC; c++)
        {
            campo[l][c].vizinhos = quantMinasVizinhas(l, c, campo);
        }
    }
}

void abrirCoordenada(int l, int c, Celula campo[TamL][TamC])
{
    if (coordenaValida(l, c) == 1 && campo[l][c].posAberta == 0)
    {
        campo[l][c].posAberta = 1;
        if (campo[l][c].vizinhos == 0)
        {
            abrirCoordenada(l - 1, c, campo);
            abrirCoordenada(l + 1, c, campo);
            abrirCoordenada(l, c - 1, campo);
            abrirCoordenada(l, c + 1, campo);
        }
    }
}

int verificaVitoria(Celula campo[TamC][TamL])
{
    int n = 0;

    for (int i = 0; i < TamC; i++)
    {
        for (int j = 0; j < TamC; j++)
        {
            if (campo[i][j].posAberta == 0 && campo[i][j].eMina == 0)
                n++;
        }
    }
    return n;
}

void exibirCampoAtual(Celula campo[TamL][TamC])
{
    printf("\n\n\t   ");
    for (int i = 0; i < TamC; i++)
        if (i < 10)
            printf(" %d  |", i);
        else if (i < 19)
            printf(" %d |", i);
        else
            printf(" %d ", i);
    printf("\n");
    for (int i = 0; i < TamL; i++)
    {
        printf("\t  -----------------------------------------------------------------------------------------------------\n");
        printf("\t%d |", i);
        for (int j = 0; j < TamC; j++)
        {
            if (campo[i][j].posAberta)
            {
                if (campo[i][j].eMina)
                    printf(" \U0001f4a3  |");
                else
                    printf(" %d  |", campo[i][j].vizinhos);
            }
            else
            {
                printf("    |");
            }
        }
        printf("\n");
    }
    printf("\t  -----------------------------------------------------------------------------------------------------\n");
}

 void registro(long *tempo){
    FILE *arquivo;
    char nome[50];
    char org2[255] = "           ";
    char org[255] = "|        ";
    
   printf("\nDigite seu primeiro nome: ");
   scanf("%s", nome);

    arquivo = fopen("registro.txt", "a");
    fprintf(arquivo, "\n");
    fprintf(arquivo, "%s", org);
    fprintf(arquivo, "%s", nome);
    fprintf(arquivo, "%s", org2);
    fprintf(arquivo, "%s", org);
    
    fprintf(arquivo, "%ld", *tempo);
    fprintf(arquivo, "%s", "seg");
    fprintf(arquivo, "%s", org2);
    fprintf(arquivo, "%s", org);
    
    
    fclose(arquivo);
}
char imprimir_registro(){
    FILE *arquivo;
    char texto_arquivo[255];
    arquivo = fopen("registro.txt", "r");

    while (fgets(texto_arquivo, 255, arquivo) != NULL);
    printf("%s", texto_arquivo);
    printf("\n");
    fclose(arquivo);
    
}

void ajudar(Celula campo[TamL][TamC])
{
    int *vet;
    vet = malloc(2 * sizeof(int));

    int linha;
    int coluna;
    srand(time(NULL));
    linha = rand() % 10;
    coluna = rand() % 20;

    if (campo[linha][coluna].posAberta == 0 && campo[linha][coluna].vizinhos < 2)
    {
        vet[0] = linha;
        vet[1] = coluna;
        printf("Digite a coordenada [%d-%d]", vet[0], vet[1]);
    }
    else
        ajudar(campo);

    free(vet);
}

void modoAutonomo(Celula campo[TamL][TamC])
{
    int linha;
    int coluna;
    srand(time(NULL));

    do
    {
        exibirCampoAtual(campo);
        printf("\n\n\t---BOT PENSANDO...\n\n");
        sleep(3);
        linha = rand() % 10;
        coluna = rand() % 20;

        if(campo[linha][coluna].posAberta == 0 && campo[linha][coluna].vizinhos < 8){
            abrirCoordenada(linha, coluna, campo);
        }
        else
            modoAutonomo(campo);

    }while(verificaVitoria(campo) != 0 && campo[linha][coluna].eMina == 0);

    if (campo[linha][coluna].eMina == 1)
    {
        exibirCampoAtual(campo);
        printf("\n\n\t------O BOT PERDEU!\n\n------");
    }
    else
    {
        exibirCampoAtual(campo);
        printf("\n\n\t------O BOT GANHOU!------\n");    
        //scanf("%s", nome);
        //registro(50, nome);
    }
}

void jogar(Celula campo[TamL][TamC], time_t *inicio, time_t *meio, time_t *fim)
{
    int linha, coluna, escolha = 1, i = 0;
    time_t total;

    do
    {
        exibirCampoAtual(campo);
        do
        {
            printf("\nEscolha o que deseja fazer: \n");
            printf("1- Revelar uma célula\n");
            printf("2- Pedir ajuda\n");
            printf("3- Mostrar tempo decorrido\n");
            printf("\nOpção: ");
            scanf("%d", &escolha);
            if (escolha > 3 || escolha < 1)
            {
                printf("\n------Opção Inválida!------\n");
                printf("  ---Digite novamente!---\n");
            }
        } while (escolha != 1 && escolha != 2 && escolha != 3);

        if (escolha == 1)
        {
            do
            {
                printf("\nDigite o número da linha e da coluna: ");
                scanf("%d %d", &linha, &coluna);

                if (coordenaValida(linha, coluna) == 0)
                {
                    printf("\nCoordenada inválida!\n");
                }
                if (campo[linha][coluna].posAberta == 1)
                {
                    printf("\nCoordenada Já foi aberta!\n");
                }
            } while (coordenaValida(linha, coluna) == 0 || campo[linha][coluna].posAberta == 1);
        }
        if (i < 1)
        {
            *inicio = time(NULL);
            i++;
        }
        if (escolha == 2)
        {
            ajudar(campo);
        }

        if (escolha == 3)
        {
            *meio = time(NULL);
            printf("Tempo: %ld Segundos\n", (*meio - *inicio));
        }
        abrirCoordenada(linha, coluna, campo);
    } while (verificaVitoria(campo) != 0 && campo[linha][coluna].eMina == 0);

    *fim = time(NULL);
    total = fim - inicio;

    if (campo[linha][coluna].eMina == 1)
    {
        exibirCampoAtual(campo);
        printf("\n\n\tPERDEU!\n");
        
        registro(&total); // remover depois, para teste
    }
    else
    {
        exibirCampoAtual(campo);
        printf("\n\n\tGANHOU!\n");
        printf("\nDigite seu primeiro nome: ");
        //scanf("%s", nome);
        //registro(50, nome);
    }
    printf("Tempo Total: %ld", total);
}
