/*
 Prints all the elems as strings separated by a space
*/

 #include "list.h"

void traverse_string(struct s_node* head){

	struct s_node* nextNode = head;

    while(nextNode != NULL)
    {
        if(nextNode->elem == NULL)
            my_str("NULL");
        else
            my_str(nextNode->elem);

        my_str(" ");
        nextNode = nextNode->next;
    }

    my_char('\n');
}