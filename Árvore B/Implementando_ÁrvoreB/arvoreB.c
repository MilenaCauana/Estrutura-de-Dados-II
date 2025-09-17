//Implementando árvore B - Milena Cauana
//Primeiro irei fazer da minha cabeça e, depois, irei conferir com os materiais.
//Primeiro farei com ponteiros, depois mudo para arquivos binários
#include<stdlib.h>
#include<stdio.h>

#include "avoreB.h"

//Função que inicializa a árvore
ArvoreB inicializaArvore()
{
    return NULL;
}

//Função de busca sem busca Binária np vetor de chaves
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

//Função de busca com busca Binária np vetor de chaves
/*ARRUMAR:
* - meio = (inicio + fim) /2
* - colocar recursão para ir para os outros nós
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
    //Irá parar a recursão se encontrar ou se for folha e não encontrar

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

    //Se for folha, acabou a busca e não achou
    if(raiz -> ehFolha == 1)
    {
        RetornoBusca noNaoEncontrado;
        noNaoEncontrado.indiceChave = -1;
        noNaoEncontrado.noEncotrado = NULL;

        printf("\nNao encontrado!");
        return noNaoEncontrado;
    }

    //Agora, se ele chegou aqui, ele não encontrou no vetor e não é folha, ou seja, é para entrar na recursão
    return buscaArvBBuscaBinaria(raiz -> filho[inicio], chaveBusca);
}


// Função para liberar a memória alocada por uma Árvore B
// Ela percorre a árvore de forma recursiva, liberando os nós a partir das folhas
void desfazArvore(ArvoreB raiz)
{
    // Se a raiz não for nula, continua a recursão
    if (raiz != NULL)
    {
        // Percorre todos os filhos do nó atual para liberá-los
        for (int i = 0; i <= raiz -> numeroDeChaves; i++)
        {
            // Chamada recursiva para cada filho
             desfazArvore(raiz -> filho[i]);
        }

        // Depois que todos os filhos foram liberados, libera o nó atual
        free(raiz);
        printf("\nNó liberado!"); // Mensagem de confirmação para debug
    }
}

// Função para liberar a memória de um nó
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

    // 3. Libera o próprio nó
    free(no);
    no = NULL; // Evita ponteiros dangling
}

// ---- REMOÇÃO ----
int removeArvoreB(ArvoreB no, int chaveRemover)
{
    //Para a lógica dessa função, irei percorrer o nó que está entrando e procurando qual dos três casos ela pertence
    printf("\n-- Iniciando processo de remoção de %c...", chaveRemover);


    //CASO 1: a chave aparece no nó e o nó é uma folha
    //Para caso de estudo: como todos os splits necessários já foram feitos antes da remoção, podemos apenas remover a chave do nó
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

    //Agora, como o nó não é folha, irei percorrer ele a procura da chave que está sendo procurada ou do filho para o qual devo continuar a busca
    for (int i = 0; i < no -> numeroDeChaves; i++)
    {
        //CASO 2: a chave está no nó e o nó é interno
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

        //CASO 2C; Caso os dois filhos tenham menos de T chaves, merge e chama recursivamente a remoção.

        //Primeiro, irei passar pelo nó tirando a chave
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

        //Agora, irei pegar o nó que será removido e irei juntar com o nó que será feito o merge.
        //Nesse processo, se o nó for interno e tiver filhos, esses ponteiros são passados.
        //Como no nó folha todos os ponteiros para filhos estão nulos, ao passar eles de um pra outro ele continuará nulo, então farei isso.
        int j;
        for (j = 0; j < noARemover -> numeroDeChaves; j++)
        {
            noMerge -> chave[noMerge -> numeroDeChaves] = noARemover -> chave[j];
            noMerge -> filho[noMerge -> numeroDeChaves + 1] = noARemover -> filho[j];

            noMerge -> numeroDeChaves++;
        }
        noMerge -> filho[noMerge -> numeroDeChaves + 1] = noARemover -> filho[j];

        //Agora que já foi tudo passado, podemos liberar o nó
        destruirNo(noARemover);

        //Chamando a função de remoção para o nó em que foi feito o merge e que agora, possui a chave a ser removida
        return removeArvoreB(noMerge, chaveRemover);
        }
    }

    //Se chegou aqui, não é folha e estamos em um nó interno que não possui a chave que estamos procurando.
    //CASO 3: a chave não está no nó e o nó é interno. Encontrar a raiz do filho que deve conter k.
    int i;
    for (i = 0; chaveRemover > no -> chave[i]; i++);

    ArvoreB noFilho;
    noFilho = no -> filho [i];

    ArvoreB noIrmaoEsq, noIrmaoDir;
    noIrmaoEsq = no -> filho[i - 1];
    noIrmaoDir = no -> filho[i + 1];

    if (noFilho -> numeroDeChaves < T)
    {
        if (noIrmaoEsq -> numeroDeChaves >= T) //O irmão a esquerda tem quantidade mínima para realizar a rotação
        {
            //Passando pelo nó filho abrindo espaço para receber o no -> chave [i - 1]
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

            // Move a última chave de noIrmaoEsq para o pai
            no->chave[i - 1] = noIrmaoEsq->chave[noIrmaoEsq->numeroDeChaves - 1];

            // Atualiza o número de chaves
            noFilho->numeroDeChaves++;
            noIrmaoEsq->numeroDeChaves--;

            return removeArvoreB(noFilho, chaveRemover);
        }

        if (noIrmaoDir -> numeroDeChaves >= T) //O irmão a direita tem quantidade mínima para realizar a rotação
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

            // Atualiza o número de chaves
            noFilho->numeroDeChaves++;
            noIrmaoDir->numeroDeChaves--;

            return removeArvoreB(noFilho, chaveRemover);
        }

        //Se chegou aqui, o nó filho < T e seus irmão diretos < T também, então, faremos um merge
        //Agora, irei de fato fazer o merge
        int i;

        for (i = 0; i < no -> numeroDeChaves && chaveRemover > no -> chave[i]; i++); //Encontrando o indice do filho que deverá conter a chave

        // Movendo a chave do pai para o noFilho
        noFilho -> chave[noFilho -> numeroDeChaves] = no -> chave[i];
        noFilho -> numeroDeChaves++;

        //Movendo todas as chaves do noIrmaoDir para o noFilho
        for (int j = 0; j < noIrmaoDir -> numeroDeChaves; j++)
        {
            noFilho -> chave[noFilho -> numeroDeChaves + j] = noIrmaoDir -> chave[j];
        }

        // Se não for uma folha, move os ponteiros dos filhos
        if (!noFilho -> ehFolha)
        {
            for (int j = 0; j <= noIrmaoDir -> numeroDeChaves; j++)
            {
                noFilho -> filho[noFilho -> numeroDeChaves + j] = noIrmaoDir -> filho[j];
            }
        }

        // Atualiza o número de chaves do nó mesclado
        noFilho -> numeroDeChaves += noIrmaoDir -> numeroDeChaves;

        // Agora, remove a chave e o ponteiro do nó pai
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

        // Atualiza o número de chaves do nó pai
        no -> numeroDeChaves--;

        // Libera o nó do irmão que foi mesclado
        destruirNo(noIrmaoDir);

        // Agora, chama recursivamente a função de remoção para o nó mesclado
        return removeArvoreB(noFilho, chaveRemover);
    }

    return removeArvoreB(noFilho, chaveRemover);
}

//Função para imprimir a árvore
void imprimirArvore(ArvoreB no)
{
    for (int i = 0; i < no -> numeroDeChaves; i++)
    {
        imprimirProduto(no -> chave[i]);
        imprimirArvore(no -> filho[i]);
    }

    imprimirArvore(no -> filho[i]);
}
