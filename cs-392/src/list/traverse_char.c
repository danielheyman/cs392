/*
 Prints all the elems as chars separated by a space
*/

 #include "list.h"

void traverse_char(struct s_node* head){
    char* pnt;

    while(head != NULL)
    {
        if(head->elem == NULL)
            my_str("NULL");
        else
        {
            pnt = (char*) head->elem;
            my_char(*pnt);
        }

        my_str(" ");
        head = head->next;
    }

    my_char('\n');
}
