#include "socialNetwork.h"

/*
    Função loadSocialNetwork: Lê arquivos que contém Vertices e Arestas e carrega-os no grafo
    Retorno:
    Grafo* G -> endereço do grafo que contém a rede social
 */
Grafo* loadSocialNetwork(){
    Usuario* usersArray;
    Grafo* G;

    G = criar_grafo();
    
    usersArray = ReadUserFile();

    for(int i=0; strcmp(usersArray[i].nome,END_OF_ARRAY); i++){
        inserir_vertice(G, usersArray[i]);
    }
    readFriendships(G);
    free(usersArray);

    return G;
}

/*
    Função login: Lê usuário e senha e realiza login se ambos estiverem corretos
    Parâmetros:
    Grafo* G -> endereço do grafo que contém a rede
    Retorno:
    Vertice* user -> vertice contendo o usuário encontrado
 */
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

/*
    Função logout: Realiza logout do usuário
    Parâmetros:
    Vertice* user -> usuário que realiza logout
 */
void logout(Vertice *user){
    user->usuario.logged = false;
}

/*
    Função createAccount: Registra um novo usuário na rede e salva no csv de usuários7
    Parâmetros:
    Grafo* G-> endereço do grafo que contém a rede
 */
void createAccount(Grafo* G){
    Usuario user;
    bool validName = false;
    printf("\n\n");
    while(!validName){
        //Usuário utilizado como chave primária
        printf("Digite seu username: "); scanf(" %[^\n]s", user.nome);
        if(buscar_vert(G, user.nome) == NULL){
            validName = true;
        }
        else{
            system("clear");
            printf("\nO username %s não está disponível, tente novamente!\n", user.nome);

        }
    }
    //Entrada dos dados
    printf("\n\nDigite sua senha: "); scanf("%s", user.senha);
    printf("\n\nDigite sua idade: "); scanf("%d", &user.idade);
    printf("\n\nDigite sua cidade: "); scanf(" %[^\n]s", user.cidade);
    printf("\n\nDigite seu gênero de filme favorito: "); scanf(" %[^\n]s", user.generoFilme);
    printf("\n\nDigite seu console de Video Game favorito: "); scanf(" %[^\n]s", user.consoleFavorito);
    printf("\n\nDigite sua área de atuação profissional: "); scanf(" %[^\n]s", user.areaAtuacao);
    printf("\nDigite seu time: "); scanf(" %[^\n]s", user.timeEsportivo);
    //Id = número atual de vértices
    user.id = G->numVertices;
    G->numVertices++;
    //Escrita do novo usuário no arquivo
    saveNewUser(user);

    G = loadSocialNetwork();
}

/*
    Função suggestFriends: Procura usuários com nível de afinidade acima de 40 e sugere como amigos
    Parâmetros:
    Grafo* G-> endereço do grafo que contém a rede social
    Vertice* user -> usuário logado 
 */
void suggestFriends(Grafo* G, Vertice* user)
{
    float auxNota, multiplicador;
    Vertice* auxV = G->vertices;
    printf("AMIGOS SUGERIDOS PARA SEU PERFIL:\n\n");
    
    //itera por todos vértices dos grafos
    for(int i = 0; i  < G->numVertices; i++) {
        //pula o usuário logado
        if(auxV->usuario.id != user->usuario.id)
        {
            auxNota = calculaAfinidade(G, auxV, user);
            Aresta* ant;
            //Caso a afinidade seja maior que o limite de sugestão de amizade e não sejam amigos
            if(auxNota >= _SUGGEST_FRIEND_THRESHOLD && !buscar_aresta(user, auxV->usuario.nome, &ant)){
                printf("Você e o usuário %s tem coisas em comum!!\n", auxV->usuario.nome);
                printf("Deseja adicionar como amigo?\n1 - SIM\n2 - NÃO\n");
                int op=0;
                while(op!=1 && op!=2){ //Leitura de opção válida
                    scanf("%d",&op);
                }
                if(op==1){
                    sendFriendRequest(user, auxV);
                }
            }
        }
        auxV = auxV->prox;
    }

    
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
        sendFriendRequest(user, friend);
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
            if(aux && aux->grauAfinidade < _FALSE_FRIEND_THRESHOLD_){
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
            float afinidade = calculaAfinidade(G, aux, user);
            if(afinidade>=_LOVE_THRESHOLD_){
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
                        sendFriendRequest(user, aux);
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

void sendFriendRequest(Vertice* user, Vertice* requested)
{  /*
    for(int i=0;i<requested->usuario.nSolicitacoes; i++){
        //Checa para duplas solicitações
        if(requested->usuario.solicitacoesAmizade[i]->usuario.id == user->usuario.id){
            printf("Você já enviou uma solicitação para este usuário!\n");
            return;
        }
    }*/
    //Envio de solicitação de amizade
    if(requested->usuario.solicitacoesAmizade)
        requested->usuario.nSolicitacoes++;
    requested->usuario.solicitacoesAmizade = realloc(requested->usuario.solicitacoesAmizade, sizeof(Vertice *)*requested->usuario.nSolicitacoes);
    requested->usuario.solicitacoesAmizade[requested->usuario.nSolicitacoes-1] = user;
    printf("Solicitação de amizade enviada!\n");
}

/*
    Função calculaAfinidade: calcula o grau de afinidade entre 2 usuários de acordo com
    os interesses passados
    Parâmetros:
    Vertice* a -> vértice que contém o primeiro usuário
    Vertice* b -> vérice que contém o segundo usuários
    Retorno:
    int afinidade/bfs(G, b, a->usuario.id) -> grau de afinidade calculado a partir dos gostos
                                              e multiplicado pelo inverso da distancia mínima entre os vértices 
*/
float calculaAfinidade(Grafo* G, Vertice* a, Vertice* b){
    int afinidade = 0;
    if(abs(a->usuario.idade - b->usuario.idade)<=6){
        afinidade+=10;
    }
    if(strcmp(a->usuario.cidade, b->usuario.cidade)==0){
        afinidade+=30;
    }
    if(strcmp(a->usuario.timeEsportivo, "São Caetano")==0 && strcmp(b->usuario.timeEsportivo, "São Caetano")==0){
        afinidade+=100;
    }else if(strcmp(a->usuario.timeEsportivo, b->usuario.timeEsportivo)==0){
        afinidade+=10;
    }
    if(strcmp(a->usuario.areaAtuacao, b->usuario.areaAtuacao)==0){
        afinidade+=30;
    }
    if(strcmp(a->usuario.generoFilme, b->usuario.generoFilme)==0){
        afinidade+=20;
    }
    
    return afinidade/(float)bfs(G, b, a->usuario.id); //quanto mais distante do vertice do usuário, menor a sua pontuação.
}