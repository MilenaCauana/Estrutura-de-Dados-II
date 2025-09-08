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

//Split ou Divisão
/* Seja um nó cheio, crie dois novos nós:
* - Um com as chaves [1], ..., chave[t-1] e outro com as chaves chave[t+a],...,chave[t].
*/
void splitArvB(raizArvB noMae, raizArvB noCheio)
{

    int meio = noCheio -> n/2;
    int chaveSubida = noCheio -> chave[meio];

    //Criar os novos nós
    raizArvB novo_no1 = (*NoArvB) malloc(sizeof(NoArvB));
    raizArvB novo_no2 = (*NoArvB) malloc(sizeof(NoArvB));

    //Colocando as informações prévias dos nós
    novo_no1 -> n = meio;
    novo_no2 -> n = noCheio -> n - (meio + 1);
    novo_no1 -> folha = noCheio -> folha;
    novo_no2 -> folha = noCheio -> folha;

    for(j = 0; j < no.chave[meio]; j++)
        {
            novo_no1.chave[j] = noCheio.chave[j];
            novo_no1.filhos[j] = noCheio.filhos[j];
        }
    novo_no1 -> filhos[meio] = noCheio -> filhos[meio];

    // Copia as chaves e filhos para o segundo novo nó
    for (int i = 0; i < novoNo2->n; i++)
    {
        novo_no2->chave[i] = noCheio->chave[meio + 1 + i];
        novo_no2->filhos[i] = noCheio->filhos[meio + 1 + i];
    }
    novo_no2->filhos[novo_no2->n] = noCheio->filhos[noCheio->n];

    //Agora, irei colocar o elemento no no mãe e mover seus elementos a direita
    for(i = 0; i <= noMae -> n; i++)
    {
        int aux;
        if (noMae -> chave[i] == noMae -> chave[noMae -> n]) //Se o local onde o elemento for inserido for o vago depois do n-1
        {
            noMae -> chave[i] = chaveSubida;
            noMae -> filhos[i] = novo_no1;
            noMae -> filhos[i + 1] = novo_no2;
            break;
        } else if(chaveSubida < noMae -> chave[i]) //Se ele encontrar um lugar no meio do vetor
        {
            aux = noMae -> chave[i-1];
            noMae -> chave[i-1] = aux;

            raizArvB no_aux = noMae -> filhos[i];
            noMae -> filhos[i - 1] = novo_no1;
            noMae -> filhos[i] = novo_no2;

            int aux1;
            for (j = i; j <= noMae-> n; j++)
            {
                aux1 = noMae -> chave[i];
                noMae -> chave[i] = aux;
                aux = aux1;

                raizArvB no_aux1 = noMae -> filhos[i + 1];
                noMae -> filhos[i + 1] = no_aux;
                no_aux = no_aux1;
            }
        }
    }

    //Agora, veremos se o nó mãe está cheio, para ir subindo recursivamente, se não, ele retorna.
}

//Função de busca para o nó (Inserção)
/*
* Utilizarei recursão:
* - Parará quando achar a folha em que o número será inserida;
*/
raizArvB buscaArvB(raizArvB noMae, raizArvB no, int busca)
{
    int i;

    for (i = 0; i < no.n; i++)
    {
        if (no.chave[i] == busca)
        {
            printf("\nElemento ja existe!");
            return NULL;
        }

        if (busca < no.chave[i])
        {
            if (no.folha)
            {
                if (no.n > MAX)
                {
                    //Chama a função split;
                } else
                {
                    return no;
                }
            }
            buscarArvB(no, no.filhos[i], busca);
        }
    }

    buscaArvB(no, no.filhos[i], busca);
}


