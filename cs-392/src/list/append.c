/*
 Adds a node to the end of a list. DO NOT add a NULL pointer or
 a node with a NULL elem.
 Parse once
*/

 #include "list.h"

 void append(struct s_node* node, struct s_node** head){

 	struct s_node* nextNode;
    struct s_node* prev;

    if(head != NULL && node != NULL && *head != NULL)
    {
        prev = *head;
        nextNode = *head;

        while(nextNode != NULL)
        {
            prev = nextNode;
            nextNode = nextNode->next;
        }
        
        if(prev != NULL)
            prev->next = node;
        else
            (*head)->next = node;
    }
}