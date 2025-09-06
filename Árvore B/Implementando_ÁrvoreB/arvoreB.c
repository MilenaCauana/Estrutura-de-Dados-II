//Implementando �rvore B - Milena Cauana
//Primeiro irei fazer da minha cabe�a e, depois, irei conferir com os materiais.
//Primeiro farei com ponteiros, depois mudo para arquivos bin�rios
#include<stdlib.h>

#typedef MAX 20;

// ---- DEFININDO A ESTRUTURA DO N� ----
typedef struct No
{
    int n; //N�mero de chaves
    int folha; //Booleano
    int chave [MAX]; //Aqui, estou criando o vetor que armazenar� os dados
    struct No *filhos[MAX + 1]; //Ponteiros para os filhos

}NoArvB, *raizArvB;

//Fun��o de busca
/*
* Utilizarei recurs�o:
* - Parar� quando achar;
* - Parar� quando chegar em uma folha e n�o encontrar.
*/
int buscaArvB(raizArvB no, int busca)
{
    int i;

    for (i = 0; i < no.n; i++)
    {
        if (no.chave[i] == busca)
        {
            return no.chave[i];
        }
        if (busca < no.chave[i])
        {
            buscarArvB(no.filhos[i], busca);
        }
    }

    if (no.folha)
    {
        printf("Valor nao encontrado");
        return -1;
    }

    buscaArvB(no.filhos[i], busca);
}


