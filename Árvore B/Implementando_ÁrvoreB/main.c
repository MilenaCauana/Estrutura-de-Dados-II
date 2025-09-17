#include <stdio.h>
#include <stdlib.h>

#include "avoreB.h"

int main()
{
    int ordem, t;
    ArvoreB produtos;

    printf("\n ...Inicializando Arvore...");
    produtos = inicializaArvore();

    //Verificando se foi inicializada direito
    if(produtos == NULL)
    {
        printf("\nArvore Inicializada!");
    } else
    {
        printf("\nERRO: Nao foi possivel inicializar a arvore!");
        return -1;
    }

    printf("\n\n\nPara comecarmos, diga o tamanho de cada no: ");
    scanf("%d", &ordem);
    fflush(stdin);

    t = (ordem + 1)/2;

    printf("\n--- ENTRANDO NO SISTEMA DA LOJA ---");
    printf("\nBem-vindo!");

    int x;
    int codigoDeBarras;
    RetornoBusca infoProdutoBusca;
    Produto produto;

    do
    {
        printf("\n\nEscolha uma das opcoes: ");
        printf("\n1) Visualizar todos os produtos;");
        printf("\n2) Buscar produto especifico;");
        printf("\n3) Inserir produto;");
        printf("\n4) Remover produto;");
        printf("\n5) Remover quantidade de produto;");
        printf("\n-1) SAIR;");
        printf("\nOpcao: ");

        scanf("%d", &x);
        fflush(stdin);

        switch(x)
        {
            case 1:
                if (produtos == NULL)
                {
                    printf("\nNao tem produtos!");
                    break;
                }

                imprimirArvore(produtos);
                break;

            case 2:
                if (produtos == NULL)
                {
                    printf("\nNao tem produtos!");
                    break;
                }

                printf("\nCodigo de Barras: ");
                scanf("%d", &codigoDeBarras);
                fflush(stdin);

                infoProdutoBusca = buscaArvBBuscaBinaria(produtos, codigoDeBarras);

                if(infoProdutoBusca.noEncontrado == NULL)
                {
                    break;
                }

                imprimirProduto(infoProdutoBusca.noEncontrado -> chave[infoProdutoBusca.indiceChave]);
                break;

            case 3:
                printf("\n\n --- ADICIONAR PRODUTO ---");

                int y = 0;
                do
                {
                    printf("\nO produto ja existe na loja?");
                    printf("\n1) Sim (Adicionar ao estoque existente)");
                    printf("\n2) Nao (Cadastrar novo produto)");
                    printf("\nOpcao: ");
                    scanf("%d", &y);
                    fflush(stdin);

                    if(y != 1 && y != 2)
                    {
                        printf("\nOpcao Invalida, tente novamente.");
                    }

                }while (y != 1 && y != 2);

                if (y == 1)
                {
                    printf("\n\nADICIONAR PRODUTO EXISTENTE:");

                    if (produtos == NULL)
                    {
                        printf("\nNao tem produtos!");
                        printf("\nAdicione um novo produto.");
                        break;
                    }

                    printf("\nCodigo de Barras: ");
                    scanf("%d", &codigoDeBarras);
                    fflush(stdin);

                    infoProdutoBusca = buscaArvBBuscaBinaria(produtos, codigoDeBarras);

                    if(infoProdutoBusca.noEncontrado == NULL)
                    {
                        printf("\nTente novamente!");
                        break;
                    }

                    printf("\nProduto: %s", infoProdutoBusca.noEncontrado -> chave[infoProdutoBusca.indiceChave].nome);
                    int quantidadeSomar;
                    printf("\nQuantidade do produto: ");
                    scanf("%d", &quantidadeSomar);
                    fflush(stdin);

                    infoProdutoBusca.noEncontrado -> chave[infoProdutoBusca.indiceChave].quantidade += quantidadeSomar;

                    printf("\n\nPRODUTO ADICIONADO COM SUCESSO!");

                    imprimirProduto(infoProdutoBusca.noEncontrado -> chave[infoProdutoBusca.indiceChave]);
                    break;
                }

                if (y == 2)
                {
                    printf("\n\nCADASTRAR NOVO PRODUTO");
                    printf("\nNome do Produto: ");
                    scanf("%s", produto.nome);
                    fflush(stdin);

                    printf("\nCodigo de Barras: ");
                    scanf("%d", &produto.codigoDeBarras);
                    fflush(stdin);
                    printf("\n");

                    produto.estaDisponivel = 1;

                    printf("Quantidade do Produto: ");
                    scanf("%d", &produto.quantidade);
                    fflush(stdin);

                    printf("\nDescricao: ");
                    scanf("%s", produto.descricao);
                    fflush(stdin);

                    printf("\nValor: ");
                    scanf("%f", &produto.valor);
                    fflush(stdin);

                    produtos = InsereArvoreB(produtos, produto, t);
                }

                break;

            case 4:
                printf("\n\nREMOVER PRODUTO");

                if (produtos == NULL)
                {
                    printf("\nNao tem produtos!");
                    break;
                }

                int codigoDeBarrasRemov;

                printf("\nCodigo de Barras: ");
                scanf("%d", &codigoDeBarrasRemov);
                fflush(stdin);

                int foiRemovido = removeArvoreB(produtos, codigoDeBarrasRemov, t);
                if(foiRemovido)
                {
                    printf("\nProduto removido com sucesso!");
                } else
                {
                    printf("\nFalha ao remover produto.");
                }

                break;

            case 5:
                printf("\n\nREMOVER QUANTIDADE DE PRODUTO:");

                if (produtos == NULL)
                {
                    printf("\nNao tem produtos!");
                    break;
                }

                printf("\nCodigo de Barras: ");
                scanf("%d", &codigoDeBarras);
                fflush(stdin);

                infoProdutoBusca = buscaArvBBuscaBinaria(produtos, codigoDeBarras);

                if(infoProdutoBusca.noEncontrado == NULL)
                {
                    printf("\nTente novamente!");
                    break;
                }


                int quantidadeSomar;
                printf("\nQuantidade que será removida: ");
                scanf("%d", &quantidadeSomar);
                fflush(stdin);

                infoProdutoBusca.noEncontrado -> chave[infoProdutoBusca.indiceChave].quantidade -= quantidadeSomar;

                printf("\n\nPRODUTO ADICIONADO COM SUCESSO!");

                imprimirProduto(infoProdutoBusca.noEncontrado -> chave[infoProdutoBusca.indiceChave]);
                break;
        }

    }while (x != -1);

    printf("\nTchau!");
    printf("\nFinalizando...\n");
    desfazArvore(produtos);

return 0;
}
