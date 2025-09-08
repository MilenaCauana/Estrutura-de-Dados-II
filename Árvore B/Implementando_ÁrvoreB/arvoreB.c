//Implementando �rvore B - Milena Cauana
//Primeiro irei fazer da minha cabe�a e, depois, irei conferir com os materiais.
//Primeiro farei com ponteiros, depois mudo para arquivos bin�rios
#include<stdlib.h>
#include<stdio.h>

#define MAX 3
#define T (MAX + 1)/2 //Aqui, estou definindo t, que ser� utilizado para fazer a conta do m�ximo e do m�nimo de chaves que um n� deve ter

// ---- DEFININDO A ESTRUTURA DO N� ----
typedef struct No
{
    int numeroDeChaves;
    int ehFolha;
    int chave[MAX];
    struct No *filho[MAX + 1];

}NoArvB, *ArvoreB;

//Criando uma estrutura que ir� me permitir retornar o n� e o �ndice na fun��o de busca
typedef struct
{
    int indiceChave;
    ArvoreB noEncotrado;
} RetornoBusca;

//Fun��o de busca sem busca Bin�ria np vetor de chaves
RetornoBusca buscaArvB(ArvoreB raiz, int chaveBusca)
{
    int i = 0;

    while(i < raiz->numeroDeChaves && chaveBusca > raiz -> chave[i])
    {
        i++;
    }

    if (i < raiz -> numeroDeChaves && chaveBusca == raiz -> chave[i])
    {
        RetornoBusca noEncontrado;
        noEncontrado.indiceChave = i;
        noEncontrado.noEncotrado = raiz;

        return (noEncontrado);
    }

    if (raiz -> ehFolha)
    {
        return NULL;
    }

    return buscaArvB(raiz -> filho[i], chaveBusca);
}

//Fun��o de busca com busca Bin�ria np vetor de chaves
RetornoBusca buscaArvBBuscaBinaria(ArvoreB raiz, int chaveBusca)
{
    int i = raiz -> numeroDeChaves/2;
    int indiceMaximo = raiz -> numeroDeChaves;
    int indiceMinimo = 0;

    while (indiceMaximo != indiceMinimo)
    {
        if(chaveBusca == raiz -> chave[i])
        {
            RetornoBusca noEncontrado;
            noEncontrado.indiceChave = i;
            noEncontrado.noEncotrado = raiz;

            return (noEncontrado);
        }

        if(chaveBusca < raiz -> chave[i])
        {
            indiceMaximo = i;
            i = (i - indiceMinimo) /2;
        } else if(chaveBusca > raiz -> chave[i])
        {
            indiceMinimo = i;
            i = ((indiceMaximo - i) / 2) + i;
        }
    }

    return NULL;
}

//Fun��o SplitChildren
void splitChildren (ArvoreB noPai, int indiceParaDivisao)
{
    ArvoreB novoIrmao = (ArvoreB) malloc(sizeof(NoArvB));
    ArvoreB noParaDivisao = noPai -> filho[indiceParaDivisao];
    novoIrmao -> ehFolha = noParaDivisao -> ehFolha;

    noIrmao -> numeroDeChaves = T - 1;

    for (j = 0; j < T; j++)
    {
        novoIrmao -> chave[j] = noParaDivisao -> chave[T + j]; //Est� passando os valores depois da mediana para o novo n�
    }

    if (!noParaDivis�o -> folha)
    {
        for (j = 0; j < T; j++)
        {
            noIrmao -> filho[j] = noParaDivisao -> filho[T + j]; //Ou seja, se o n� que est� passando pela divis�o n�o for folha, seus filhos de T + 1 devem ser passado para o noIrmao
        }
    }

    noParaDivisao -> numeroDeChaves = T - 1;

    //Alterando o n� pai
    for (j = noPai -> numeroDeChaves + 1; j > indiceParaDivisao; j--)
    {
        noPai -> filho[j + 1] = noPai -> filho[j];
    }
    noPai -> filho[i + 1] = noIrmao;

    for (j = noPai -> numeroDeChaves; i > indiceParaDivisao - 1; j--)
    {
        noPai -> chave[j+1] = noPai -> chave[j];
    }
    noPai -> chave[i] = noParaDivisao -> chave[T];

    noPai -> numeroDeChaves = noPai -> numeroDeChaves + 1;
}
