/*
 Removes the last node from the list.
 Parse Once.
*/

 #include "list.h"

void* remove_last(struct s_node** head){

	struct s_node* nextNode;
    void* returnElem = NULL;

    if(head != NULL && *head != NULL)
    {
        nextNode  = *head;

        while(nextNode->next->next != NULL)
            nextNode = nextNode->next;

        returnElem = nextNode->next->elem;
        nextNode->next = NULL;
    }

    return returnElem;
}
