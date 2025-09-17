#ifndef ARVOREB_H
#define ARVOREB_H

#define MAX 3
#define T (MAX + 1)/2 //Aqui, estou definindo t, que ser� utilizado para fazer a conta do m�ximo e do m�nimo de chaves que um n� deve ter

#include "Produto.h"

// ---- DEFININDO A ESTRUTURA DO N� ----
typedef struct No
{
    int numeroDeChaves;
    int ehFolha;
    Produto *chave;
    struct No **filho;

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

//Fun��es
ArvoreB inicializaArvore();

RetornoBusca buscaArvBBuscaBinaria(ArvoreB raiz, int chaveBusca);

#endif // ARVOREB_H
