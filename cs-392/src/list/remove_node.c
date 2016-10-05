/* 
 Removes the given node from the list. Returns elem and frees the 
 node from memory.
 DOES NOT PARSE.
*/

 #include "list.h"

void* remove_node(struct s_node** node){

	void* nodeelem = NULL;
    struct s_node* headNext;

    if(node != NULL && *node != NULL)
    {
        headNext = *node;
        nodeelem = (*node)->elem;
        *node = headNext->next;
        free(headNext);
        headNext = NULL;
    }

    return nodeelem;
}
