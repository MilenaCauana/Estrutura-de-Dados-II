//Implementando árvore B - Milena Cauana
//Primeiro irei fazer da minha cabeça e, depois, irei conferir com os materiais.
//Primeiro farei com ponteiros, depois mudo para arquivos binários
#include<stdlib.h>
#include<stdio.h>

#define MAX 20
#define T (MAX + 1)/2 //Aqui, estou definindo t, que será utilizado para fazer a conta do máximo e do mínimo de chaves que um nó deve ter

// ---- DEFININDO A ESTRUTURA DO NÓ ----
typedef struct No
{
    int numeroDeChaves;
    int ehFolha;
    int chave[MAX];
    struct No *filho[MAX + 1];

}NoArvB, *ArvoreB;

//Criando uma estrutura que irá me permitir retornar o nó e o índice na função de busca
typedef struct
{
    int indiceChave;
    ArvoreB noEncotrado;
} RetornoBusca;

//Função de busca sem busca Binária np vetor de chaves
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

    return buscaArvB(raiz -> filho[i]);
}

//Função de busca com busca Binária np vetor de chaves
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
