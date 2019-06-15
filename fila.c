#include "fila.h"
#include <stdlib.h>
#include <stdio.h>

Fila* criaFila(){
    Fila* f = calloc(1, sizeof(Fila));
    f->total=0;
    f->ini=NULL;
    f->fim = f->ini;
}

NoFila* criaNo(Vertice *v){
    NoFila* new = calloc(1, sizeof(NoFila));
    new->vert = v;
    new->prox = NULL;
}

void enqueue(Fila* f, Vertice* v){
    NoFila* new = criaNo(v);
    if(f->total==0){
        f->ini = new;
    }else{
        f->fim->prox = new;
    }
    f->fim = new;
    f->total++;
}

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

void freeFila(Fila *f){
    NoFila* aux = f->ini;
    while (aux){
        NoFila* temp = aux;
        aux = aux->prox;
        free(temp);
    }
    
}