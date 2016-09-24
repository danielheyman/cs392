#include "my.h"

/* Authors: Carla Noshi and Daniel Heyman

 Allocates new memory 
 Copies str into that new memory 
 returns pointer to new string */

char *my_strdup(char *str) {
    if(str == NULL) return NULL;
    
    char *dup = malloc(sizeof(char) * (my_strlen(str) + 1));
    my_strcpy(dup, str);
    return dup;
}
