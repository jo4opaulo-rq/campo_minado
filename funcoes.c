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
// Gera aleatoriamente as minas do campo
void gerarMinas(Celula campo[TamL][TamC])
{
    srand(time(NULL)); // Inicializa o gerador de números aleatórios com o valor da função time(NULL)
    int linha;
    int coluna;

    for (int i = 0; i < minas; i++)
    {
        linha = rand() % 10;
        coluna = rand() % 20;
        if (campo[linha][coluna].eMina == 0) // Verifica se a coordenada já possui uma mina
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
// Conta a quantidade minas vizinhas de forma recursiva
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

// Faz o preenchimento do campo vizinhos de acordo com a quantidades de minas ao redor
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
    if (coordenaValida(l, c) == 1 && campo[l][c].posAberta == 0) //
    {
        campo[l][c].posAberta = 1;
        if (campo[l][c].vizinhos == 0)
        {
            abrirCoordenada(l - 1, c, campo); //Vertical
            abrirCoordenada(l + 1, c, campo); //Vertical
            abrirCoordenada(l, c - 1, campo); //Horizontal
            abrirCoordenada(l, c + 1, campo); //Horizontal
            abrirCoordenada(l - 1, c - 1, campo); //Diagonal
            abrirCoordenada(l - 1, c + 1, campo); //Diagonal
            abrirCoordenada(l + 1, c - 1, campo); //Diagonal 
            abrirCoordenada(l + 1, c + 1, campo); //Diagonal
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
    for (int i = 0; i < TamC; i++) // Imprime a quantidade colunas
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
        printf("\t%d |", i); // Imprime a quantidade de linhas, indo de 0 a 19
        for (int j = 0; j < TamC; j++)
        {
            if (campo[i][j].posAberta) // Imprime a mina ou um vizinho apenas se a posição estiver revelada
            {
                if (campo[i][j].eMina)
                    printf(" \U0001f4a3 |"); // Figurinha da bomba
                else
                    printf(" %d  |", campo[i][j].vizinhos);
            }
            else
            {
                printf("    |"); // imprime apenas espaços caso a posição esteja fechada
            }
        }
        printf("\n");
    }
    printf("\t  -----------------------------------------------------------------------------------------------------\n");
}

void ajudar(Celula campo[TamL][TamC])
{
    int *vet; //Cria um ponteiros
    vet = malloc(6 * sizeof(int)); 

    int linha;
    int coluna;
    srand(time(NULL));
    linha = rand() % 10;
    coluna = rand() % 20;

    if (campo[linha][coluna].posAberta == 0 && campo[linha][coluna].vizinhos < 2) 
    {
        vet[0] = linha;
        vet[1] = coluna;
        printf("\n\t---Digite a coordenada [%d-%d]---\n", vet[0], vet[1]);
    }
    else
        ajudar(campo);

    free(vet);
}

void modoAutonomo(Celula campo[TamL][TamC])
{
    int linha;
    int coluna;
    int i=0;
    srand(time(NULL));
    
    do
    {
        exibirCampoAtual(campo);
        printf("\n\n\t---BOT PENSANDO...\n\n");
        sleep(3);
        linha = rand() % 10;
        coluna = rand() % 20;

        abrirCoordenada(linha, coluna, campo);
        
    } while (verificaVitoria(campo) != 0 && campo[linha][coluna].eMina == 0);

    if (campo[linha][coluna].eMina == 1)
    {
        exibirCampoAtual(campo);
        printf("\n\n\t------O BOT PERDEU!\n\n------");
    }
    else
    {
        exibirCampoAtual(campo);
        printf("\n\n\t------O BOT GANHOU!------\n");
    }
}

void registro(double total)
{
    FILE *arquivo;
    char nome[50];
    char barra[3] = "\0";
    char espaco[255] = "                ";
    char espaco2[255] = "            ";

    printf("\nDigite seu primeiro nome: ");
    scanf("%s", nome);

    arquivo = fopen("registro.txt", "a");
    fprintf(arquivo, "\n");

    fprintf(arquivo, "%s", espaco);

    fprintf(arquivo, "%s", nome);
    fprintf(arquivo, "%s", espaco);
    fprintf(arquivo, "%s", espaco2);

    fprintf(arquivo, "%.0f", total);
    fprintf(arquivo, "%s", "s");

    fclose(arquivo);
}

char imprimir_registro()
{
    FILE *arquivo;
    char texto_arquivo[255];
    char texto;
    arquivo = fopen("registro.txt", "r");

    do
    {

        texto = fgetc(arquivo);

        printf("%c", texto);
    } while (texto != EOF); 
    printf("\n");
}

void jogar(Celula campo[TamL][TamC], time_t *inicio, time_t *meio, time_t *fim, float total)
{
    int linha, coluna, escolha = 1, i = 0;

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
            if (escolha == 2)
            {
                ajudar(campo);

            }

            if (escolha == 3)
            {
                if (i < 1)
                {
                    printf("\n---O tempo só inicia depois da primeira jogada!---\n");
                }
                else
                {
                    *meio = time(NULL);
                    printf("\n\t---Tempo: %ld Segundos---\n", (*meio - *inicio));
                }
            }
        } while ((escolha != 1 && escolha != 2 && escolha != 3) || escolha == 2 || escolha == 3);

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
            } while (coordenaValida(linha, coluna) == 0 && campo[linha][coluna].posAberta == 1);
        }
        if (i < 1)
        {
            *inicio = time(NULL);
            i++;
        }
        abrirCoordenada(linha, coluna, campo);
    } while (verificaVitoria(campo) != 0 && campo[linha][coluna].eMina == 0);

    *fim = time(NULL);

    total = difftime(*fim, *inicio);

    if (campo[linha][coluna].eMina == 1)
    {
        exibirCampoAtual(campo);
        printf("\n\n\t     ------PERDEU!------\n");
        printf("\n\t---Tempo Total: %.0f Segundos---\n", total);
    }
    else
    {
        exibirCampoAtual(campo);
        printf("\n\n\tGANHOU!\n");
        printf("\n\t---Tempo Total: %.0f Segundos---\n", total);
        registro(total);
    }
}
