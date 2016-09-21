#include "my.h"

int my_strlen(char* s) {
    if(s == NULL) return -1;
    int len = 0;
    while(*s != '\0') {
        len++;
        s++;
    }
    return len;
}
