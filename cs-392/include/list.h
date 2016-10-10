/* Header for liblist assignment. */ 
#ifndef _MYLIST_H_
#define _MYLIST_H_

#include "my.h"

struct s_node{
	void* elem;
	struct s_node* next;
	struct s_node* prev;
};

struct s_node* new_node(void*, struct s_node*, struct s_node*);
void add_node(struct s_node*, struct s_node**);
void add_elem(void*, struct s_node**);
void append(struct s_node*, struct s_node**);
void add_node_at(struct s_node*, struct s_node**, int);
void* remove_node(struct s_node**);
void* remove_last(struct s_node**);
void* remove_node_at(struct s_node**, int);
int count_s_nodes(struct s_node*);
void empty_list(struct s_node**);
struct s_node* node_at(struct s_node*, int);
void* elem_at(struct s_node*, int);
void traverse_int(struct s_node*);
void traverse_char(struct s_node*);
void traverse_string(struct s_node*);
void debug_int(struct s_node* head);
void debug_char(struct s_node* head);
void debug_string(struct s_node* head);
void print_int(struct s_node* node);
void print_char(struct s_node* node);
void print_string(struct s_node* node);


#endif
