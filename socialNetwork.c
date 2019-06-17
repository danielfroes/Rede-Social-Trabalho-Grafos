#include "socialNetwork.h"


Grafo* loadSocialNetwork(){
    Usuario* usersArray;
    Grafo* G;

    G = criar_grafo();
    
    usersArray = ReadUserFile();

    for(int i=0; strcmp(usersArray[i].nome,END_OF_ARRAY); i++){
        inserir_vertice(G, usersArray[i]);
    }

    free(usersArray);

    return G;
}

Vertice* login(Grafo* G){
    char username[MAX]; 
    char senha[MAX];
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
    printf("Digite a senha: ");
    scanf("\n%[^\n]s", senha);
    while(strcmp(senha, user->usuario.senha)!=0){
        printf("Senha incorreta, digite novamente.\n");
        scanf("\n%[^\n]s", senha);
    }
    user->usuario.logged=true;
    return user;
}

void logout(Vertice *user){
    user->usuario.logged = false;
}

void createAccount(Grafo* G){
    Usuario user;
    bool validName = false;
    printf("\n\n");
    while(!validName)
    {
        printf("Digite seu username: "); scanf(" %[^\n]s", user.nome);

        if(buscar_vert(G, user.nome) == NULL){
  
            validName = true;
        }
        else{
            system("clear");
            printf("\nO username %s não está disponível, tente novamente!\n", user.nome);

        }
    }
    printf("\n\nDigite sua senha: "); scanf("%s", user.senha);

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


/*
    Função addFriend: Busca usuário por nome e adiciona uma solicitação de amizade no usuário buscado
    Grafo* G -> endereço do grafo que contém a rede social
    Vertice* user -> usuário logado
 */
void addFriend(Grafo* G, Vertice* user){
    char friendName[MAX];
    Vertice* friend;
    printf("Digite o username do usuário que quer adicionar: "); 
    scanf("\n%[^\n]s", friendName);
    friend = buscar_vert(G, friendName);
    if(friend && friend->usuario.id == user->usuario.id){
        printf("Você não pode se adicionar!\n");
        return;
    }
    Aresta* ant=NULL;
    Aresta* friendship = buscar_aresta(user, friendName, &ant);
    if(friend && !friendship){ //Caso usuário exista e usuário logado e buscado não sejam amigos
        friend->usuario.nSolicitacoes++;
        friend->usuario.solicitacoesAmizade = realloc(friend->usuario.solicitacoesAmizade, sizeof(Vertice *)*friend->usuario.nSolicitacoes);
         //Adiciona o usuário atual no vetor de usuários que realizaram solicitação
        friend->usuario.solicitacoesAmizade[friend->usuario.nSolicitacoes-1] = user;
        printf("Solicitação de amizade enviada!\n");
    }else if(!friend){
        printf("Usuário não encontrado!\n");
    }else if(friendship){
        printf("Você já é amigo deste usuário!\n");

    }

    
}

/*
    Função acceptFriendRequest: Percorre vetor com usuários que realizaram solicitação de amizade e pergunta ao
    usuário se deseja adicioná-los
    Grafo* G -> endereço do grafo que contém a rede social
    Vertice* user -> usuário logado
 */
void acceptFriendRequest(Grafo* G, Vertice* user){
    if(user->usuario.nSolicitacoes){
        for(int i=0; i<user->usuario.nSolicitacoes; i++){
            printf("O usuário %s te enviou uma solicitação de amizade.\nDeseja adicioná-lo?\n1 - SIM\n2 - NÃO\n", user->usuario.solicitacoesAmizade[i]->usuario.nome);
            int op=0;
            while(op!=1 && op!=2)
                scanf("%d", &op);
            if(op==1){
                inserir_aresta(G, user, user->usuario.solicitacoesAmizade[i]);
                inserir_aresta(G, user->usuario.solicitacoesAmizade[i], user);
            }    
        }
        user->usuario.nSolicitacoes=0;
        free(user->usuario.solicitacoesAmizade);
    }else{
        printf("Você não tem solicitações de amizade!\n");
    }
}

/*
    Função detectFalseFriends: Percorre a lista de amigos de um usuário e checa se possuem um grau de afinidade
    menor que 20
    Parâmetros:
    Grafo* G -> endereço do grafo que contém a rede social
    Vertice* user -> usuário logado
 */
void detectFalseFriends(Grafo *G, Vertice* user){
    Aresta* aux = user->primeiro_elem;
    int nFalsos=0;
    if(user->num_arestas){
        for(int i=0; i<user->num_arestas; i++){
            if(aux && aux->grauAfinidade < 20){
                nFalsos++;
                printf("Infelizmente o usuário %s tem baixa afinidade com você =(\n", aux->usuarioAmigo.nome);
                printf("Deseja remover amizade?\n1 - SIM\n2 - NÂO\n");
                int opcao=0;
                while (opcao!= 1 && opcao!=2){ //Leitura feita até uma entrada válida
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
    if(!nFalsos && user->num_arestas){
        printf("Você não tem falsas amizades!\n");
    }
}

/*
    Função removeFriend: Busca usuário pelo username e remove as arestas entre os 2 usuários
    Parâmetros:
    Grafo* G -> endereço do grafo que contém a rede social
    Vertice* user -> usuário logado
 */
void removeFriend(Grafo* G, Vertice* user){
    if(user->num_arestas==0){
        printf("Parabéns! Você não tem amigos!\n");
        return;
    }
        
    char toBeRemoved[MAX];
    printf("Digite o nome do amigo que deseja remover a amizade: ");
    scanf("\n%[^\n]", toBeRemoved);
    Aresta* ant=NULL;
    //Busca de aresta e usuário
    Aresta* friendship = buscar_aresta(user, toBeRemoved, &ant);
    Vertice* otherUser = buscar_vert(G, toBeRemoved);
    if(otherUser && friendship){ //Caso o usário exista e há amizade entre user e o buscado
        removerAresta(G, user, friendship);
    }else if(!otherUser){
        printf("Usuário não encontrado!\n");
    }else if(!friendship){
        printf("Você e %s não são amigos!\n", toBeRemoved);
    }
}

/*
    Função findTrueLove: Calcula grau de afinidade de um vértice escolhido com todos os outros
    os outros vértices e sugere ao usuário adicionar outros usuários com afinidade máxima
    Parâmetros:
    Grafo* G -> endereço para o grafo da rede social
    Vertice* user -> vertice que contém o usuário logado
 */
void findTrueLove(Grafo* G, Vertice *user){
    Vertice* aux = G->vertices;
    int lovesFound=0;
    for(int i=0; i<G->numVertices; i++){
        //Calcular apenas com usuários diferentes
        if(aux->usuario.id != user->usuario.id){
            int afinidade = calculaAfinidade(aux, user);
            if(afinidade>=80){
                printf("Você tem o perfil 100%% compatível com %s\n", aux->usuario.nome);
                Aresta *ant;
                lovesFound++;
                //Checa se ja há amizade
                if(buscar_aresta(user, aux->usuario.nome, &ant)==NULL){
                    printf("Deseja adicionar como amigo?\n1 - SIM\n2 - NÃO\n");
                    int op=0;
                    while(op!=1 && op!=2){
                        scanf("%d",&op);
                    }
                    if(op==1){
                        //Envio de solicitação de amizade
                        aux->usuario.nSolicitacoes++;
                        aux->usuario.solicitacoesAmizade = realloc(aux->usuario.solicitacoesAmizade, sizeof(Vertice *)*aux->usuario.nSolicitacoes);
                        aux->usuario.solicitacoesAmizade[aux->usuario.nSolicitacoes-1] = user;
                        printf("Solicitação de amizade enviada!\n");
                    }
                }else{
                    printf("Você e %s já são amigos!\n", aux->usuario.nome);
                }
            }
        }
        aux = aux->prox;
    }
    if(!lovesFound){
        printf("Infelizmente não encontramos nenhum perfil 100%% compatível com o seu =(\n");
    }
}

