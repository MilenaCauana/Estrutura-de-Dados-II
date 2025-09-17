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

/*Fun��o de busca sem busca Bin�ria np vetor de chaves
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

/*Fun��o de busca com busca Bin�ria np vetor de chaves
*ARRUMAR:
* - meio = (inicio + fim) /2
* - colocar recurs�o para ir para os outros n�s
*/
RetornoBusca buscaArvBBuscaBinaria(ArvoreB raiz, int chaveBusca)
{
    if(raiz == NULL)
    {
        printf("\nArvore vazia!");

        RetornoBusca noNaoEncontrado = {-1, NULL};
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
            RetornoBusca noEncontrado = {meio, raiz};
            return noEncontrado;
        }

        if(chaveBusca < raiz -> chave[meio].codigoDeBarras)
        {
            fim = meio - 1;
        } else
        {
            inicio = meio + 1;
        }
    }

    //Se for folha, acabou a busca e n�o achou
    if(raiz -> ehFolha == 1)
    {
        RetornoBusca noNaoEncontrado = {-1, NULL};

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

        free(raiz -> chave);
        free(raiz -> filho);
        free(raiz);
        printf("\nNo liberado!\n"); // Mensagem de confirma��o para debug
    }
}

// Fun��o para liberar a mem�ria de um n�
void destruirNo(NoArvB *no)
{
    if (no == NULL)
    {
        return;
    }

    //Libera o array de chaves
    if (no -> chave != NULL)
    {
        free(no -> chave);
    }

    //Libera o array de ponteiros para filhos
    if (no->filho != NULL)
    {
        free(no -> filho);
    }

    //Libera o pr�prio n�
    free(no);
}

//A partir daqui o t � o t da main, uma vez que, aqui est� tratando como se o vetor fosse de 1 a ordem, mas, como vai de 0 a ordem - 1, para t pegar no meio mesmo, j� fiz o t + 1 em t

/*Fun��o Splitchildren, divide os n�s cheios em dois,
sempre que um n� cheio � encontrado*/
void SplitChild(ArvoreB noPai, int indiceFilho, int t)
{
    NoArvB *novoFilho = criarNo(t);    //Aloca novo n�, o novo filho
    NoArvB *noOriginal = noPai -> filho[indiceFilho];      //Recebe o n� cheio que ser� dividido

    novoFilho -> ehFolha = noOriginal -> ehFolha;
    novoFilho -> numeroDeChaves = t - 1;

    for (int j = 0; j < t - 1; j++)
    {
        novoFilho -> chave[j] = noOriginal -> chave[j + t];
    }

    if (!noOriginal->ehFolha)
    {
        for (int j = 0; j < t; j++)
        {
            novoFilho -> filho[j] = noOriginal -> filho[j + t];
        }
    }
    noOriginal -> numeroDeChaves = t - 1; //Atualiza o numero de chaves do no original

    for(int j = noPai -> numeroDeChaves; j >= indiceFilho; j--)    //Abre espa�o em no para o novo no
    {
        noPai -> filho[j + 1] = noPai -> filho[j];
    }

    noPai -> filho[indiceFilho + 1] = novoFilho; //no pai recebe novo no

    for(int j = noPai -> numeroDeChaves - 1; j >= indiceFilho; j--)    //Abre espa�o para a mediana do no original
    {
        noPai -> chave[j + 1] = noPai -> chave[j];
    }

    noPai -> chave[indiceFilho] = noOriginal -> chave[t - 1];        //Mediana do no original sobe pro pai
    noPai -> numeroDeChaves++;

}

/*Fun��o InsereNaoCheioArvoreB, insere os valores de maneira recursiva,
procurando o local onde inserir os valores e realizando splits quando necess�rio.*/
void InsereNaoCheioArvoreB(ArvoreB no, Produto produto, int t)
{
    int i = no -> numeroDeChaves - 1;     //Indice para percorrer as chaves do vetor

    if(no -> ehFolha)     //Se for folha, insere
    {
        while(i >= 0 && produto.codigoDeBarras < no -> chave[i].codigoDeBarras)
        {
            no -> chave[i + 1] = no -> chave[i];
            i--;
        }
        no->chave[i + 1] = produto;
        no->numeroDeChaves++;

    }else
    {
        while(i >= 0 && produto.codigoDeBarras < no -> chave[i].codigoDeBarras)     //Se n�o for folha, encontra filho apropriado
        {
            i--;
        }

        i++;

        if (no -> filho[i] -> numeroDeChaves == 2 * t - 1)      //Se filho estiver cheio,
        {
            SplitChild(no , i, t);      //Faz split antes de descer

            if(produto.codigoDeBarras > no -> chave[i].codigoDeBarras)
            {
                i++;
            }
        }

        InsereNaoCheioArvoreB(no -> filho[i], produto, t);   //Chama recursivamente para o filho
    }
}

/*Fun��o criarNo, cria n�s para a arvore-B*/
ArvoreB criarNo(int t)
{

    ArvoreB no = (ArvoreB)malloc(sizeof(NoArvB));
    if(no == NULL)
    {
        printf("\nERRO: nao foi possivel alocar a memoria.");
        return NULL;
    }

    no -> ehFolha = 1;
    no -> numeroDeChaves = 0;
    no -> chave = (Produto *) malloc((2*t - 1) * sizeof(Produto));
    no -> filho = (ArvoreB *) malloc((2*t) * sizeof(ArvoreB));

    if (no -> chave == NULL || no -> filho == NULL)
    {
        printf("\nERRO: nao foi possivel alocar memoria para chaves ou filhos.");
        free(no);
        return NULL;
    }

    //Fazendo com que todos os filhos apontem para nulo
    for (int i = 0; i < (2*t); i++)
    {
        no -> filho[i] = NULL;
    }

    return no;
}

/*Fun��o InsereArvoreB, principal
fun��o de inser��o da arvore B*/
ArvoreB InsereArvoreB(ArvoreB raiz, Produto produto, int t)
{
    if (raiz == NULL)
    {
        raiz = criarNo(t);
        raiz -> chave[0] = produto;
        raiz -> ehFolha = 1;
        raiz -> numeroDeChaves = 1;
        return raiz;
    }

    if(raiz -> numeroDeChaves == 2 * t - 1)     //Se a raiz estiver cheia
    {
       ArvoreB nova_raiz = criarNo(t);//cria nova raiz
       nova_raiz -> ehFolha = 0;
       nova_raiz -> filho[0] = raiz;
       SplitChild(nova_raiz, 0, t);  //faz split da raiz antiga

       int i = 0;

       if (nova_raiz -> chave[i].codigoDeBarras < produto.codigoDeBarras)
       {
           i++;
       }
       InsereNaoCheioArvoreB(nova_raiz -> filho[i], produto, t);   //Insere recursivamente a nova raiz

       return nova_raiz; //retorna a nova raiz

    }else
    {
        InsereNaoCheioArvoreB(raiz, produto, t);   //Insere recursivamente

        return raiz;        //retorna a raiz
    }

}

// ---- REMO��O ----
int removeArvoreB(ArvoreB no, int chaveRemover, int t)
{
    //Para a l�gica dessa fun��o, irei percorrer o n� que est� entrando e procurando qual dos tr�s casos ela pertence
    printf("\n-- Iniciando processo de remocao de do produto de codigo %d...", chaveRemover);

    if (no == NULL)
    {
        printf("\nProduto nao encontrado para remocao.");
        return 0;
    }

    int i = 0;
    //Encontrando o indice que, ou a chave estar� ou que iremos descer
    while(i < no -> numeroDeChaves && chaveRemover > no -> chave[i].codigoDeBarras)
    {
        i++;
    }

    //Agora que encontramos o �ndice, analisaremos os casos.
    //Nos primeiros casos, a chave est� dentro do n�
    if (i < no -> numeroDeChaves && chaveRemover == no -> chave[i].codigoDeBarras)
    {
        //CASO 1: a chave aparece no n� e o n� � uma folha
        //Para caso de estudo: como todos os splits necess�rios j� foram feitos antes da remo��o, podemos apenas remover a chave do n�
        if (no -> ehFolha)
        {

            printf("\nCodigo de Barras encontrado...");
            for (int j = i; j < no -> numeroDeChaves - 1; j++)
            {
                no -> chave[j] = no -> chave [j + 1];
            }
            no -> numeroDeChaves--;

            printf("\nProduto removido com sucesso!");
            return 1; //Deu certo e foi removio
        }

        //CASO 2: a chave est� no n� e o n� � interno
        printf("\nCodigo de Barras encontrado...");

        if (no -> filho[i] -> numeroDeChaves >= t) //CASO 2A)
        {
            ArvoreB predecessor;
            predecessor = no -> filho [i];

            while(!predecessor -> ehFolha)
            {
                predecessor = predecessor -> filho[predecessor -> numeroDeChaves]; //Encontrando o predecessor
            }

            Produto predecessorProduto = predecessor -> chave[predecessor -> numeroDeChaves - 1];
            no -> chave[i] = predecessorProduto;

            // Remove recursivamente o predecessor de sua sub-�rvore original.
            return removeArvoreB(no -> filho[i], predecessorProduto.codigoDeBarras, t);
        }

        if (no -> filho[i + 1] -> numeroDeChaves >= t) //CASO 2b) Se o filho que sucede tem pelo menos t chaves
        {
            ArvoreB sucessor;
            sucessor = no -> filho [i + 1];

            while(!sucessor -> ehFolha)
            {
                sucessor = sucessor -> filho[0]; //Encontrando o sucessor
            }
            Produto sucessorProduto = sucessor ->chave[0];
            // Substitui a chave a ser removida pelo produto sucessor.
            no -> chave[i] = sucessorProduto;

            // Remove recursivamente o sucessor de sua sub-�rvore original.
            return removeArvoreB(no->filho[i + 1], sucessorProduto.codigoDeBarras, t);
        }

        //CASO 2C; Caso os dois filhos tenham menos de T chaves, merge e chama recursivamente a remo��o.

        //Primeiro, irei passar pelo n� tirando a chave
        ArvoreB filho = no->filho[i];
        ArvoreB irmao = no->filho[i + 1];

        // A chave do pai (no->chave[i]) desce para o final do 'filho'.
        filho -> chave[filho -> numeroDeChaves] = no -> chave[i];
        filho->numeroDeChaves++;

        // Copia todas as chaves e filhos do 'irmao' para o 'filho'.
        for (int j = 0; j < irmao -> numeroDeChaves; j++)
        {
            filho->chave[filho->numeroDeChaves + j] = irmao->chave[j];
        }

        if (!filho->ehFolha)
        {
            for (int j = 0; j <= irmao->numeroDeChaves; j++)
            {
                filho->filho[filho->numeroDeChaves + j] = irmao->filho[j];
            }
        }
        filho->numeroDeChaves += irmao->numeroDeChaves;

        // Remove a chave[i] e o ponteiro para o 'irmao' do n� pai, deslocando os elementos.
        for (int j = i; j < no->numeroDeChaves - 1; j++)
        {
            no->chave[j] = no->chave[j + 1];
        }

        for (int j = i + 1; j < no->numeroDeChaves; j++)
        {
            no->filho[j] = no->filho[j + 1];
        }
        no->numeroDeChaves--;

        destruirNo(irmao);

        // Chama a remo��o recursivamente no n� mesclado.
        return removeArvoreB(filho, chaveRemover, t);
    }

    //Se chegou aqui, a chave n�o foi encontrada neste n�.
    //CASO 3: a chave n�o est� no n� e o n� � interno. Encontrar a raiz do filho que deve conter k.
    if (no -> ehFolha)
    {
        printf("\nProduto nao encontrado!");
        return 0;
    }

    // Antes de descer para o filho, verifica se ele tem o n�mero m�nimo de chaves.
    if (no->filho[i]->numeroDeChaves < t)
    {
        // CASO 3A) Tenta pegar emprestado do irm�o � esquerda (se ele existir e tiver chaves sobrando)
        if (i > 0 && no->filho[i - 1]->numeroDeChaves >= t)
        {
            ArvoreB filho = no->filho[i];
            ArvoreB irmaoEsq = no->filho[i - 1];

            // Abre espa�o no filho para a nova chave
            for (int j = filho->numeroDeChaves - 1; j >= 0; j--)
            {
                filho->chave[j + 1] = filho->chave[j];
            }

            int j;
            if (!filho->ehFolha)
            {
                for (j = filho->numeroDeChaves; j >= 0; j--);
            }
            filho->filho[j + 1] = filho->filho[j];

            // Chave do pai desce para o filho
            filho->chave[0] = no->chave[i - 1];
            if (!filho->ehFolha)
            {
                filho->filho[0] = irmaoEsq->filho[irmaoEsq->numeroDeChaves];
            }

            // �ltima chave do irm�o sobe para o pai
            no->chave[i - 1] = irmaoEsq->chave[irmaoEsq->numeroDeChaves - 1];

            filho->numeroDeChaves++;
            irmaoEsq->numeroDeChaves--;
        }
        // CASO 3b) Tenta pegar emprestado do irm�o � direita (se ele existir e tiver chaves sobrando)
        else if (i < no->numeroDeChaves && no->filho[i + 1]->numeroDeChaves >= t)
        {
            ArvoreB filho = no->filho[i];
            ArvoreB irmaoDir = no->filho[i + 1];

            // Chave do pai desce para o final do filho
            filho->chave[filho->numeroDeChaves] = no->chave[i];
            if (!filho->ehFolha)
            {
                filho->filho[filho->numeroDeChaves + 1] = irmaoDir->filho[0];
            }

            // Primeira chave do irm�o sobe para o pai
            no->chave[i] = irmaoDir->chave[0];

            // Desloca as chaves do irm�o para a esquerda
            for (int j = 1; j < irmaoDir->numeroDeChaves; j++)
            {
                irmaoDir->chave[j - 1] = irmaoDir->chave[j];
            }

            if (!irmaoDir->ehFolha)
            {
                for (int j = 1; j <= irmaoDir->numeroDeChaves; j++)
                {
                    irmaoDir->filho[j - 1] = irmaoDir->filho[j];
                }
            }

                filho->numeroDeChaves++;
                irmaoDir->numeroDeChaves--;
        }else
        {
            // CASO 3c) Nenhum irm�o pode emprestar, ent�o faz o merge com um deles.
            // Se 'i' � o �ltimo filho, faz o merge com o irm�o da esquerda.
            if (i == no->numeroDeChaves)
            {
                // Mescla filho[i-1] com filho[i]
                ArvoreB filho = no->filho[i-1];
                ArvoreB irmao = no->filho[i];
                // Chave do pai desce
                filho->chave[filho->numeroDeChaves] = no->chave[i-1];
                filho->numeroDeChaves++;

                // Copia chaves e filhos
                for (int j = 0; j < irmao->numeroDeChaves; j++)
                {
                    filho->chave[filho->numeroDeChaves + j] = irmao->chave[j];
                }

                if (!filho->ehFolha)
                {
                    for (int j = 0; j <= irmao->numeroDeChaves; j++)
                    filho->filho[filho->numeroDeChaves + j] = irmao->filho[j];
                }
                filho->numeroDeChaves += irmao->numeroDeChaves;

                // Remove do pai
                no->numeroDeChaves--;
                destruirNo(irmao);
            }else
            {
                // Sen�o, faz o merge com o irm�o da direita.
                // Mescla filho[i] com filho[i+1]
                ArvoreB filho = no->filho[i];
                ArvoreB irmao = no->filho[i+1];
                // Chave do pai desce
                filho->chave[filho->numeroDeChaves] = no->chave[i];
                filho->numeroDeChaves++;

                // Copia chaves e filhos
                for (int j = 0; j < irmao->numeroDeChaves; j++)
                {
                    filho->chave[filho->numeroDeChaves + j] = irmao->chave[j];
                }

                if (!filho->ehFolha)
                {
                    for (int j = 0; j <= irmao->numeroDeChaves; j++)
                    {
                        filho->filho[filho->numeroDeChaves + j] = irmao->filho[j];
                    }
                }
                    filho->numeroDeChaves += irmao->numeroDeChaves;

                // Remove do pai
                for (int j = i; j < no->numeroDeChaves - 1; j++)
                {
                    no->chave[j] = no->chave[j + 1];
                    no->filho[j + 1] = no->filho[j + 2];
                }

                no->numeroDeChaves--;
                destruirNo(irmao);
            }
        }
        // Agora que o filho tem chaves suficientes, chama a remo��o recursivamente para ele.
        return removeArvoreB(no->filho[i], chaveRemover, t);
    }
}

//Fun��o para imprimir a �rvore
void imprimirArvore(ArvoreB no)
{
    if (no == NULL)
    {
        printf("\nNao tem produtos!");
        return;
    }

    int i;
    for (i = 0; i < no -> numeroDeChaves; i++)
    {
        imprimirArvore(no -> filho[i]);
        imprimirProduto(no -> chave[i]);
    }

    imprimirArvore(no -> filho[i]);
}
