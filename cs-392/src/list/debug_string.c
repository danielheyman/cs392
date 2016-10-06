/*
 Prints all the elems as strings separated by a space in the format
 (NULL <- Elem -> Next elem), ..., (Previous elem <- Elem -> NULL) 
*/
#include "list.h"

void debug_string(struct s_node* head) {

    while(head != NULL)
    {
        my_str("(");
        print_string(head->prev);
        my_str(" <- ");
        print_string(head);        
        my_str(" -> ");
        print_string(head->next);
        my_str("), ");
        
        head = head->next;
    }

    my_char('\n');
}
