/*
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
        struct s_node *loc = *head;
        while(--n > 0 || loc->next != NULL) loc = loc->next;
        loc->next = node;
        node->prev = loc;
    }
}
