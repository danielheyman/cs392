#include "my.h"

void my_int(int i) {
    int divisor = 1;
    unsigned int unsigned_copy;
    unsigned int copy2;
    
    if(i < 0) {
        my_char('-');
        unsigned_copy = i * -1;
    } else {
        unsigned_copy = i;
    }
    
    copy2 = unsigned_copy;
    while(copy2 > 10) {
        copy2 /= 10;
        divisor *= 10;
    }
    
    while(divisor > 0) {
        my_char(((unsigned_copy / divisor) % 10) + '0');
        divisor /= 10;
    }
}
