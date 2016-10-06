/*
 Prints all the elems as ints separated by a space
*/

 #include "list.h"

void traverse_int(struct s_node* head){
    int* pnt;

    while(head != NULL)
    {
        if(head->elem == NULL)
            my_str("NULL");
        else
        {
            pnt = (int*) head->elem;
            my_int(*pnt);
        }

        my_str(" ");
        head = head->next;
    }

    my_char('\n');
}
