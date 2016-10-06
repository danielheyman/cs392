/*
 Prints all the elems as ints separated by a space in the format
 (NULL <- Elem -> Next elem), ..., (Previous elem <- Elem -> NULL) 
*/
#include "list.h"

void debug_int(struct s_node* head) {

    while(head != NULL)
    {
        my_str("(");
        print_int(head->prev);
        my_str(" <- ");
        print_int(head);        
        my_str(" -> ");
        print_int(head->next);
        my_str("), ");
        
        head = head->next;
    }

    my_char('\n');
}
