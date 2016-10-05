/* 
 Creates a new node with elem and adds it to head. DO NOT add a NULL 
 elem.
 DOES NOT PARSE
*/
 #include "list.h"

void add_elem(void* elem, struct s_node** head){

 	struct s_node* newNode;

    if(elem != NULL && head != NULL)
    {
        newNode = new_node(elem, NULL, NULL);
        add_node(newNode, head);
    }
}