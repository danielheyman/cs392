/* 
 Removes the given node from the list. Returns elem and frees the 
 node from memory.
 DOES NOT PARSE.
*/

 #include "list.h"

void* remove_node(struct s_node** node){
    if(node == NULL || *node == NULL) return NULL;
    
    void* elem = (*node)->elem;
    if((*node)->prev && (*node)->next) {
        (*node)->prev->next = (*node)->next;
        (*node)->next->prev = (*node)->prev;
    } else if((*node)->prev) {
        (*node)->prev->next = NULL;
    } else if((*node)->next) {
        (*node)->next->prev = NULL;
    }
    free(*node);
    *node = NULL;

    return elem;
}
