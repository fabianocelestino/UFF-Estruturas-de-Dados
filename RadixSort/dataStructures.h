#include <iostream>
#include <string> 
#include <cmath>
using namespace std;

typedef struct no{
    int info;
    no* next;
}NO;
typedef struct fila{
    NO* inicio;
    NO* fim;
    int tamanho;
}FILA;
void inserirNo(FILA* , int);

FILA* criarFila(){
    FILA* fila = new FILA;
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tamanho = 0;
    return fila;
}

void criarBuckets(FILA** bucket){
    for(int i = 0; i < 10 ; i++){
        bucket[i] = criarFila();
    }
    
}
void gerarTabela(FILA* f, int quantidade, int qdigitos){
    int i = 0;
    long int random = 0;
    int referenciaQuantDigitos = pow(10, qdigitos);
    srand(time(0));
    while(i < quantidade){
        random = rand() % referenciaQuantDigitos;
        inserirNo(f, random);
        i++;
    }
}

bool estaVazia(FILA* f){
    return f->tamanho < 1;
}
int tamanho(FILA* f){
    return f->tamanho;
}
void inserirNo(FILA* f, int val){
    NO* no = new NO;
    no->info = val;
    no->next = NULL;
    if(estaVazia(f)){
        f->inicio = f->fim = no;
        f->tamanho++;
        return;
    }
    if(f->tamanho == 1){
        f->inicio->next = no;
        //no->next = NULL;
        f->fim = no;
        f->tamanho++;
        return;
    }
    f->fim->next = no;
    f->fim = no;
    f->tamanho++;
   
}
void remover(FILA* f){
    NO* aux;
    if(!estaVazia(f)){
        aux = f->inicio;
        f->inicio = f->inicio->next;
        f->tamanho--;
        free(aux);
        return;
    }
    cout << "Lista Vazia.\n";
}

void imprimir(FILA* f){
    
    if(estaVazia(f)){
        cout << "\n";
        return;
    }
    int i = 1;
    NO* no =  f->inicio;
    while(no != NULL){
        cout  << no->info << " ";
        no = no->next;
    }
    cout << "\n";
}

int pegarMaior(FILA* f){
    NO* no = f->inicio;
    int maior = no->info;
    while(no != NULL){
        if(no->info > maior){
            maior = no->info;
        }
        no = no->next;
    }
    return maior;
}

void printBuckets(FILA** bucket){
    for(int i = 0; i < 10 ; i++){
        cout<< "Fila["<< i << "]: ";
        imprimir(bucket[i]);
    }
}

void cleanAllBuckets(FILA** bucket){  // exclui todos os buckets
   NO* no;
   
   for(int k = 0; k < 10; k++){
       no = bucket[k]->inicio;
       while(no != NULL){
           remover(bucket[k]);
           no = no->next;
       }
   }
    
}

void trocarValores(FILA* f, FILA** bucket){ // alterar os valores da fila original com os valores dos bucktes
    NO* nofila = f->inicio;
    NO* noBucket;
    
    int indexBucket = 0, i = 0;
    while(i < 10){
        noBucket = bucket[i]->inicio;
        while(noBucket != NULL){
            nofila->info =  noBucket->info;
            nofila = nofila->next;
            noBucket = noBucket->next;
        }
        
        i++;
    }
}

void radixSort(FILA* tabela, FILA** bucket){
    int tamanhoDoNumero = to_string(pegarMaior(tabela)).length();
   	NO* elemento = new NO;
   	elemento = tabela->inicio;
   	string temp = "";
   	int info;
   	int iteracao = 1, contador = tamanho(tabela)-1;
   	
    for(int i = tamanhoDoNumero-1; i >= 0; i--){
   	    cout << "\nTabela: ";
   	    imprimir(tabela);
   	    
   	    for(int j = 0; j < tamanho(tabela); j++){
   	        info = elemento->info;
   	        temp = to_string(info);
   	        if(temp.length()<tamanhoDoNumero){
   	            while(temp.length() < tamanhoDoNumero){
   	                temp = "0"+temp;
   	            }
   	        }
   	        
   	        inserirNo(bucket[temp[i]-48], info);
            elemento = elemento->next;
   	    }
   	    cout << "\nIteração "<<iteracao<<": "<<iteracao<<"a distribuição\n";
   	    printBuckets(bucket);
   	    trocarValores(tabela, bucket);
   	    cleanAllBuckets(bucket); 
   	    iteracao++;
   	    elemento = tabela->inicio;
   	}
}

