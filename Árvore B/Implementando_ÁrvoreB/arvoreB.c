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

//Criando uma estrutura que ir� permitir retornar a chave que ir� subir no M�todo Tradicional de Inser��o e o ponteiro para o novo n� criado
typedef struct
{
    int chaveParaSubir;
    ArvoreB noParaSubir;
}RetornoInsere;

//Fun��o que inicializa a �rvore

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

        if(chaveBusca == raiz -> chave[meio])
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

//Fun��o SplitChildren
void splitChildren (ArvoreB noPai, int indiceParaDivisao)
{
    int i;
    ArvoreB novoIrmao = (ArvoreB) malloc(sizeof(NoArvB));

    if (novoIrmao == NULL)
    {
        printf("\nErro: falha na alocacao de memoria");
        exit(1);
    }

    ArvoreB noParaDivisao = noPai -> filho[indiceParaDivisao];
    novoIrmao -> ehFolha = noParaDivisao -> ehFolha;
    novoIrmao -> numeroDeChaves = T - 1;

    //Inicializando todos os ponteiros de filho[i]
    for (i = 0; i < MAX + 1; i++)
    {
        novoIrmao -> filho[i] = NULL;
    }

    //Inicializando as chaves com um valor seguro
    for (i = 0; i < MAX; i++)
    {
        novoIrmao -> chave[i] = -1000;
    }

    //Colocando os valores do noParaDivis�o para o n� irm�o
    for (int j = 0; j < T; j++)
    {
        novoIrmao -> chave[j] = noParaDivisao -> chave[T + j]; //Est� passando os valores depois da mediana para o novo n�
    }

    if (noParaDivisao -> ehFolha == 0)
    {
        for (int j = 0; j < T; j++)
        {
            novoIrmao -> filho[j] = noParaDivisao -> filho[T + j]; //Ou seja, se o n� que est� passando pela divis�o n�o for folha, seus filhos de T + 1 devem ser passado para o noIrmao
        }
    }

    noParaDivisao -> numeroDeChaves = T - 1;

    //Alterando o n� pai
    for (int j = noPai -> numeroDeChaves + 1; j > indiceParaDivisao; j--)
    {
        noPai -> filho[j + 1] = noPai -> filho[j];
    }
    noPai -> filho[i + 1] = novoIrmao;

    for (int j = noPai -> numeroDeChaves; i > indiceParaDivisao - 1; j--)
    {
        noPai -> chave[j+1] = noPai -> chave[j];
    }
    noPai -> chave[i] = noParaDivisao -> chave[T];

    noPai -> numeroDeChaves = noPai -> numeroDeChaves + 1;
}

//Fun��o split para o M�todo Tradicional de Inser��o, ele s� serve para divir
RetornoInsere splitInsercaoTradicional(ArvoreB noParaDivisao)
{
    RetornoInsere chaveENovoNo;
    chaveENovoNo.noParaSubir = (ArvoreB) malloc(sizeof(NoArvB));

    if(chaveENovoNo.noParaSubir == NULL)
    {
        printf("\nERRO: alocacao de memoria.");
        exit(1);
    }

    chaveENovoNo.noParaSubir -> ehFolha = noParaDivisao -> ehFolha;
    chaveENovoNo.noParaSubir -> numeroDeChaves = T - 1;

    //Inicializando todos os ponteiros de filho[i]
    for (int i = 0; i < MAX + 1; i++)
    {
        chaveENovoNo.noParaSubir -> filho[i] = NULL;
    }

    //Inicializando as chaves com um valor seguro
    for (int i = 0; i < MAX; i++)
    {
        chaveENovoNo.noParaSubir -> chave[i] = -1000;
    }

    //Copia as chaves � direita da mediana para o novo n�
    for (int j = 0; j < T - 1; j++)
    {
        chaveENovoNo.noParaSubir -> chave[j] = noParaDivisao -> chave[T + j]; //Est� passando os valores depois da mediana para o novo n�
    }

    if (noParaDivisao -> ehFolha == 0)
    {
        for (int j = 0; j < T; j++)
        {
            chaveENovoNo.noParaSubir -> filho[j] = noParaDivisao -> filho[T + j];//Ou seja, se o n� que est� passando pela divis�o n�o for folha, seus filhos de T + 1 devem ser passado para o noIrmao
            noParaDivisao -> filho[T + j] = NULL;
        }

    }

    noParaDivisao -> numeroDeChaves = T - 1;

    chaveENovoNo.chaveParaSubir = noParaDivisao -> chave[T - 1];

    return chaveENovoNo;
}

//Fun��o principal que gerencia o processo de inser��o tradicional
ArvoreB insereTradicionalNaArvoreB (ArvoreB raiz, int chaveParaInserir)
{
    //Caso 1: a �rvore est� vazia
    if (raiz == NULL)
    {
        raiz = (ArvoreB) malloc(sizeof(NoArvB));

        if(raiz == NULL)
        {
            printf("\nERRO: alocacao de memoria falhou.");
        }

        raiz -> ehFolha = 1;
        raiz -> numeroDeChaves = 1;
        raiz -> chave[0] = chaveParaInserir;

        //Inicializando todos os n�s filhos
        for(int i = 0; i < MAX + 1; i++)
        {
            raiz -> filho[i] = NULL;
        }

        return raiz;
    }

    //Caso 2: a �rvore n�o est� vazia, irei inicializar a inser��o utilizando recurs�o para a busca, para que o split possa acontecer
    RetornoInsere chaveENovoNo;
    chaveENovoNo = Insere(raiz, chaveParaInserir);

    if (chaveENovoNo.chaveParaSubir != -1000) //Ou seja, a raiz sofreu split
    {
        //Criando a nova raiz
        ArvoreB novaRaiz;
        novaRaiz = (ArvoreB) malloc(sizeof(NoArvB));

        if (novaRaiz == NULL)
        {
            printf("ERRO: alocacao de memoria falhou.");
            exit(1);
        }

        novaRaiz -> numeroDeChaves = 1;
        novaRaiz -> ehFolha = 0;
        novaRaiz -> chave[0] = chaveENovoNo.chaveParaSubir;

        //Primeiro, inicializando todos os filhos como NULL
        for (int i = 0; i < MAX + 1; i++)
        {
            novaRaiz -> filho[i] = NULL;
        }

        //Agora, passando os n�s que ela dever� apontar
        novaRaiz -> filho[0] = raiz;
        novaRaiz -> filho[1] = chaveENovoNo.noParaSubir;

        return novaRaiz;
    }

    return raiz;
}


