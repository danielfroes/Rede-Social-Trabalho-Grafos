#ifndef ___SOCIAL_NETWORK__
#define ___SOCIAL_NETWORK__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileManagement.h"
#include "grafolista.h"

#define __DOTTED_LINE "---------------------------------------------\n\n"



Grafo* loadSocialNetwork();
Vertice* login(Grafo* G);
void logout(Vertice *user);
void createAccount(Grafo* G);
void addFriend(Grafo* G, Vertice* user);


#endif