#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafolista.h"
#define MAX 25

struct _aresta {
    char nome[MAX];
    struct _aresta *prox;
};

struct _vertice {
    char nome[MAX];
    char classe[MAX];
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
void inserir_vertice(Grafo *G, char nome[], char classe[]){
    Vertice *V = (Vertice *) malloc(sizeof(Vertice));
    strcpy(V->nome, nome);
    strcpy(V->classe, classe);
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

/*Função buscar_vert: verifica se a palavra ja esta na lista de vertices;
@argumentos: ponteiro para grafo G e string da palavra;
@retorno: retorna, se obteve sucesso, um ponteiro para o vertice;	
*/
Vertice *buscar_vert(Grafo *G, char word[]) {
	if(G != NULL){
        Vertice *V = G->vertices;
		while(V != NULL){
            if(!(strcmp(V->nome,word))) return (V);
            V = V->prox;
        }
	}
    return NULL;	
}

/*Função inserir_aresta: insere uma palavra na lista de arestas de um vertice;
@argumentos: ponteiro para grafo G, string da palavra vertice e string da palavra aresta;
@retorno: retorna void;	
*/
void inserir_aresta(Grafo *G, char nome_vertice[], char nome_aresta[]){
    Vertice *V = buscar_vert(G, nome_vertice);
    if(V != NULL){
        Aresta *A = (Aresta*) malloc(sizeof(Aresta));
        strcpy(A->nome, nome_aresta);
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
                printf("        ->%s\n", A->nome);
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
            if(!strcmp(temp->nome, nome))
            {
                return temp;
            }
            temp = temp->prox;
        }
    }
    return NULL;
}


/*Funçao checarPlagio: Calcula a porcentagem de plágio de um texto
@argumentos: texto a ser analisado e texto original
@retorno: porcentagem do plagio entre os dois
*/
float checarPlagio(Grafo *textoA, Grafo *textoB)
{   
    Vertice *V = textoA->vertices, *tempV;
    Aresta *A;
    int relationCnt = 0, numEdges = 0;
    int wordCnt = 0;

    while(V != NULL)
    {    
        A = V->primeiro_elem;
        tempV = buscar_vert(textoB, V->nome);
        if(tempV != NULL) //achou a palavra no outro grafo
        {
            if(!strcmp(tempV->classe,V->classe)) //checa se a palavra igual tem a mesma classe gramatical 
            {
                wordCnt ++; //incrementa o contador de palavras iguais
                while (A != NULL) //checar quais outras palavras do texto a palavra em análise se relaciona
                {
                    numEdges++;
                    if(buscar_aresta(tempV, A->nome)) //se nao achar retorna null (falso)
                    {
                        relationCnt++;
                    }
                    A = A->prox;
                }
            }
        }
        V = V->prox;
    }
    // numEdges = contarArestas(textoA);
    // printf("word: %d, relation: %d, numberWords: %d, numberEdges: %d\n\n ",wordCnt, relationCnt, textoA->numVertices, numEdges);

    return ((float)relationCnt/(float)numEdges)*100; // calcula e retorna a porcentagem de plágio
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