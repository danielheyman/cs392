/*
 Prints all the elems as ints separated by a space
*/

 #include "list.h"

void traverse_int(struct s_node* head){

    while(head != NULL)
    {
        print_int(head);

        my_str(" ");
        head = head->next;
    }
}
