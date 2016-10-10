/*
 Authors: Daniel Heyman & Carla Noshi
 Removes the node at index n or the last node.
 Parse once
*/

 #include "list.h"

void* remove_node_at(struct s_node** head, int n) {
    if(head == NULL || *head == NULL) return NULL;

    while(n-- > 0 && (*head)->next != NULL) head = &((*head)->next);
    return remove_node(head);
 }
