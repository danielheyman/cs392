#include "my.h"

int my_strrindex(char* s, char c) {
    if(s == NULL) return -1;
    
    unsigned int i = 0;
    int res = -1;
    while(*s != '\0') {
        if(*s == c) res = i;
        s++;
        i++;
    } 
    return res;
}
