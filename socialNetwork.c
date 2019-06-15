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
    while(!user){
        printf("Usuário não encontrado!\nDigite o username novamente: ");
        scanf("\n%[^\n]s", username);
        user = buscar_vert(G, username);
    }
    user->usuario.logged=true;
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

        if(buscar_vert(G, user.nome) == NULL)//** não ta dando certo
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
    user.id = G->numVertices;
    G->numVertices++;
    saveNewUser(user);
    
    G = loadSocialNetwork();
}

void addFriend(Grafo* G, Vertice* user){
    char friendName[MAX];
    Vertice* friend;
    printf("Digite o username do usuário que quer adicionar: "); 
    scanf("\n%[^\n]s", friendName);
    Aresta* ant=NULL;
    friend = buscar_vert(G, friendName);
    Aresta* friendship = buscar_aresta(user, friendName, &ant);
    if(friend!=NULL && friendship==NULL){
        inserir_aresta(G, user, friend);
        inserir_aresta(G, friend, user);
    }else if(!friend){
        printf("Usuário não encontrado!\n");
    }else if(friendship){
        printf("Você já é amigo deste usuário!\n");
    }
}


void detectFalseFriends(Grafo *G, Vertice* user){
    Aresta* aux = user->primeiro_elem;
    if(user->num_arestas){
        for(int i=0; i<user->num_arestas; i++){
            if(aux && aux->grauAfinidade < 20){
                printf("Infelizmente o usuário %s tem baixa afinidade com você =(\n", aux->usuarioAmigo.nome);
                printf("Deseja remover amizade?\n1 - SIM\n2 - NÂO\n");
                int opcao=0;
                while (opcao!= 1 && opcao!=2){
                    scanf("%d", &opcao);
                }
                if(opcao==1){
                    removerAresta(G, user, aux);
                }
                
            }
            aux = aux->prox;
        }
    }else{
        printf("Parabéns! Você não tem amigos!\n");
    }
}

void removeFriend(Grafo* G, Vertice* user){
    if(user->num_arestas==0){
        printf("Parabéns! Você não tem amigos!\n");
        return;
    }
        
    char toBeRemoved[MAX];
    printf("Digite o nome do amigo que deseja remover a amizade: ");
    scanf("\n%[^\n]", toBeRemoved);
    Aresta* ant=NULL;
    Aresta* friendship = buscar_aresta(user, toBeRemoved, &ant);
    Vertice* otherUser = buscar_vert(G, toBeRemoved);
    if(otherUser && friendship){
        removerAresta(G, user, friendship);
    }else if(!otherUser){
        printf("Usuário não encontrado!\n");
    }else if(!friendship){
        printf("Você e %s não são amigos!\n", toBeRemoved);
    }
}

void findTrueLove(Grafo* G, Vertice *user){
    Vertice* aux = G->vertices;
    for(int i=0; i<G->numVertices; i++){
        if(aux->usuario.id != user->usuario.id){
            int afinidade = calculaAfinidade(aux, user);
            if(afinidade==100){
                printf("Você tem o perfil 100%% compatível com %s\n", aux->usuario.nome);
                Aresta *ant;
                if(buscar_aresta(user, aux->usuario.nome, &ant)==NULL){
                    printf("Deseja adicionar como amigo?\n1 - SIM\n2 - NÃO\n");
                    int op=0;
                    while(op!=1 && op!=2){
                        scanf("%d",&op);
                    }
                    if(op==1){
                        inserir_aresta(G, user, aux);
                        inserir_aresta(G, aux, user);
                    }
                }
            }
        }
        aux = aux->prox;
    }
}