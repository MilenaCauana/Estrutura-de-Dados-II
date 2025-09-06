//Implementando árvore B - Milena Cauana
//Primeiro irei fazer da minha cabeça e, depois, irei conferir com os materiais.
//Primeiro farei com ponteiros, depois mudo para arquivos binários
#include<stdlib.h>

#typedef MAX 20;

// ---- DEFININDO A ESTRUTURA DO NÓ ----
typedef struct No
{
    int n; //Número de chaves
    int folha; //Booleano
    int chave [MAX]; //Aqui, estou criando o vetor que armazenará os dados
    struct No *filhos[MAX + 1]; //Ponteiros para os filhos

}NoArvB, *raizArvB;

//Função de busca
/*
* Utilizarei recursão:
* - Parará quando achar;
* - Parará quando chegar em uma folha e não encontrar.
*/
int buscaArvB(raizArvB no, int busca)
{
    int i;

    for (i = 0; i < no.n; i++)
    {
        if (no.chave[i] == busca)
        {
            return no.chave[i];
        }
        if (busca < no.chave[i])
        {
            buscarArvB(no.filhos[i], busca);
        }
    }

    if (no.folha)
    {
        printf("Valor nao encontrado");
        return -1;
    }

    buscaArvB(no.filhos[i], busca);
}


