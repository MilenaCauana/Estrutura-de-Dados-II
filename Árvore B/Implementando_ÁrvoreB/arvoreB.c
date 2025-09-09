//Implementando árvore B - Milena Cauana
//Primeiro irei fazer da minha cabeça e, depois, irei conferir com os materiais.
//Primeiro farei com ponteiros, depois mudo para arquivos binários
#include<stdlib.h>
#include<stdio.h>

#define MAX 3
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

//Criando uma estrutura que irá permitir retornar a chave que irá subir no Método Tradicional de Inserção e o ponteiro para o novo nó criado
typedef struct
{
    int chaveParaSubir;
    ArvoreB noParaSubir;
}RetornoInsere;

//Função que inicializa a árvore

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

//Função SplitChildren
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

    //Colocando os valores do noParaDivisão para o nó irmão
    for (int j = 0; j < T; j++)
    {
        novoIrmao -> chave[j] = noParaDivisao -> chave[T + j]; //Está passando os valores depois da mediana para o novo nó
    }

    if (noParaDivisao -> ehFolha == 0)
    {
        for (int j = 0; j < T; j++)
        {
            novoIrmao -> filho[j] = noParaDivisao -> filho[T + j]; //Ou seja, se o nó que está passando pela divisão não for folha, seus filhos de T + 1 devem ser passado para o noIrmao
        }
    }

    noParaDivisao -> numeroDeChaves = T - 1;

    //Alterando o nó pai
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

//Função split para o Método Tradicional de Inserção, ele só serve para divir
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

    //Copia as chaves à direita da mediana para o novo nó
    for (int j = 0; j < T - 1; j++)
    {
        chaveENovoNo.noParaSubir -> chave[j] = noParaDivisao -> chave[T + j]; //Está passando os valores depois da mediana para o novo nó
    }

    if (noParaDivisao -> ehFolha == 0)
    {
        for (int j = 0; j < T; j++)
        {
            chaveENovoNo.noParaSubir -> filho[j] = noParaDivisao -> filho[T + j];//Ou seja, se o nó que está passando pela divisão não for folha, seus filhos de T + 1 devem ser passado para o noIrmao
            noParaDivisao -> filho[T + j] = NULL;
        }

    }

    noParaDivisao -> numeroDeChaves = T - 1;

    chaveENovoNo.chaveParaSubir = noParaDivisao -> chave[T - 1];

    return chaveENovoNo;
}

//Função principal que gerencia o processo de inserção tradicional
ArvoreB insereTradicionalNaArvoreB (ArvoreB raiz, int chaveParaInserir)
{
    //Caso 1: a Árvore está vazia
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

        //Inicializando todos os nós filhos
        for(int i = 0; i < MAX + 1; i++)
        {
            raiz -> filho[i] = NULL;
        }

        return raiz;
    }

    //Caso 2: a Árvore não está vazia, irei inicializar a inserção utilizando recursão para a busca, para que o split possa acontecer
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

        //Agora, passando os nós que ela deverá apontar
        novaRaiz -> filho[0] = raiz;
        novaRaiz -> filho[1] = chaveENovoNo.noParaSubir;

        return novaRaiz;
    }

    return raiz;
}


