/*
 Removes the node at index n or the last node.
 Parse once
*/

 #include "list.h"

void* remove_node_at(struct s_node** head, int n){
	struct s_node* prev;
    struct s_node* nextNode;
    void* returnElem = NULL;

    if(head != NULL)
    {
        if(n == 0)
            returnElem = remove_node(head);
        else
        {
            nextNode = (*head)->next;

            while(n > 0 && nextNode != NULL)
            {
                prev = nextNode;
                nextNode = nextNode->next;
                n--;
            }

            returnElem = prev->elem;
            prev->next = nextNode;
        }
    }

    return returnElem;
}