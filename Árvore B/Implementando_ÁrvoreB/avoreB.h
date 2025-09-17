#ifndef ARVOREB_H
#define ARVOREB_H

#define MAX 3
#define T (MAX + 1)/2 //Aqui, estou definindo t, que será utilizado para fazer a conta do máximo e do mínimo de chaves que um nó deve ter

#include "Produto.h"

// ---- DEFININDO A ESTRUTURA DO NÓ ----
typedef struct No
{
    int numeroDeChaves;
    int ehFolha;
    Produto *chave;
    struct No **filho;

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

//Funções
ArvoreB inicializaArvore();

RetornoBusca buscaArvBBuscaBinaria(ArvoreB raiz, int chaveBusca);

#endif // ARVOREB_H
