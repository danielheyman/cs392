/*
 Returns a pointer to the elem at index n or the last node.
 Parse once.
*/

 #include "list.h"

void* elem_at(struct s_node* head, int n){

	void* returnElem = NULL;
    struct s_node* counter;

    if(head != NULL)
    {
        counter = head;

        for( ; n > 0 && counter->next != NULL; counter = counter->next, n--)
            ;

        returnElem = counter->elem;
    }

    return returnElem;
}