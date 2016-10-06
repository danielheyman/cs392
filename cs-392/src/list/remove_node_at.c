/*
 Removes the node at index n or the last node.
 Parse once
*/

 #include "list.h"

void* remove_node_at(struct s_node** head, int n) {
    if(head == NULL || *head == NULL) return NULL;
    
    struct s_node *loc = *head;
    while(n-- > 0 || loc->next != NULL) loc = loc->next;
    return remove_node(&loc);
 }
