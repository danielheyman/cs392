/*
 Authors: Daniel Heyman & Carla Noshi
 Frees all the nodes in the list.
 CHALLENGE: Write in two lines (allowed to use other methods in 
 this assignment)
*/

#include "list.h"

void empty_list(struct s_node** head){
	if(head == NULL) return;
	while(*head != NULL) {
		remove_last(head);
	}
}
