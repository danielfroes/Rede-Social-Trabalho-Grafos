#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafolista.h"
#include "fileManagement.h"


int main(int argc, char* argv[])
{

    char fileName[100] = "usuarios.csv";
    Usuario* usersArray;
    Grafo* G;

    G = criar_grafo();
    

    usersArray = ReadUserFile(fileName);



    for(int i=0; strcmp(usersArray[i].nome,END_OF_ARRAY); i++)
    {
        inserir_vertice(G, usersArray[i]);
    }

 
    Vertice* V = buscar_vert(G, "Lúcio");

    inserir_aresta(G, V->usuario.nome, "Daniela" );


    imprime_grafo(G);



    free(G);
    free(usersArray);
}


