#include "fila.h"
#include <stdlib.h>
#include <stdio.h>

/*
    Função criaFila: aloca espaço necessário e inicializa valores da fila
    Retorono:
    Fila* f -> endereço da nova fila
 */
Fila* criaFila(){
    Fila* f = calloc(1, sizeof(Fila));
    f->total=0;
    f->ini=NULL;
    f->fim = f->ini;
}

/*
    Função criaFila: aloca espaço necessário e inicializa valores do nó
    Retorono:
    NoFila* new -> endereço do novo nó
 */
NoFila* criaNo(Vertice *v){
    NoFila* new = calloc(1, sizeof(NoFila));
    new->vert = v;
    new->prox = NULL;
}

/*
    Função enqueue: insere elemento no final da fila
    Parâmetros:
    Fila *f -> endereço da fila
    Vertice* v -> elemento a ser inserido
 */
void enqueue(Fila* f, Vertice* v){
    NoFila* new = criaNo(v);
    if(f->total==0){//Caso fila esteja vazia
        f->ini = new;
    }else{
        f->fim->prox = new;
    }
    f->fim = new;
    f->total++;
}

/*
    Função dequeue: Retira elemento do início da fila e o retorna
    Parâmetro:
    Fila* f -> endereço da fila
    Retorno:
    NULL caso fila esteja vazia
    Vertice* vAux -> elemento retirado
 */
Vertice* dequeue(Fila* f){
    if(f->total){
        NoFila* aux = f->ini;
        f->ini = aux->prox;
        f->total--;
        Vertice* vAux = aux->vert;
        free(aux);
        return vAux;
    }
    return NULL;
}

/*
    Função freeFila: libera toda memória alocada pela fila
    Parâmetros:
    Fila* f -> endereço da fila
 */
void freeFila(Fila *f){
    NoFila* aux = f->ini;
    while (aux){
        NoFila* temp = aux;
        aux = aux->prox;
        free(temp);
    }
    free(f);
}