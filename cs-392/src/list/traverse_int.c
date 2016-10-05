/*
 Prints all the elems as ints separated by a space
*/

 #include "list.h"

void traverse_int(struct s_node* head){

	struct s_node* nextNode = head;
    int* pnt;

    while(nextNode != NULL)
    {
        if(nextNode->elem == NULL)
            my_str("NULL");
        else
        {
            pnt = (int*) nextNode->elem;
            my_int(*pnt);
        }

        my_str(" ");
        nextNode = nextNode->next;
    }

    my_char('\n');
}