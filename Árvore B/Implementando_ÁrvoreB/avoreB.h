#ifndef AVOREB_H
#define AVOREB_H

#include "Produto.h"

// ---- DEFININDO A ESTRUTURA DO NÓ ----
typedef struct No
{
    int numeroDeChaves;
    int ehFolha;
    Produto *chave;
    struct No **filho;

} NoArvB, *ArvoreB;

// Estrutura para o retorno da busca
typedef struct
{
    int indiceChave;
    ArvoreB noEncontrado; // Corrigido 'noEncotrado' para 'noEncontrado'
} RetornoBusca;

// Protótipos das Funções
ArvoreB inicializaArvore();

RetornoBusca buscaArvBBuscaBinaria(ArvoreB raiz, int chaveBusca);

void imprimirArvore(ArvoreB no);

ArvoreB InsereArvoreB(ArvoreB raiz, Produto produto, int t);

ArvoreB criarNo(int t);

int removeArvoreB(ArvoreB no, int chaveRemover, int t);

void desfazArvore(ArvoreB raiz);

#endif // AVOREB_H
