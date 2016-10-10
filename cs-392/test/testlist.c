/* Test file

Carla Noshi and Daniel Heyman
I pledge my honor that I have abided by the Stevens Honor System.

*/ 
#include "list.h"

int main(int argc, char **argv) {
    //char* test;
    //test = my_strdup("$$$$$$$$$$$$$$$");
    //free(test);
    int int1 = 1;
    int int2 = 2;
    //int int3 = 3;
    char char1 = 'a';
    //char char2 = 'b';
    //char char3 = 'c';
    char * str1 = "aaa";
    //char char2 = 'b';
    //char char3 = 'c';
    struct s_node* head;
    struct s_node* test;
    
    my_str("new_node, print_char, print_int, print_str tests:\n");
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
    
    my_str("\nadd_node, debug_int, debug_char, debug_string, empty_list tests:\n");
    head = new_node(&int1, NULL, NULL);
    test = new_node(&int2, NULL, NULL);
    debug_int(head);
    my_str("\n = (NULL <- 1 -> NULL),\n");
    add_node(test, &head);
    debug_int(test);
    my_str("\n = (NULL <- 2 -> 1), (2 <- 1 -> NULL),\n");
    empty_list(&head);
    debug_int(head);
    my_str("\n = (NULL <- 2 -> NULL),\n");
    print_int(test);
    my_str("\n = (NULL <- 2 -> NULL),\n");
    
    
    
    return 0;
}
