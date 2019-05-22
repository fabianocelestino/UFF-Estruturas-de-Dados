/*

Authors:
        Fabiano Celestino
        Paulo Jr Niche    
        
        
                        Universidade Federal Fluminense
                            Sistemas de Informacao
                              Estruturas de Dados
                              
        Implementacao do algoritmo de ordenacao por distribuicao - Radix sort
        
        Enunciado: 
            Implemente um programa que recebe como entrada inteiros N e D e gera aleatoriamente
            uma lista com elementos com exatamente D digitos(o digitomais significante - MSD - pode ser 0).
            O programa deve listar os N elementos gerados e a seguir, quando solicitado, executar a ordenacao por distribuicao.
            O programa deve imprimir, a cada iteracao, o estado corrente das B filas temporarias(buckets), bem como
            o estado corrente da lista de elementos a ser ordenada.
            
            Considerem B = 10;
*/

#include <iostream>
#include <string> 
#include <cmath>
using namespace std;

#include "dataStructures.h"

int main(){
  // cria 10 baldes para ordenacao dos elementos - digitos de 0 a 9
  FILA *bucket[10];
  criarBuckets(bucket);
  
  // cria a fila original para receber os elementos a serem ordenados
  FILA *tabela = criarFila();

  int n, d;
  cout << "Informe a quantidade de elementos a serem gerados... ";
  cin >> n;

  cout << "Informe a quantidade maxima de digitos de cada elemento... ";
  cin >> d;

  // ???
  gerarTabela(tabela, n, d);
    
  // funcao para executar a ordenacao por distribuicao
  radixSort(tabela, bucket, n, d);

  cout << "\n";
  cout << "Tabela: ";
  imprimir(tabela);

  return 0;
}