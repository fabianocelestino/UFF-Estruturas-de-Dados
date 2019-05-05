/*
                        Universidade Federal Fluminense
                            Sistemas de Informação
                              Estruturas de Dados
                              
        Implementação do algoritmo de ordenação por distribuição - Radix sort
        
        Enunciado: 
            Implemente um programa que recebe como entrada inteiros N e D e gera aleatoriamente
        uma lista com elementos com exatamente D digitos(o digitomais significante - MSD - pode ser 0).
            O programa deve listar os N elementos gerados e a seguir, quando solicitado, executar a ordenação por distribuição.
            O programa deve imprimir, a cada iteração, o estado corrente das B filas temporárias(buckets), bem como
        o estado corrente da lista de elementos a ser ordenada.    
        Considerem B = 10;
*/

#include "dataStructures.h"

int main()
{
    FILA* bucket[10];
    criarBuckets(bucket);
    
    FILA* tabela = criarFila(); 
    gerarTabela(tabela,10 , 4);

    radixSort(tabela, bucket);
   	
   	cout << "\n";
   	cout << "Tabela: ";
    imprimir(tabela);
    
    return 0;
}


    




