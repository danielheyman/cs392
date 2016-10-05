/*
 Allocates and returns a new node with the given pointers. You may
 create nodes with NULLs.
*/

#include "list.h"

struct s_node* new_node(void* elem, struct s_node* next, struct s_node* previous){
	
	struct s_node* newNode = NULL;
    
    if(elem != NULL)
    {
        newNode = (struct s_node*) malloc(sizeof(struct s_node));
        newNode->elem = elem;
        newNode->next = next;
        newNode->prev = previous;
    }

    return newNode;
}