#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafolista.h"



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
void inserir_aresta(Grafo *G, Vertice* Va, Vertice* Vb){
    if(Va != NULL && Vb != NULL){
        Aresta *A = (Aresta*) malloc(sizeof(Aresta));
        A->usuarioAmigo = Vb->usuario;
        Va->num_arestas++;
        if(Va->primeiro_elem != NULL){
            A->prox = Va->ultimo_elem->prox;
            Va->ultimo_elem->prox = A;
        }
        else {
            Va->primeiro_elem = A;
            Va->ultimo_elem = A;
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
            printf("Vertice: %s, - %d arestas\n", V->usuario.nome, V->num_arestas);
            while (A != NULL){
                printf("        |\n");
                printf("        ->%s\n", A->usuarioAmigo.nome);
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
            if(!strcmp(temp->usuarioAmigo.nome, nome))
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