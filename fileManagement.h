#ifndef ___FILEMANAGEMENT__
#define ___FILEMANAGEMENT__


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafolista.h"
#include <ctype.h>

#define END_OF_ARRAY "\0"
#define __USERDATA_FILE_NAME__ "database/userData.csv"

Usuario* ReadUserFile();
void saveNewUser(Usuario user);



#endif