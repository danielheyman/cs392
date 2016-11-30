/*
 Authors: Daniel Heyman & Carla Noshi
 Prints the elem of node as a strings
*/
#include "list.h"

void print_string(struct s_node* node) {
    char* pnt;
    
    if(node == NULL || node->elem == NULL) my_str("NULL");
    else {
        pnt = (char*)(node->elem);
        my_str(pnt);
    }
}
