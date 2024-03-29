#ifndef GRAFOLISTA_H
#define GRAFOLISTA_H

#define MAX 100

#define false 0
#define true 1

#define _NAO_VISITADO 0
#define _VISITADO_ 1
#define _COMPLETO_ 2


typedef int bool;
typedef struct _aresta Aresta;
typedef struct _vertice Vertice;
typedef struct _grafo Grafo;
typedef struct _usuario Usuario;


struct _grafo {
    Vertice *vertices;
    int numVertices;
};

struct _usuario{
    int id;
    bool logged;
    char nome[MAX];
    char senha[MAX];
    int  idade;
    char cidade[MAX];
    char consoleFavorito[MAX];
    char generoFilme[MAX];
    char areaAtuacao[MAX];
    char timeEsportivo[MAX];
    Vertice** solicitacoesAmizade;
    int nSolicitacoes;
};

struct _aresta {
    Usuario usuarioAmigo;
    float grauAfinidade;
    struct _aresta *prox;
};

struct _vertice {
    Usuario usuario;
    int num_arestas;
	struct _vertice *prox;
    Aresta *primeiro_elem;
    Aresta *ultimo_elem;
};

Grafo *criar_grafo();
void inserir_vertice(Grafo *G, Usuario novoUsuario);
Vertice *buscar_vert(Grafo *G, char word[]);
void inserir_aresta(Grafo *G, Vertice* Va, Vertice* Vb);
void imprime_grafo(Grafo *G);
float checarPlagio(Grafo *textoA, Grafo *textoB);
int contarArestas(Grafo* G);
Aresta* buscar_aresta(Vertice* V, char* nome, Aresta** ant);
void removerAresta(Grafo* G,Vertice* user, Aresta* toBeRemoved);
void destroiGrafo(Grafo* G);
int bfs(Grafo* G, Vertice* startVertex, int searchId );
#endif