#ifndef GRAFOLISTA_H
#define GRAFOLISTA_H

typedef struct _aresta Aresta;
typedef struct _vertice Vertice;
typedef struct _grafo Grafo;

struct _grafo {
    Vertice *vertices;
    int numVertices;
};

Grafo *criar_grafo();
void inserir_vertice(Grafo *G, char nome[], char classe[]);
Vertice *buscar_vert(Grafo *G, char word[]);
void inserir_aresta(Grafo *G, char nome_vertice[], char nome_aresta[]);
void imprime_grafo(Grafo *G);
float checarPlagio(Grafo *textoA, Grafo *textoB);
int contarArestas(Grafo* G);

#endif