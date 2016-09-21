#include "my.h"

void my_num_base(int i, char* s) {
    unsigned int unsigned_copy;
    
    if(s == NULL || *s == '\0') {
        my_str("Invalid string");
        return;
    }
    if(i == 0) {
        my_char(s[0]);
        return;
    } else if (i < 0) {
        my_char('-');
        unsigned_copy = i * -1;
    } else {
        unsigned_copy = i;
    }
    
    unsigned int base = my_strlen(s);
    if(base == 1) {
        while(unsigned_copy-- > 0)
            my_char(s[0]);
        return;
    }
    if(unsigned_copy / base != 0)
        my_num_base(unsigned_copy / base, s);
    my_char(s[unsigned_copy % base]);
}
