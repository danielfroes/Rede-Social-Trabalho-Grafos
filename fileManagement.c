#include "fileManagement.h"


Usuario* ReadUserFile(char* fileName)
{
    char line[500];
    char** lineData;
    Usuario*

    FILE *f = fopen(fileName, "r"); 



    fgets(line, 500, f);

    while(fgets(line, 500, f)!= NULL)
    {
        lineData = split(line, ",");

    }

    fclose(f);
}



/*  @ Divide uma string usando os caracteres da string divider como delimitodores;
    @ Parâmetros: str - string a ser dividida; divider - string contendo os divisores;
    @ Retorno: Vetor de substrings;
*/
char** split(char* str, char*  divider )
{
    char* token;

    token =  strtok(str, divider);

    char** matrix;

    matrix = (char**) calloc (10, sizeof(char*));    

    int i = 0;
    while(token != NULL)
    {
        matrix[i]  = (char*) calloc (200, sizeof(char));
        strcpy(matrix[i], token);
        token = strtok(NULL, divider);
        i++;
    }

    return matrix;
}

