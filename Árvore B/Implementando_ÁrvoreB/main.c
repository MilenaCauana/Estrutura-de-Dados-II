#include <stdio.h>
#include <stdlib.h>

#include "avoreB.h"

int main()
{
    int ordem, t, tFuncoes;
    ArvoreB produtos;

    printf("\n ...Inicializando Arvore...");
    produtos = inicializaArvore();

    //Verificando se foi inicializada direito
    if(produtos == NULL)
    {
        printf("\nERRO: nao foi possivel inicializar a arvore!");
        return -1;
    }
    printf("\nArvore Inicializada!");

    printf("Para comecarmos, diga o tamanho de cada no: ");
    scanf("%d", &ordem);

    t = (ordem + 1)/2;
    tFuncoes = t + 1;

    printf("\n--- ENTRANDO NO SISTEMA DA LOJA ---");
    printf("\nBem-vindo!");

    int x;
    do
    {
        printf("\n\nEscolha uma das opcoes: ");
        printf("\n1) Visualizar todos os produtos;");
        printf("\n2) Buscar produto especifico;");
        printf("\n3) Inserir produto;");
        printf("\n4) Remover produto;");
        printf("\n-1) SAIR;");

        scanf("%d", &x);
        fflush();

        switch(x)
        {
            case 1:
                imprimirArvore(produtos);
                break;

            case 2:
                int codigoDeBarras;
                RetornoBusca infoProdutoBusca;

                printf("\nCodigo de Barras: ")
                scanf("%d", &codigoDeBarras);

                infoProdutoBusca = buscaArvBBuscaBinaria(produtos, codigoDeBarras);

                if(infoProdutoBusca.noEncotrado == NULL)
                {
                    break;
                }

                imprimirProduto(infoProdutoBusca.noEncotrado -> chave[infoProdutoBusca.indiceChave]);

            case 3:
                Produto produto;
                RetornoBusca infoProdutoBusca;

                printf("\n\n --- ADICIONAR PRODUTO ---");

                int y, codigoDeBarras;
                do
                {
                    printf("\nO produto ja existe na loja?");
                    printf("\n1) Sim.");
                    printf("\n2) Nao.");

                }while (y != 1 || y != 2)

                if (y == 1)
                {
                    printf("\n\nADICIONAR PRODUTO EXISTENTE:");

                    printf("\nCodigo de Barras: ");
                    scanf("%d", &codigoDeBarras);
                    fflush();

                    infoProdutoBusca = buscaArvBBuscaBinaria(produtos, codigoDeBarras);

                    if(infoProdutoBusca.noEncotrado == NULL)
                    {
                        printf("\nTente novamente!");
                        break;
                    }

                    produto = infoProdutoBusca.noEncotrado -> chave[infoProdutoBusca.indiceChave];

                    int quantidadeSomar;
                    printf("\nQuantidade do produto: ");
                    scanf("%d", &quantidadeSomar);
                    fflush();

                    produto.quantidade += quantidadeSomar;

                    printf("\n\nPRODUTO ADICIONADO COM SUCESSO!");
                }

                if (x == 2)
                {
                    printf("\nNome do Produto: ");
                    scanf("%s", produto.nome);

                    printf("\nCodigo de Barras: ");
                    scanf("%d", &produto.codigoDeBarras);
                    fflush();

                    produto.estaDisponivel = 1;

                    printf("Quantidade do Produto: ");
                    scanf("%d", &produto.quantidade);
                    fflush();

                    printf("\nDescricao: ");
                    scanf("%s", produto.descricao);

                    produtos = insereArvoreB(produtos, produto);
                }

                break;

            case 4:
                printf("\n\nREMOVER PRODUTO");
                int codigoDeBarrasRemov;

                printf("\nCodigo de Barras: ");
                scanf("%d", &codigoDeBarrasRemov);
                fflush();

                removeArvoreB(produtos, codigoDeBarrasRemov);

                break;
        }

    }while (x != -1);

    printf("\nTchau!")
    printf("\nFinalizando...");
    desfazArvore(produtos);

return 0;
}
