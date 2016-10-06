/*
 Prints the elem of node as a char
*/
#include "list.h"

void print_int(struct s_node* node) {
    char* pnt;
    
    if(node == NULL || node->elem == NULL) my_str("NULL");
    else {
        pnt = (char*) node->elem;
        my_int(*pnt);
    }
}
