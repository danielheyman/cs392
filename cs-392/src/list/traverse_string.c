/*
 Authors: Daniel Heyman & Carla Noshi
 Prints all the elems as ints separated by a space
*/

 #include "list.h"

void traverse_string(struct s_node* head){

    while(head != NULL)
    {
        print_string(head);

        my_str(" ");
        head = head->next;
    }
}
