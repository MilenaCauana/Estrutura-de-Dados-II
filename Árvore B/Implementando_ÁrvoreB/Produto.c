#include<stdlib.h>
#include<stdio.h>

#include "Produto.h"

void imprimirProduto(Produto produto)
{
    printf("\n\n --- %s ----", produto.nome);
    printf("\nCodigo de Barras: %d", produto.codigoDeBarras);
    printf("\nEsta Disponivel: ");
    if(produto.estaDisponivel)
    {
        printf("Sim");
    }else
    {
        printf("Nao");
    }
    printf("\nQuantidade: %d", produto.quantidade);
    printf("\nDescricao: %s", produto.descricao);
    printf("\nValor: %.2f", produto.valor);
}

