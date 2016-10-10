/*
 Returns the value the length of the list
 Parse Once.
*/
 #include "list.h"

int count_s_nodes(struct s_node* head){
	unsigned int num = 0;

    while(head != NULL)
    {
        num++;
        head = head->next;
    }

    return num;
}
