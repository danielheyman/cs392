/* 
 Removes the given node from the list. Returns elem and frees the 
 node from memory.
 DOES NOT PARSE.
*/

 #include "list.h"

void* remove_node(struct s_node** node){
    if(node == NULL || *node == NULL) return NULL;
    
    void* elem = (*node)->elem;
    struct s_node * prev = (*node)->prev;
    struct s_node * next = (*node)->next;
    
    free(*node);
    *node = NULL;
    node = NULL;
    if(prev && next) {
        prev->next = next;
        next->prev = prev;
    } else if(prev) {
        prev->next = NULL;
    } else if(next) {
        next->prev = NULL;
    }

    return elem;
}
