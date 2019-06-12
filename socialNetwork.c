#include "socialNetwork.h"


Grafo* loadSocialNetwork() //**Load no Grafo de amizades
{
    Usuario* usersArray;
    Grafo* G;

    G = criar_grafo();
    
    usersArray = ReadUserFile();

    for(int i=0; strcmp(usersArray[i].nome,END_OF_ARRAY); i++)
    {
        inserir_vertice(G, usersArray[i]);
    }

    free(usersArray);

    return G;
}

Vertice* login(Grafo* G) ///** adicionar senhas //** bug q não ta dando login duas vezes
{
    char username[MAX]; 
    Vertice *user;

    printf(__DOTTED_LINE);
    printf("LOGIN\n");
    printf("Digite seu username:  ");
    
    scanf("\n%[^\n]s", username);
    printf("\n");


    user = buscar_vert(G, username);

    user->usuario.logged;

    return user;
}

void logout(Vertice *user)
{
    user->usuario.logged = false;
}

void createAccount(Grafo* G) //** adicionar a checagem para ver usernames repetidos
{
    Usuario user;
    bool validName = false;
    printf("\n\n");
    while(!validName)
    {
        printf("Digite seu username: "); scanf(" %[^\n]s", user.nome);

        if(buscar_vert(G, user.nome) != NULL)//** não ta dando certo
        {
  
            validName = true;
        }
        else
        {
            system("clear");
            printf("\nO username %s não está disponível, tente novamente!\n", user.nome);

        }
    }
    printf("\n\nDigite sua idade: "); scanf("%d", &user.idade);

    printf("\n\nDigite sua cidade: "); scanf(" %[^\n]s", user.cidade);

    printf("\n\nDigite seu gênero de filme favorito: "); scanf(" %[^\n]s", user.generoFilme);

    printf("\n\nDigite seu console de Video Game favorito: "); scanf(" %[^\n]s", user.consoleFavorito);
    
    printf("\n\nDigite sua área de atuação profissional: "); scanf(" %[^\n]s", user.areaAtuacao);
    
    printf("\nDigite seu time: "); scanf(" %[^\n]s", user.timeEsportivo);

    saveNewUser(user);

    G = loadSocialNetwork();
}

void addFriend(Grafo* G, Vertice* user)
{
    char friendName[MAX];
    Vertice* friend;
    printf("Digite o username do usuário que quer adicionar: "); 
    scanf("%[^\n]s", friendName);

    friend = buscar_vert(G, friendName);//** considerar caso de não encontrar

    inserir_aresta(G, user, friend);//** fazer calculo da pontuação
    inserir_aresta(G, friend, user);
}