#include <iostream>
#include <string> 
#include <cmath>
using namespace std;

#include "dataStructures.h"

FILA* criarFila(){ // cria uma nova fila vazia
    FILA* fila = new FILA;
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tamanho = 0;
    return fila;
}

void criarBuckets(FILA** bucket){ // cria 10 filas no vetor de baldes para ordenar os elementos
    for(int i = 0; i < 10 ; i++){
        bucket[i] = criarFila();
    }
}

void gerarTabela(FILA* f, int quantidade, int qdigitos){ //Gera n numeros aleatórios
    int i = 0;
    long int random = 0;
    
    int referenciaQuantDigitos = pow(10, qdigitos); // variável que será referencia para o intervalo permitido para geracao dos numeros. 
                                                    // Caso resultado seja 10, será gerado numeros com até 1 dígito - de 0 a 9.
                                                    // Caso 100, será gerado numeros com com até 2 dígitos - de 0 a 99.
                                                    // Caso 1000, será gerado numeros com com até 3  dígitos - ntervalo de 0 a 999
    string temp = "";
    
    srand(time(0));         
    
    while(i < quantidade){
        random = rand() % referenciaQuantDigitos; // rand() gera numeros de 0 a, no minimo, 32767; Utilizado em conjuto com o operador MOD irá retornar
                                                  // para randon um valor entre o intervalo definido segundo o comentário da variavel referenciaQuantDigitos 
        temp = to_string(random);
        
        if(temp.length()<qdigitos){                 //realiza uma manipulação de string verificando se o numeros possui menos digitos que o
   	            while(temp.length() < qdigitos){    // especificado pelo parametro quantidade. EM caso afirmativo, insere o's a esquerda tantos
   	                temp = "0"+temp;                // quantos sejam necesários.
   	            }
   	        }
        inserirNo(f, temp);                         // insere na fila o elemento gerado
        i++;
    }
}

bool estaVazia(FILA* f){ // verifica se a fila esta vazia - condicao booleana
    return f->tamanho < 1;
}

int tamanho(FILA* f){ // retorna o tamanho da fila
    return f->tamanho;
}

void inserirNo(FILA* f, string val){ // insere novo node na fila
    // aloca novo node
    NO* no = new NO;
    no->info = val;
    no->next = NULL;
    // se fila vazia - aloca no inicio
    if(estaVazia(f)){
        f->inicio = f->fim = no;
        f->tamanho++;
        return;
    }
    // senao - aloca como proximo elemento
    f->fim->next = no;
    f->fim = no;
    f->tamanho++;
}

void remover(FILA* f){ // remove elemento da fila
    NO* aux;
    // verifica se fila vazia antes da remocao
    if(!estaVazia(f)){
        aux = f->inicio;
        f->inicio = f->inicio->next;
        f->tamanho--;
        free(aux);
        return;
    }
    cout << "Lista Vazia.\n";
}

void imprimir(FILA* f){ // imprime elementos de uma fila
    // verifica se fila vazia antes da impressao
    if(estaVazia(f)){
        cout << "\n";
        return;
    }
    int i = 1;
    NO* no =  f->inicio;
    // node auxiliar percorre todos os elementos da fila imprimindo-os
    while(no != NULL){
        cout  << no->info << " ";
        no = no->next;
    }
    cout << "\n";
}

void printBuckets(FILA** bucket){ // imprime os elementos dos baldes - imprime todos os elementos de todas as filas
    for(int i = 0; i < 10 ; i++){
        cout<< "Fila["<< i << "]: ";
        imprimir(bucket[i]);
    }
}

void cleanAllBuckets(FILA** bucket){ // exclui todos os baldes
   NO* no;
   // ponteiro auxiliar 'no' recebe a posicao pro primeiro elemento de cada balde
   for(int k = 0; k < 10; k++){
       no = bucket[k]->inicio;
       // ponteiro auxiliar 'no' percorre todos os elementos do balde indicado por 'k' e os envia para a funcao 'remover' esvaziando-o
       while(no != NULL){
           remover(bucket[k]);
           no = no->next;
       }
   }
}

void trocarValores(FILA* f, FILA** bucket){ // substitui os elementos da fila original pelos elementos ordenados pelos baldes
    NO* nofila = f->inicio; // ponteiro auxiliar 'noFila' recebe a posicao inicial da fila original
    NO* noBucket;
    int i = 0;
    // ponteiro auxiliar 'noBucket' percorre os baldes indicados por 'i' e os percorre
    // enviando os elementos do respectivo balde ja em processo de ordenacao de volta para a fila original
    while(i < 10){
        noBucket = bucket[i]->inicio;
        while(noBucket != NULL){
            nofila->info = noBucket->info;
            nofila = nofila->next;
            noBucket = noBucket->next;
        }       
        i++;
    }
}

void radixSort(FILA* tabela, FILA** bucket, int n, int d){
    int tamanhoDoNumero = d; // define quantos digitos serao gerados para cada elemento
    int quantDeElementos = n; // define quantos elementos serao gerados na lista
    
   	NO* elemento = new NO; // aloca novo node
   	
    elemento = tabela->inicio;
   	int iteracao = 1;
    int contador = quantDeElementos-1;
    // seta o digito respectivo para a ordenacao dos elementos - LSD
    for(int i = tamanhoDoNumero-1; i >= 0; i--){
   	    cout << "\nTabela: ";
   	    imprimir(tabela);
   	    // distribui os elementos da lista
        // adicionando-os nos baldes com base no respectivo digito que foi setado anteriormente
        for(int j = 0; j < quantDeElementos; j++){
   	        inserirNo(bucket[elemento->info[i]-48], elemento->info); // indice por manipulacao do char via tabela ascii
            elemento = elemento->next;
   	    }
        
   	    cout << "\nIteracao "<<iteracao<<": "<<iteracao<<"a distribuicao\n";
   	    printBuckets(bucket);
   	    
        trocarValores(tabela, bucket);
        cleanAllBuckets(bucket); 
        iteracao++;
   	    
        elemento = tabela->inicio;
   	}
}