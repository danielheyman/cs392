/* Test file

Carla Noshi and Daniel Heyman
I pledge my honor that I have abided by the Stevens Honor System.

*/ 
#include "list.h"

int main(int argc, char **argv) {
    int int1 = 1;
    int int2 = 2;
    int int3 = 3;
    char char1 = 'a';
    char char2 = 'b';
    //char char3 = 'c';
    char * str1 = "aaa";
    char * str2 = "bbb";
    //char char3 = 'c';
    struct s_node* head;
    struct s_node* test;
    
    my_str("new_node, print_char, print_int, print_str, remove_node tests:\n");
    test = new_node(&char1, NULL, NULL);
    head = new_node(NULL, test, NULL);
    print_char(NULL);
    print_int(NULL);
    print_string(NULL);
    my_str("\t = NULLNULLNULL\n");
    print_char(head);
    print_int(head);
    print_string(head);
    my_str("\t = NULLNULLNULL\n");
    print_char(head->next);
    my_str("\t\t = a\n");
    remove_node(&head);
    head = new_node(NULL, NULL, test);
    print_char(head->prev);
    my_str("\t\t = a\n");
    remove_node(&head);
    head = new_node(&int1, NULL, NULL);
    print_int(head);
    my_str("\t\t = 1\n");
    remove_node(&head);
    head = new_node(&str1, NULL, NULL);
    print_string(head);
    my_str("\t\t = aaa\n");
    remove_node(&test);
    remove_node(&head);
    
    my_str("\nadd_node, append, add_node_at, traverse_int, debug_int, traverse_char, debug_char, traverse_string, debug_string, remove_last, empty_list tests:\n");
    head = new_node(&int1, NULL, NULL);
    test = new_node(&int2, NULL, NULL);
    debug_int(head);
    my_str("\n = (NULL <- 1 -> NULL),\n");
    add_node(test, &head);
    debug_int(head);
    my_str("\n = (NULL <- 2 -> 1), (2 <- 1 -> NULL),\n");
    remove_last(&head);
    traverse_int(head);
    debug_int(head);
    my_str("\n = 2 (NULL <- 2 -> NULL),\n");
    empty_list(&head);
    head = new_node(&char1, NULL, NULL);
    test = new_node(&char2, NULL, NULL);
    append(test, &head);
    traverse_char(head);
    debug_char(head);
    my_str("\n = a b (NULL <- a -> b), (a <- b -> NULL),\n");
    empty_list(&head);
    head = new_node(&str1, NULL, NULL);
    test = new_node(&str2, NULL, NULL);
    add_node_at(test, &head, 1);
    traverse_string(head);
    debug_string(head);
    my_str("\n = aaa bbb (NULL <- aaa -> bbb), (aaa <- bbb -> NULL),\n");
    empty_list(&head);
    
    my_str("\ncount_s_nodes, node_at, elem_at:\n");
    head = new_node(&int1, NULL, NULL);
    test = new_node(&int2, NULL, NULL);
    append(test, &head);
    test = new_node(&int3, NULL, NULL);
    append(test, &head);
    debug_int(head);
    my_str("\n = (NULL <- 1 -> 2), (1 <- 2 -> 3), (2 <- 3 -> NULL),\n");
    my_int(count_s_nodes(head));
    my_str("\t = 3\n");
    print_int(node_at(head, 5));
    my_str("\t = 2\n");
    int * i = elem_at(head, 1);
    my_int(*i);
    my_str("\t = 1\n");
    empty_list(&head);
    
    return 0;
}
