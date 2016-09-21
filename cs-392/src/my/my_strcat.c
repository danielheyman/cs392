#include "my.h"

char *my_strcat(char *dst, char *src) {
    if(dst == NULL || src == NULL) {
        return dst;
    }
    while(*dst != '\0') dst++;
    while(*src != '\0') {
        *dst = *src;
        dst++;
        src++;
    }
    *dst = '\0';
    return dst;
}
