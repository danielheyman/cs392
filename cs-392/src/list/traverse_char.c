/*
 Prints all the elems as chars separated by a space
*/

 #include "list.h"

void traverse_char(struct s_node* head){
	struct s_node* nextNode = head;
    char* pnt;

    while(nextNode != NULL)
    {
        if(nextNode->elem == NULL)
            my_str("NULL");
        else
        {
            pnt = (char*) nextNode->elem;
            my_char(*pnt);
        }

        my_str(" ");
        nextNode = nextNode->next;
    }

    my_char('\n');
}
