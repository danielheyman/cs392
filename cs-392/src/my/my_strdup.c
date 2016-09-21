#include "my.h"

char *my_strdup(char *str) {
    if(str == NULL) return NULL;
    
    char *dup = malloc(sizeof(char) * (my_strlen(str) + 1));
    my_strcpy(dup, str);
    return dup;
}
