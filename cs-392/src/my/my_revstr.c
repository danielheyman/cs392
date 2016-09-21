#include "my.h"

int my_revstr(char* s) {
    int len = my_strlen(s);
    unsigned int i = 0;
    
    while(i < len / 2) {
        char temp = s[i];
        s[i] = s[len - 1 - i];
        s[len - 1 - i] = temp;
        i++;
    }
    return len;
}
