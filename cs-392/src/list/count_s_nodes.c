/*
 Returns the value the length of the list
 Parse Once.
*/
 #include "list.h"

int count_s_nodes(struct s_node* head){

	unsigned int num = 0;

    if(head != NULL)
    {
        struct s_node* nextElem = head;

        while(nextElem != NULL)
        {
            nextElem = nextElem->next;
            num++;
        }
    }

    return num;
}