#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafolista.h"
#include "fila.h"
#include "fileManagement.h"
#include "socialNetwork.h"



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

void loadAresta(Grafo* G, Vertice* user, char* buffer){
    char** nomesAmizades = split(buffer, ";\n");
    int i=0;
    while(nomesAmizades[i]){
        Vertice* aux = buscar_vert(G, nomesAmizades[i]);
        inserir_aresta(G, aux, user);
        inserir_aresta(G, user, aux);
        i++;
        free(aux);
    }
    free(nomesAmizades);
    
}

/*Função inserir_vertice: insere uma nova palavra na lista de vertices;
@argumentos: ponteiro para grafo G e string da palavra;
@retorno: void;	
*/
void inserir_vertice(Grafo *G, Usuario novoUsuario){
    Vertice *V = (Vertice *) malloc(sizeof(Vertice));
    strcpy(V->usuario.nome, novoUsuario.nome);
    strcpy(V->usuario.senha, novoUsuario.senha);
    V->usuario.idade = novoUsuario.idade;
    strcpy(V->usuario.cidade, novoUsuario.cidade );
    strcpy(V->usuario.consoleFavorito, novoUsuario.consoleFavorito );
    strcpy(V->usuario.generoFilme, novoUsuario.generoFilme );
    strcpy(V->usuario.areaAtuacao, novoUsuario.areaAtuacao );
    strcpy(V->usuario.timeEsportivo, novoUsuario.timeEsportivo );
    V->usuario.id = novoUsuario.id;
    V->usuario.nSolicitacoes=0;
    V->usuario.solicitacoesAmizade = NULL;
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

/*
Função buscar_vert: verifica se um vertice ja esta na lista de vertices;
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
        A->grauAfinidade = calculaAfinidade(G,Va, Vb);
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
        for (int j=0; j<G->numVertices; j++){
            A = V->primeiro_elem;
            printf("Vertice: %s, - %d arestas\n", V->usuario.nome, V->num_arestas);
            for (int i=0; i<V->num_arestas; i++){
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
Aresta* buscar_aresta(Vertice* V, char* nome, Aresta** ant)
{
    Aresta* anterior=NULL;
    if(V != NULL)
    {
        Aresta *temp = V->primeiro_elem;
        while(temp != NULL)
        {
            if(!strcmp(temp->usuarioAmigo.nome, nome))
            {
                *ant = anterior;
                return temp;
            }
            anterior = temp;
            temp = temp->prox;
        }
    }
    *ant = anterior;
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

/*
    Função removerAresta: remove as arestas entre 2 usuários
    Parâmetros:
    Grafo* G -> endereço do grafo
    Vertice* user -> usuário que deseja remover a amizade
    Aresta* toBeremoved -> primeira aresta a ser removida
 */
void removerAresta(Grafo* G,Vertice* user, Aresta* toBeRemoved){
    Aresta* ant1=NULL,*ant2=NULL;
    Vertice* user2 = buscar_vert(G, toBeRemoved->usuarioAmigo.nome);
    Aresta* aresta2 = buscar_aresta(user2, user->usuario.nome, &ant2);
    buscar_aresta(user, user2->usuario.nome, &ant1);
    if(toBeRemoved && aresta2){
        if(toBeRemoved->usuarioAmigo.id == user->primeiro_elem->usuarioAmigo.id){
            user->primeiro_elem = user->primeiro_elem->prox;
        }else{
            if(toBeRemoved->prox)
                ant1->prox = toBeRemoved->prox;
        }
        if(aresta2->usuarioAmigo.id == user2->primeiro_elem->usuarioAmigo.id){
            user2->primeiro_elem = user2->primeiro_elem->prox;
        }else{
            if(aresta2->prox)
                ant2->prox = aresta2->prox;
        }
        free(toBeRemoved);
        free(aresta2);
        user->num_arestas--;
        user2->num_arestas--;
    }
    
}




int bfs(Grafo* G, Vertice* startVertex, int searchId)//**  testar função 
{ 
    int nArestas, cnt = 0;
    
    Fila* q = criaFila();

    startVertex->status = _VISITADO_;
    enqueue(q, startVertex);
    
    while(q->ini != NULL)
    {   
        
        Vertice* auxV = dequeue(q);
        nArestas = auxV->num_arestas;
        Aresta* auxA = auxV->primeiro_elem;
        cnt++;
        for(int i = 0; i < nArestas; i++)
        {    
            Vertice* tempV = buscar_vert(G, auxA->usuarioAmigo.nome);
            if(tempV->usuario.id == searchId)
            {
                return 1/cnt;
            }     
            if(tempV->status == _NAO_VISITADO)
            {
                enqueue(q, tempV);
                tempV->status == _VISITADO_;
            }
            auxA = auxA->prox;
        }

      
    }

    return cnt;
}

void destroiListaAdj(Aresta* primeiro){
    Aresta* aux = primeiro;
    while(aux){
        Aresta* temp = aux;
        aux = aux->prox;
        free(temp);
    }
}

void destroiGrafo(Grafo* G){
    Vertice *aux;
    if(G->numVertices)
        aux = G->vertices;
    for(int i=0; i<G->numVertices; i++){
        if(aux->num_arestas)
            destroiListaAdj(aux->primeiro_elem);
        Vertice* temp = aux;
        aux = aux->prox;
        free(temp); 
    }
}
