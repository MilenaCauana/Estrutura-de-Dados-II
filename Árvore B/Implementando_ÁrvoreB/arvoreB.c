//Implementando �rvore B - Milena Cauana
//Primeiro irei fazer da minha cabe�a e, depois, irei conferir com os materiais.
//Primeiro farei com ponteiros, depois mudo para arquivos bin�rios
#include<stdlib.h>
#include<stdio.h>

#define MAX 20
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

    return buscaArvB(raiz -> filho[i]);
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

//Split ou Divis�o
/* Seja um n� cheio, crie dois novos n�s:
* - Um com as chaves [1], ..., chave[t-1] e outro com as chaves chave[t+a],...,chave[t].
*/
void splitArvB(raizArvB noMae, raizArvB noCheio)
{

    int meio = noCheio -> n/2;
    int chaveSubida = noCheio -> chave[meio];

    //Criar os novos n�s
    raizArvB novo_no1 = (*NoArvB) malloc(sizeof(NoArvB));
    raizArvB novo_no2 = (*NoArvB) malloc(sizeof(NoArvB));

    //Colocando as informa��es pr�vias dos n�s
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

    // Copia as chaves e filhos para o segundo novo n�
    for (int i = 0; i < novoNo2->n; i++)
    {
        novo_no2->chave[i] = noCheio->chave[meio + 1 + i];
        novo_no2->filhos[i] = noCheio->filhos[meio + 1 + i];
    }
    novo_no2->filhos[novo_no2->n] = noCheio->filhos[noCheio->n];

    //Agora, irei colocar o elemento no no m�e e mover seus elementos a direita
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

    //Agora, veremos se o n� m�e est� cheio, para ir subindo recursivamente, se n�o, ele retorna.
}

//Fun��o de busca para o n� (Inser��o)
/*
* Utilizarei recurs�o:
* - Parar� quando achar a folha em que o n�mero ser� inserida;
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
                    //Chama a fun��o split;
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


