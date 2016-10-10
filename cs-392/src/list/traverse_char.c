/*
 Authors: Daniel Heyman & Carla Noshi
 Prints all the elems as ints separated by a space
*/

 #include "list.h"

void traverse_char(struct s_node* head){

    while(head != NULL)
    {
        print_char(head);

        my_str(" ");
        head = head->next;
    }
}
