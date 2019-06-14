#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "socialNetwork.h"

#define __EXIT__ 0

#define __LOGIN__ 1
#define __CREATE_ACCOUNT__ 2

#define __LOGOUT__ 1
#define __ADICIONAR_AMIGO__ 2
#define __ENCONTRAR_FALSO_AMIGO__ 3


void printMenu(Usuario user);

int main(int argc, char* argv[])
{

    Grafo* G;
    short unsigned int menu;

    G = loadSocialNetwork();

    Vertice* user = malloc(sizeof(user));
    user->usuario.logged = false;



    while(true)
    {

        printMenu(user->usuario);

        scanf("%hd", &menu);
        //system("clear");
        

       
        if(menu == __EXIT__)
        {
            printf(__DOTTED_LINE);
            printf("Até a próxima! =D \n\n");
            printf(__DOTTED_LINE);
            break;
        }


        if(user->usuario.logged)
        {  
            if(menu == __LOGOUT__)
            {
                logout(user);
            }
            else if(menu == __ADICIONAR_AMIGO__)
            {
                addFriend(G, user);
                imprime_grafo(G);
            }else if(menu == __ENCONTRAR_FALSO_AMIGO__){
                detectFalseFriends(G, user);
            }
        }
        else //usuario não logado
        {
            if(menu == __LOGIN__)
            {      
                user = login(G);
            }
            else if(menu == __CREATE_ACCOUNT__)
            {
                createAccount(G);
                G = loadSocialNetwork();
            }
        }
  

    }
    free(G);
 
}


void printMenu(Usuario user)
{

    //system("clear");
    printf(__DOTTED_LINE);
    printf(__DOTTED_LINE);
    
    
    if(user.logged)
    {
        printf("Olá, %s! Tudo bem?\n", user.nome);
        printf("O que você deseja fazer agora?\n");
        printf(__DOTTED_LINE);
        printf("0 - SAIR DO PROGRAMA\n\n");
        printf("1 - LOGOUT\n\n");
        printf("2 - ADICIONAR UM AMIGO\n\n");
        printf("3 - ECONTRAR FALSAS AMIZADES\n\n");
    }
    else
    {  
        printf("Você não está conectado! Por favor, faça o login na sua conta!\n\n");
        printf(__DOTTED_LINE);
        printf("0 - SAIR DO PROGRAMA\n\n");
        printf("1 - LOGIN\n\n");
        printf("2 - CRIAR NOVA CONTA\n\n");
    }
    
    printf(__DOTTED_LINE);
    printf(__DOTTED_LINE);

}