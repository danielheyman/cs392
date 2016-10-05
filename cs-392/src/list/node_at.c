/*
 Returns a pointer to the node at index n or the last node.
 Parse once
*/

#include "list.h"

struct s_node* node_at(struct s_node* head, int n){

	struct s_node* nextNode = NULL;

    if(head != NULL)
    {
        nextNode = head;

        while(nextNode->next != NULL && n > 0)
        {
            nextNode = nextNode->next;
            n--;
        }
    }

    return nextNode;
}