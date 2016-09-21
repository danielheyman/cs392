#include "my.h"

int my_strindex(char* s, char c) {
    if(s == NULL) return -1;
    
    unsigned int i = 0;
    while(*s != '\0') {
        if(*s == c) return i;
        s++;
        i++;
    } 
    return -1;
}
