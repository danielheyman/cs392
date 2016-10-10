/*
 Prints all the elems as chars separated by a space in the format
 (NULL <- Elem -> Next elem), ..., (Previous elem <- Elem -> NULL) 
*/
#include "list.h"

void debug_char(struct s_node* head) {

    while(head != NULL)
    {
        my_str("(");
        print_char(head->prev);
        my_str(" <- ");
        print_char(head);        
        my_str(" -> ");
        print_char(head->next);
        my_str("), ");
        
        head = head->next;
    }
}
