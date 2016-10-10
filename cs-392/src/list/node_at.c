/*
 Authors: Daniel Heyman & Carla Noshi
 Returns a pointer to the node at index n or the last node.
 Parse once
*/

#include "list.h"

struct s_node* node_at(struct s_node* head, int n){
    if(head == NULL) return NULL;
    
    while(n-- > 0 && head->next != NULL) head = head->next;
    return head;
}
