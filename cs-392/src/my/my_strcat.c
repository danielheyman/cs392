#include "my.h"

/* Authors: Carla Noshi and Daniel Heyman

 Copies src onto the end of dst and returns dst
 Does not allocate memory
 Assumes there is enough memory allocated in dst to hold both strings
 Overwrites src's original '\0' and places a new '\0' onto the end */

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
