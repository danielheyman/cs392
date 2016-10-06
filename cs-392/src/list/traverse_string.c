/*
 Prints all the elems as strings separated by a space
*/

 #include "list.h"

void traverse_string(struct s_node* head){

    while(head != NULL)
    {
        if(head->elem == NULL)
            my_str("NULL");
        else
            my_str(head->elem);

        my_str(" ");
        head = head->next;
    }

    my_char('\n');
}
