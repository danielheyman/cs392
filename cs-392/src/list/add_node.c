/*
 Inserts a node at the start of the list. DO NOT add a NULL pointer or
 a node with a NULL elem.
 DOES NOT PARSE
*/
 
#include "list.h"

void add_node(struct s_node* node, struct s_node** head){

	if(node != NULL && head != NULL)
    {
        if(*head != NULL)
        {
            node->next = *head;
            (*head)->prev = node;
        }
        *head = node;
    }
}
