/*
 Returns a pointer to the elem at index n or the last node.
 Parse once.
*/

 #include "list.h"

void* elem_at(struct s_node* head, int n){
    if(head == NULL) return NULL;
    
    return node_at(head, n)->elem;
}
