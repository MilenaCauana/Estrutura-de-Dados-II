#ifndef PRODUTO_H
#define PRODUTO_H

// ---- ESTRUTURA DO PRODUTO ----
typedef struct
{
    char nome[50];
    int codigoDeBarras;
    int estaDisponivel;
    int quantidade;
    char descricao[1000];
    float valor;

}Produto;


// FUNÇÕES
void imprimirProduto(Produto produto);

#endif // PRODUTO_H

