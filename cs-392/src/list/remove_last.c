/*
 Removes the last node from the list.
 Parse Once.
*/

 #include "list.h"

void* remove_last(struct s_node** head){
    return remove_node_at(head, INT_MAX);
}
