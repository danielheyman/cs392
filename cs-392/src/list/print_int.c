/*
 Authors: Daniel Heyman & Carla Noshi
 Prints the elem of node as an int
*/
#include "list.h"

void print_int(struct s_node* node) {
    int* pnt;
    
    if(node == NULL || node->elem == NULL) my_str("NULL");
    else {
        pnt = (int*) node->elem;
        my_int(*pnt);
    }
}
