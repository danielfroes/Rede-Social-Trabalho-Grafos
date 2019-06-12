#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafolista.h"


int main(int argc, char* argv[])
{

    char fileName[100];
    Usuario* userArray;
    Grafo* G;

    G = criar_grafo();
    
    userArray = readUserFile(fileName);


}


