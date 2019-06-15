#ifndef FILA_H
#define FILA_H

#include "grafolista.h"

typedef struct no{
    Vertice* vert;
    struct no* prox;
}NoFila;

typedef struct fila{
    NoFila* ini, *fim;
    int total;
}Fila;



Fila* criaFila();
void enqueue(Fila* f, Vertice* v);
Vertice* dequeue(Fila* f);
void freeFila(Fila *f);
#endif