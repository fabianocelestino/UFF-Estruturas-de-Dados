#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

typedef struct no{ // estrutura padrao de node
    string info;
    no* next;
}NO;

typedef struct fila{ // estrutura padrao de fila
    NO* inicio;
    NO* fim;
    int tamanho;
}FILA;

// assinaturas das funcoes utilizadas

void inserirNo(FILA* , string);

FILA* criarFila();

void criarBuckets(FILA** bucket);

void gerarTabela(FILA* f, int quantidade, int qdigitos);

bool estaVazia(FILA* f);

int tamanho(FILA* f);

void inserirNo(FILA* f, string val);

void remover(FILA* f);

void imprimir(FILA* f);

void printBuckets(FILA** bucket);

void cleanAllBuckets(FILA** bucket);

void trocarValores(FILA* f, FILA** bucket);

void radixSort(FILA* tabela, FILA** bucket, int n, int d);

#endif