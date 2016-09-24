#include "my.h"

/* Authors: Carla Noshi and Daniel Heyman

 Allocates new memory 
 Copies concatenated strings in that new memory 
 Returns pointer to it
 If both NULL return NULL */

char *my_strconcat(char *a, char *b) {
    if(a == NULL && b == NULL) return NULL;
    
    int len = 0;
    if(my_strlen(a) != 0) 
        len += my_strlen(a);
    if(my_strlen(b) != 0) 
        len += my_strlen(b);
    
    char *cat = malloc(sizeof(char) * (len + 1));
    int i = 0;
    while(a != NULL && *a != '\0')
        cat[i++] = *(a++);
    while(b != NULL && *b != '\0')
        cat[i++] = *(b++);
    cat[i] = '\0';
    
    return cat;
}
