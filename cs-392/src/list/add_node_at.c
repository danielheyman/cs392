/*
 Authors: Daniel Heyman & Carla Noshi
 Adds a node at index n of a list or at the end of the list if n is 
 too large.
 Parse once
*/

 #include "list.h"

void add_node_at(struct s_node* node, struct s_node** head, int n) {
    if(head == NULL || node == NULL || node->elem == NULL) return;
    
    if(*head == NULL || n == 0) {
        add_node(node, head);
    } else {
        while(--n > 0 && (*head)->next != NULL) head = &((*head)->next);
        if((*head)->next != NULL) {
            (*head)->next->prev = node;
        }
        (*head)->next = node;
        node->prev = (*head);
    }
}
