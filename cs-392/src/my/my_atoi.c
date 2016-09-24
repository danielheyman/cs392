#include "my.h"

/* Authors: Carla Noshi and Daniel Heyman

 Returns the int represented by the ascii string
 Handles negatives.
 Ignores preceding characters and trailing numbers and chars */

int my_atoi(char *s) {
    if(s == NULL) return 0;
    int num = 0;
    
    int neg = 1;
    if(*s == '-') {
        s++;
        neg = -1;
    }
    
    while(*s != '\0') {
        num = num * 10 + neg * (*(s++) - '0');
    }
    
    return num;
}
