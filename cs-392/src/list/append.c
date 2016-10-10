/*
 Authors: Daniel Heyman & Carla Noshi
 Adds a node to the end of a list. DO NOT add a NULL pointer or
 a node with a NULL elem.
 Parse once
*/

#include "list.h"

void append(struct s_node* node, struct s_node** head){
    add_node_at(node, head, INT_MAX);
}
