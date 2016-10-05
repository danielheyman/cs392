/*
 Adds a node at index n of a list or at the end of the list if n is 
 too large.
 Parse once
*/

 #include "list.h"

void add_node_at(struct s_node* node, struct s_node** head, int n){

	struct s_node* nextNode;

    if(head != NULL && node != NULL)
    {
        if(n == 0 || *head == NULL)
            add_node(node, head);
        else
        {
            nextNode = *head;
            n--;

            for( ; n > 0 && nextNode->next != NULL; nextNode = nextNode->next, n--)
                ;

            node->next = nextNode->next;
            nextNode->next = node;
        }
    }
}
