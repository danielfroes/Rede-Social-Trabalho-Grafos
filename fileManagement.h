#ifndef ___FILEMANAGEMENT__
#define ___FILEMANAGEMENT__


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafolista.h"
#include <ctype.h>

#define END_OF_ARRAY "\0"
#define __USERDATA_FILE_NAME__ "database/userData.csv"
#define __FRIENDSHIPS_FILE_NAME__ "database/friendship.txt"
Usuario* ReadUserFile();
void saveNewUser(Usuario user);
char** split(char* str, char*  divider );
void saveFriendShips(Vertice* user);
#endif