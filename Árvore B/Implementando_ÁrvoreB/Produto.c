#include<stdlib.h>
#include<stdio.h>

#include "Produto.h"

void imprimirProduto(Produto produto)
{
    printf("\n\n --- %c ----", produto.nome);
    printf("\nCódigo de Barras: %d", produto.codigoDeBarras);
    printf("\nEsta Disponivel: ");
    if(produto.estaDisponivel)
    {
        printf("Sim");
    }else
    {
        printf("Nao");
    }
    printf("\nQuantidade: %d", produto.quantidade);
    printf("\nDescricao: %c", produto.descricao);
}

#include "Produto.h"
