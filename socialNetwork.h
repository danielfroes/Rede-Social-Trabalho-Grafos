#ifndef ___SOCIAL_NETWORK__
#define ___SOCIAL_NETWORK__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileManagement.h"
#include "grafolista.h"

#define __DOTTED_LINE "---------------------------------------------\n\n"


#define _SUGGEST_FRIEND_THRESHOLD 10
#define _LOVE_THRESHOLD_ 50
#define _FALSE_FRIEND_THRESHOLD_ 10


Grafo* loadSocialNetwork();
Vertice* login(Grafo* G);
void logout(Vertice *user);
void createAccount(Grafo* G);
void addFriend(Grafo* G, Vertice* user);
void removeFriend(Grafo* G, Vertice* user);
void detectFalseFriends(Grafo *G, Vertice* user);
void findTrueLove(Grafo* G, Vertice *user);
void acceptFriendRequest(Grafo* G, Vertice* user);
float calculaAfinidade(Grafo* G, Vertice* a, Vertice* b);
void suggestFriends(Grafo* G, Vertice* user);
void sendFriendRequest(Vertice* user, Vertice* requested);
#endif