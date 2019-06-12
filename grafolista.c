#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafolista.h"




typedef struct _usuario{
    char nome[MAX];
    int  idade;
    char cidade[MAX];
    char consoleFavorito[MAX];
    char generoFilme[MAX];
    char areaAtuacao[MAX];
    char timeEsportivo[MAX];
};



struct _aresta {
    char nomeAmizade[MAX];
    int grauAfinidade;
    struct _aresta *prox;
};

struct _vertice {
    char nome[MAX];
    char classe[MAX];
    Usuario usuario;
    int num_arestas;
	struct _vertice *prox;
    Aresta *primeiro_elem;
    Aresta *ultimo_elem;
};



/*Função criar_grafo: cria um grafo;
@argumentos: void;
@retorno: retorna, se obteve sucesso, um ponteiro para o grafo criado;	
*/
Grafo *criar_grafo(){
	Grafo *G = (Grafo *)malloc(sizeof(Grafo));
	if(G == NULL){
		return NULL;
	}
	G->numVertices = 0;
	G->vertices = NULL;
	return G;
}

/*Função inserir_vertice: insere uma nova palavra na lista de vertices;
@argumentos: ponteiro para grafo G e string da palavra;
@retorno: void;	
*/
void inserir_vertice(Grafo *G, Usuario novoUsuario){
    Vertice *V = (Vertice *) malloc(sizeof(Vertice));


    strcpy(V->usuario.nome, novoUsuario.nome);
    V->usuario.idade = novoUsuario.idade;
    strcpy(V->usuario.cidade, novoUsuario.cidade );
    strcpy(V->usuario.consoleFavorito, novoUsuario.consoleFavorito );
    strcpy(V->usuario.generoFilme, novoUsuario.generoFilme );
    strcpy(V->usuario.areaAtuacao, novoUsuario.areaAtuacao );
    strcpy(V->usuario.timeEsportivo, novoUsuario.timeEsportivo );


    G->numVertices++;
    V->primeiro_elem = NULL;
    V->ultimo_elem = NULL;
    V->num_arestas = 0;
    if(G->vertices != NULL){
        V->prox = G->vertices;
    }else {
        V->prox = NULL;
    }
    G->vertices = V;
    
}

/*Função buscar_vert: verifica se um vertice ja esta na lista de vertices;
@argumentos: ponteiro para grafo G e string da palavra;
@retorno: retorna, se obteve sucesso, um ponteiro para o vertice;	
*/
Vertice *buscar_vert(Grafo *G, char nomeUsuario[]) {
	if(G != NULL){
        Vertice *V = G->vertices;
		while(V != NULL){
            if(!(strcmp(V->usuario.nome,nomeUsuario))) return (V);
            V = V->prox;
        }
	}
    return NULL;	
}

/*Função inserir_aresta: insere uma palavra na lista de arestas de um vertice;
@argumentos: ponteiro para grafo G, string da palavra vertice e string da palavra aresta;
@retorno: retorna void;	
*/
void inserir_aresta(Grafo *G, char nome_vertice[], char nome_aresta[]){ //**ajeitar isso aqui para não ser direcional
    Vertice *V = buscar_vert(G, nome_vertice);
    if(V != NULL){
        Aresta *A = (Aresta*) malloc(sizeof(Aresta));
        strcpy(A->nomeAmizade, nome_aresta);
        V->num_arestas++;
        if(V->primeiro_elem != NULL){
            A->prox = V->ultimo_elem->prox;
            V->ultimo_elem->prox = A;
        }
        else {
            V->primeiro_elem = A;
            V->ultimo_elem = A;
            A->prox = NULL;
        }
    }
    return;
}

/*Função imprime_grafo: imprime o grafo na tela;
@argumentos: ponteiro para grafo G;
@retorno: retorna void;	
*/
void imprime_grafo(Grafo *G) {
    if(G != NULL){
        Vertice *V = G->vertices;
        Aresta *A;
        printf("Grafo texto - %d vertices:\n", G->numVertices);
        while (V != NULL){
            A = V->primeiro_elem;
            printf("Vertice: %s, Classe Gram: %s - %d arestas\n", V->nome, V->classe, V->num_arestas);
            while (A != NULL){
                printf("        |\n");
                printf("        ->%s\n", A->nomeAmizade);
                A = A->prox;
            }
            V = V->prox;
        }
    }
    printf("FIM\n");
}

/*Função buscar_aresta: busca determinada aresta em um vértice
@argumentos: vértice em análise e nome do vertice de destino da aresta
@retorno: ponteiro para a aresta procurada; Caso não ache retorna null
*/
Aresta* buscar_aresta(Vertice* V, char* nome)
{
    if(V != NULL)
    {
        Aresta *temp = V->primeiro_elem;
        while(temp != NULL)
        {
            if(!strcmp(temp->nomeAmizade, nome))
            {
                return temp;
            }
            temp = temp->prox;
        }
    }
    return NULL;
}

/*Funçao contarArestas: conta a quantidade de arestas em todos os vertices de um grafo
@argumentos: grafo em análise
@retorno: quantidade das arestas
*/
int contarArestas(Grafo* G)
{
    int cntA = 0;
    Vertice *V;
    if(G != NULL){
        V = G->vertices;
		while(V != NULL){
            cntA += V->num_arestas;
            V = V->prox;
        }
	}
    return cntA;
}