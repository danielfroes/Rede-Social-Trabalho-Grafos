#include "fileManagement.h"




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



Usuario* ReadUserFile()
{
    char line[500];
    char** lineData;
    Usuario* usersArray = (Usuario*) malloc(sizeof(Usuario));
    int nElem = 1, i = 0;
    FILE *f = fopen(__USERDATA_FILE_NAME__, "r");

    fgets(line, 500, f); // pula a linha com os nomes dos campos;

    while(fgets(line, 500, f)!= NULL)
    {

        lineData = split(line, ",\n");

        usersArray = (Usuario*)realloc(usersArray , nElem*sizeof(Usuario));
        usersArray[i].id = atoi(lineData[0]);
        strcpy(usersArray[i].nome, lineData[1]);
        usersArray[i].idade = atoi(lineData[2]);
        strcpy(usersArray[i].cidade, lineData[3]);
        strcpy(usersArray[i].generoFilme, lineData[4]);
        strcpy(usersArray[i].consoleFavorito, lineData[5]);
        strcpy(usersArray[i].areaAtuacao, lineData[6]);
        strcpy(usersArray[i].timeEsportivo, lineData[7]);
        i++;
        nElem++;
    }

    usersArray = (Usuario*)realloc(usersArray , nElem*sizeof(Usuario));
    strcpy(usersArray[i].nome, END_OF_ARRAY);

    fclose(f);
    
    return usersArray;
}


void saveNewUser(Usuario newUser)
{
    FILE* f = fopen(__USERDATA_FILE_NAME__, "a");
    
    fprintf(f, "%d,", newUser.id);
    fprintf(f, "%s,", newUser.nome);
    fprintf(f, "%d,", newUser.idade);
    fprintf(f, "%s,", newUser.cidade);
    fprintf(f, "%s,", newUser.generoFilme);
    fprintf(f, "%s,", newUser.consoleFavorito);
    fprintf(f, "%s,", newUser.areaAtuacao);
    fprintf(f, "%s\n", newUser.timeEsportivo);
    
    fclose(f);
}


