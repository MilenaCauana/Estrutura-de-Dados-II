//Implementando �rvore B - Milena Cauana
//Primeiro irei fazer da minha cabe�a e, depois, irei conferir com os materiais.
//Primeiro farei com ponteiros, depois mudo para arquivos bin�rios
#include<stdlib.h>
#include<stdio.h>

#include "avoreB.h"

//Fun��o que inicializa a �rvore
ArvoreB inicializaArvore()
{
    return NULL;
}

//Fun��o de busca sem busca Bin�ria np vetor de chaves
RetornoBusca buscaArvB(ArvoreB raiz, int chaveBusca)
{
    int i = 0;

    while(i < raiz->numeroDeChaves && chaveBusca > raiz -> chave[i].codigoDeBarras)
    {
        i++;
    }

    if (i < raiz -> numeroDeChaves && chaveBusca == raiz -> chave[i].codigoDeBarras)
    {
        RetornoBusca noEncontrado;
        noEncontrado.indiceChave = i;
        noEncontrado.noEncotrado = raiz;

        return (noEncontrado);
    }

    if (raiz -> ehFolha)
    {
        RetornoBusca noNaoEncontrado;
        noNaoEncontrado.indiceChave = -1;
        noNaoEncontrado.noEncotrado = NULL;

        printf("\nNao encontrado!");
        return noNaoEncontrado;
    }

    return buscaArvB(raiz -> filho[i], chaveBusca);
}

//Fun��o de busca com busca Bin�ria np vetor de chaves
/*ARRUMAR:
* - meio = (inicio + fim) /2
* - colocar recurs�o para ir para os outros n�s
*/
RetornoBusca buscaArvBBuscaBinaria(ArvoreB raiz, int chaveBusca)
{
    if(raiz == NULL)
    {
        printf("\nArvore vazia.");

        RetornoBusca noNaoEncontrado;
        noNaoEncontrado.indiceChave = -1;
        noNaoEncontrado.noEncotrado = NULL;

        printf("\nNao encontrado!");
        return noNaoEncontrado;
    }
    //Ir� parar a recurs�o se encontrar ou se for folha e n�o encontrar

    //Buscando dentro do vetor
    int inicio = 0;
    int fim = raiz -> numeroDeChaves - 1;
    int meio;

    while (inicio <= fim)
    {
        meio = (inicio + fim) / 2;

        if(chaveBusca == raiz -> chave[meio].codigoDeBarras)
        {
            RetornoBusca noEncontrado;
            noEncontrado.indiceChave = meio;
            noEncontrado.noEncotrado = raiz;

            return noEncontrado;
        }

        if(chaveBusca < raiz -> chave[meio])
        {
            fim = meio - 1;
        } else if(chaveBusca > raiz -> chave[meio])
        {
            inicio = meio + 1;
        }
    }

    //Se for folha, acabou a busca e n�o achou
    if(raiz -> ehFolha == 1)
    {
        RetornoBusca noNaoEncontrado;
        noNaoEncontrado.indiceChave = -1;
        noNaoEncontrado.noEncotrado = NULL;

        printf("\nNao encontrado!");
        return noNaoEncontrado;
    }

    //Agora, se ele chegou aqui, ele n�o encontrou no vetor e n�o � folha, ou seja, � para entrar na recurs�o
    return buscaArvBBuscaBinaria(raiz -> filho[inicio], chaveBusca);
}


// Fun��o para liberar a mem�ria alocada por uma �rvore B
// Ela percorre a �rvore de forma recursiva, liberando os n�s a partir das folhas
void desfazArvore(ArvoreB raiz)
{
    // Se a raiz n�o for nula, continua a recurs�o
    if (raiz != NULL)
    {
        // Percorre todos os filhos do n� atual para liber�-los
        for (int i = 0; i <= raiz -> numeroDeChaves; i++)
        {
            // Chamada recursiva para cada filho
             desfazArvore(raiz -> filho[i]);
        }

        // Depois que todos os filhos foram liberados, libera o n� atual
        free(raiz);
        printf("\nN� liberado!"); // Mensagem de confirma��o para debug
    }
}

// Fun��o para liberar a mem�ria de um n�
void destruirNo(NoArvB *no) {
    if (no == NULL) {
        return;
    }

    // 1. Libera o array de chaves
    if (no->chave != NULL) {
        free(no->chave);
        no->chave = NULL; // Evita ponteiros dangling
    }

    // 2. Libera o array de ponteiros para filhos
    if (no->filho != NULL) {
        free(no->filho);
        no->filho = NULL; // Evita ponteiros dangling
    }

    // 3. Libera o pr�prio n�
    free(no);
    no = NULL; // Evita ponteiros dangling
}

// ---- REMO��O ----
int removeArvoreB(ArvoreB no, int chaveRemover)
{
    //Para a l�gica dessa fun��o, irei percorrer o n� que est� entrando e procurando qual dos tr�s casos ela pertence
    printf("\n-- Iniciando processo de remo��o de %c...", chaveRemover);


    //CASO 1: a chave aparece no n� e o n� � uma folha
    //Para caso de estudo: como todos os splits necess�rios j� foram feitos antes da remo��o, podemos apenas remover a chave do n�
    if (no -> ehFolha)
    {
        for (int i = 0; i < no -> numeroDeChaves; i++)
        {
            if (chaveRemover == no -> chave[i])
            {
                printf("\nCodigo de Barras encontrado...");
                for (j = i; j < no -> numeroDeChaves; j++)
                {
                    no -> chave[j] = no -> chave [j + 1];
                }
                produto.quantidade--;
                if (produto.quantidade == 0)
                {
                    produto.estaDisponivel = 0;
                }

                printf("\nProduto removido com sucesso!");

                return 1; //Deu certo e foi removio
            }
        }

        printf("\nCodigo de Barras nao encontrado!");
        return 0;
    }

    //Agora, como o n� n�o � folha, irei percorrer ele a procura da chave que est� sendo procurada ou do filho para o qual devo continuar a busca
    for (int i = 0; i < no -> numeroDeChaves; i++)
    {
        //CASO 2: a chave est� no n� e o n� � interno
        if (chaveRemover == no -> chave[i]) //CASO 2a) Se o filho que precede tem pelo menos t chaves
        {
            printf("\nCodigo de Barras encontrado...");

            if (no -> filho[i] -> numeroDeChaves >= T)
            {
                ArvoreB predecessor;
                predecessor = no -> filho [i];

                while(predecessor -> ehFolha == 0)
                {
                    predecessor = predecessor -> filho[predecessor -> numeroDeChaves]; //Encontrando o predecessor
                }

                int novaChaveRemover = predecessor -> chave[predecessor -> numeroDeChave - 1];
                no -> chave [i] = novaChaveRemover;

                return removeArvoreB(predecessor, novaChaveRemover);
            }

        if (no -> filho[i + 1] -> numeroDeChaves >= T) //CASO 2b) Se o filho que sucede tem pelo menos t chaves
        {
            ArvoreB sucessor;
            sucessor = no -> filho [i + 1];

            while(sucessor -> ehFolha == 0)
            {
                sucessor = sucessor -> filho[0]; //Encontrando o sucessor
            }

            int novaChaveRemover = sucessor -> chave[0];
            no -> chave [i] = novaChaveRemover;

            return removeArvoreB(sucessor, novaChaveRemover);
        }

        //CASO 2C; Caso os dois filhos tenham menos de T chaves, merge e chama recursivamente a remo��o.

        //Primeiro, irei passar pelo n� tirando a chave
        for (int j = i; j < no -> numeroDeChaves; j++)
        {
            no -> chave [i] = no -> chave[i + 1];
            no -> filho[1 + i] = no -> filho[2 + i];
        }

        //Agora, irei de fato fazer o merge
        ArvoreB noMerge;
        noMerge = no -> filho[i];
        ArvoreB noARemover;
        noARemover = no -> filho[i + 1];

        noMerge -> chave[no -> numeroDeChaves] = chaveRemover;
        noMerge -> numeroDeChaves ++;

        //Agora, irei pegar o n� que ser� removido e irei juntar com o n� que ser� feito o merge.
        //Nesse processo, se o n� for interno e tiver filhos, esses ponteiros s�o passados.
        //Como no n� folha todos os ponteiros para filhos est�o nulos, ao passar eles de um pra outro ele continuar� nulo, ent�o farei isso.
        int j;
        for (j = 0; j < noARemover -> numeroDeChaves; j++)
        {
            noMerge -> chave[noMerge -> numeroDeChaves] = noARemover -> chave[j];
            noMerge -> filho[noMerge -> numeroDeChaves + 1] = noARemover -> filho[j];

            noMerge -> numeroDeChaves++;
        }
        noMerge -> filho[noMerge -> numeroDeChaves + 1] = noARemover -> filho[j];

        //Agora que j� foi tudo passado, podemos liberar o n�
        destruirNo(noARemover);

        //Chamando a fun��o de remo��o para o n� em que foi feito o merge e que agora, possui a chave a ser removida
        return removeArvoreB(noMerge, chaveRemover);
        }
    }

    //Se chegou aqui, n�o � folha e estamos em um n� interno que n�o possui a chave que estamos procurando.
    //CASO 3: a chave n�o est� no n� e o n� � interno. Encontrar a raiz do filho que deve conter k.
    int i;
    for (i = 0; chaveRemover > no -> chave[i]; i++);

    ArvoreB noFilho;
    noFilho = no -> filho [i];

    ArvoreB noIrmaoEsq, noIrmaoDir;
    noIrmaoEsq = no -> filho[i - 1];
    noIrmaoDir = no -> filho[i + 1];

    if (noFilho -> numeroDeChaves < T)
    {
        if (noIrmaoEsq -> numeroDeChaves >= T) //O irm�o a esquerda tem quantidade m�nima para realizar a rota��o
        {
            //Passando pelo n� filho abrindo espa�o para receber o no -> chave [i - 1]
            for (int i = noFilho -> numeroDeChaves; i > 0; i--)
            {
                noFilho -> chave[i] = noFilho -> chave[i - 1];
            }

            if (!noFilho -> ehFolha)
            {
                for (int j = noFilho->numeroDeChaves + 1; j > 0; j--)
                {
                    noFilho->filho[j] = noFilho->filho[j - 1];
                }
            }

            noFilho -> chave[0] = no -> chave[i - 1];

            if (!noFilho->ehFolha)
            {
                noFilho->filho[0] = noIrmaoEsq->filho[noIrmaoEsq->numeroDeChaves];
            }

            // Move a �ltima chave de noIrmaoEsq para o pai
            no->chave[i - 1] = noIrmaoEsq->chave[noIrmaoEsq->numeroDeChaves - 1];

            // Atualiza o n�mero de chaves
            noFilho->numeroDeChaves++;
            noIrmaoEsq->numeroDeChaves--;

            return removeArvoreB(noFilho, chaveRemover);
        }

        if (noIrmaoDir -> numeroDeChaves >= T) //O irm�o a direita tem quantidade m�nima para realizar a rota��o
        {
            // Move a chave do pai para noFilho
            noFilho->chave[noFilho->numeroDeChaves] = no->chave[i];

            // Move o primeiro filho de noIrmaoDir para noFilho
            if (!noFilho->ehFolha)
            {
                noFilho->filho[noFilho->numeroDeChaves + 1] = noIrmaoDir->filho[0];
            }

            // Move a primeira chave de noIrmaoDir para o pai
            no->chave[i] = noIrmaoDir->chave[0];

            // Desloca as chaves de noIrmaoDir para a esquerda
            for (int j = 0; j < noIrmaoDir->numeroDeChaves - 1; j++)
            {
                noIrmaoDir->chave[j] = noIrmaoDir->chave[j + 1];
            }

            // Desloca os filhos de noIrmaoDir para a esquerda
            if (!noFilho -> ehFolha)
            {
                for (int j = 0; j < noIrmaoDir->numeroDeChaves; j++)
                {
                    noIrmaoDir->filho[j] = noIrmaoDir->filho[j + 1];
                }
            }

            // Atualiza o n�mero de chaves
            noFilho->numeroDeChaves++;
            noIrmaoDir->numeroDeChaves--;

            return removeArvoreB(noFilho, chaveRemover);
        }

        //Se chegou aqui, o n� filho < T e seus irm�o diretos < T tamb�m, ent�o, faremos um merge
        //Agora, irei de fato fazer o merge
        int i;

        for (i = 0; i < no -> numeroDeChaves && chaveRemover > no -> chave[i]; i++); //Encontrando o indice do filho que dever� conter a chave

        // Movendo a chave do pai para o noFilho
        noFilho -> chave[noFilho -> numeroDeChaves] = no -> chave[i];
        noFilho -> numeroDeChaves++;

        //Movendo todas as chaves do noIrmaoDir para o noFilho
        for (int j = 0; j < noIrmaoDir -> numeroDeChaves; j++)
        {
            noFilho -> chave[noFilho -> numeroDeChaves + j] = noIrmaoDir -> chave[j];
        }

        // Se n�o for uma folha, move os ponteiros dos filhos
        if (!noFilho -> ehFolha)
        {
            for (int j = 0; j <= noIrmaoDir -> numeroDeChaves; j++)
            {
                noFilho -> filho[noFilho -> numeroDeChaves + j] = noIrmaoDir -> filho[j];
            }
        }

        // Atualiza o n�mero de chaves do n� mesclado
        noFilho -> numeroDeChaves += noIrmaoDir -> numeroDeChaves;

        // Agora, remove a chave e o ponteiro do n� pai
        // Desloca as chaves do pai para a esquerda
        for (int j = i; j < no -> numeroDeChaves - 1; j++)
        {
            no -> chave[j] = no -> chave[j + 1];
        }

        // Desloca os ponteiros dos filhos do pai para a esquerda
        for (int j = i + 1; j < no -> numeroDeChaves; j++)
        {
            no->filho[j] = no -> filho[j + 1];
        }

        // Atualiza o n�mero de chaves do n� pai
        no -> numeroDeChaves--;

        // Libera o n� do irm�o que foi mesclado
        destruirNo(noIrmaoDir);

        // Agora, chama recursivamente a fun��o de remo��o para o n� mesclado
        return removeArvoreB(noFilho, chaveRemover);
    }

    return removeArvoreB(noFilho, chaveRemover);
}

//Fun��o para imprimir a �rvore
void imprimirArvore(ArvoreB no)
{
    for (int i = 0; i < no -> numeroDeChaves; i++)
    {
        imprimirProduto(no -> chave[i]);
        imprimirArvore(no -> filho[i]);
    }

    imprimirArvore(no -> filho[i]);
}
