#include "fileManagement.h"




/*  @ Divide uma string usando os caracteres da string divider como delimitodores;
    @ Parâmetros: str - string a ser dividida; divider - string contendo os divisores;
    @ Retorno: Vetor de substrings;
*/
char** split(char* str, char*  divider, int* total )
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
    
    *total = i;
    return matrix;
}

/*
    Função readFriendships: Lê arquivo que contém as amizades registradas e as adiciona no Grafo
    Parâmetros:
    Grafo* G -> endereço do grafo que contém a rede social
 */
void readFriendships(Grafo* G){
    FILE* f = fopen(__FRIENDSHIPS_FILE_NAME__, "r");
    while(!feof(f)){
        //Nome do vértice
        char nome1[MAX];
        fscanf(f, "%[^\n]s", nome1);
        Vertice* v1 = buscar_vert(G, nome1);
        char buffer[500];
        //Pula linha
        fgets(buffer, 500, f);
        //Leitura da linha contendo amizades
        fscanf(f, "%[^\n]s", buffer);
        int totalAmigos=0;
        //Usuários amigos separados por ;
        char** nomes = split(buffer, ";", &totalAmigos);
        fgets(buffer, 500, f);
        for(int i=0; i<totalAmigos; i++){
            //Inserção das arestas
            Vertice* v2 = buscar_vert(G, nomes[i]);
            inserir_aresta(G, v1, v2);
        }
    }
    fclose(f);
}

/*
    Função storeFriendships: Escreve todas as amizades contidas no grafo no arquivo antes de encerrar o programa
    Parâmetros:
    Grafo* G -> endereço do grafo que contém a rede social
 */
void storeFriendships(Grafo *G){
    //Apaga o que estava no arquivo
    FILE* f =  fopen(__FRIENDSHIPS_FILE_NAME__, "w");
    Vertice* auxV = G->vertices;
    Aresta* auxA;
    for(int i=0; i<G->numVertices; i++){
        if(auxV->num_arestas) //Usuário só será registrado caso tenha amizades
            fprintf(f, "%s\n", auxV->usuario.nome); //Escreve o username do usuário
        auxA = auxV->primeiro_elem;
        for(int j=0; j<auxV->num_arestas; j++){
            fprintf(f,"%s;",auxA->usuarioAmigo.nome); //Escreve o username de seus amigos
            auxA=auxA->prox;
        }
        if(auxV->num_arestas)
            fprintf(f, "\n");
        auxV = auxV->prox;
    }
}

/*
    Função ReadUserFile: Lê o csv contendo todos os usuários e monta um array contendo todos os usuários
 */
Usuario* ReadUserFile(){
    char line[500];
    char** lineData;
    Usuario* usersArray = (Usuario*) malloc(sizeof(Usuario));
    int nElem = 1, i = 0;
    FILE *f = fopen(__USERDATA_FILE_NAME__, "r");
    int total;

    fgets(line, 500, f); // pula a linha com os nomes dos campos;

    while(fgets(line, 500, f)!= NULL)
    {  
        lineData = split(line, ",\n", &total); //Divide campos por ,

        usersArray = (Usuario*)realloc(usersArray , nElem*sizeof(Usuario));
        //Leitura de todos os campos
        usersArray[i].id = atoi(lineData[0]);
        strcpy(usersArray[i].nome, lineData[1]);
        strcpy(usersArray[i].senha, lineData[2]);
        usersArray[i].idade = atoi(lineData[3]);
        strcpy(usersArray[i].cidade, lineData[4]);
        strcpy(usersArray[i].generoFilme, lineData[5]);
        strcpy(usersArray[i].consoleFavorito, lineData[6]);
        strcpy(usersArray[i].areaAtuacao, lineData[7]);
        strcpy(usersArray[i].timeEsportivo, lineData[8]);
        i++;
        nElem++;
    }
    //Escreve o último usuário
    usersArray = (Usuario*)realloc(usersArray , nElem*sizeof(Usuario));
    strcpy(usersArray[i].nome, END_OF_ARRAY);
    for(int j=0; j<total; j++){
        free(lineData[j]);
    }
    free(lineData);
    fclose(f);
    
    return usersArray;
}

/*
    Função saveNewUser: Escreve novo usuário no fim do arquivo
    Parâmetros:
    Usuario newUser -> informações do novo usuário
 */
void saveNewUser(Usuario newUser)
{
    FILE* f = fopen(__USERDATA_FILE_NAME__, "a");
    
    fprintf(f, "%d,", newUser.id);
    fprintf(f, "%s,", newUser.nome);
    fprintf(f, "%s,", newUser.senha);
    fprintf(f, "%d,", newUser.idade);
    fprintf(f, "%s,", newUser.cidade);
    fprintf(f, "%s,", newUser.generoFilme);
    fprintf(f, "%s,", newUser.consoleFavorito);
    fprintf(f, "%s,", newUser.areaAtuacao);
    fprintf(f, "%s,;\n", newUser.timeEsportivo);
    
    fclose(f);
}


