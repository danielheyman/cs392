#include "list.h"

/* regarding the traverse and debug methods. It's up to them which one
they used for testing, though obviously debug_ is better to check for back
pointers. If they only used traverse_ when dealing with main data, take
-5 overall. They don't really need to test print_ methods as long as they 
call the debug_ methods.
Each debug_ and traverse_ method needs to be called at least once with
and empty list and with a non empty one */

void my_panic(char *s, unsigned int n) {   my_str(s);   exit(n); }

int main()
{
  my_str("Initializing stuff\n----------------------------------------------\n");
  int arr[10] = {4, 65, 32, 1, 68, 23, 83, 12, 6, 82};
  char *str = "Hello!";                     my_str("str is ");my_str(str);my_char('\n');
  char *str2 = "World!";                    my_str("str is ");my_str(str);my_char('\n');
  struct s_node *head = NULL;                      my_str("the head is NULL\n");my_char('\n');
  unsigned int i;                           
  struct s_node *tmp = NULL;                       my_str("tmp is currently NULL and a t_node *\n");my_char('\n');
  int n = 5;
  //struct s_node **test = NULL;                     
  my_str("test is currenlty NULL and a t_node**\n");my_char('\n');my_char('\n');
  void *ret = NULL;                         my_str("ret is a void* and NULL");my_char('\n');my_char('\n');
  /* new_node test */
  my_char('\n');
    my_str("Testing new_node()\n----------------------------------------------\n");
  tmp = new_node(str, NULL, NULL);      my_str("\t|\t Adding a new node with "); my_str(str); my_str("in tmp\n");my_char('\n');
  print_string(tmp);                    my_str("\t| \t printing string (N<-Hello!->N)\n");my_char('\n');my_char('\n');
  //my_char('\n');
  print_char(tmp);                      my_str("\t| \t printing char (N<-H->N)\n");my_char('\n');
  //my_char('\n');
  free(tmp);                             my_str("Freeing tmp");my_char('\n');
  tmp = new_node(NULL, NULL, NULL);      my_str("new_node with all Nulls\n");my_char('\n');
  if (tmp != NULL && tmp->elem == NULL){
    my_str("Node created with NULLs Galore\n");my_char('\n');
  }
  else{
    my_str("Didn't make node with NULLs\n");my_char('\n');
    exit(1);
    }
  
  /* add_node test */my_char('\n');
  my_str("Testing add_node()\n----------------------------------------------\n");
  debug_int(head);                                    my_str("\t|\t The list is empty");my_char('\n');
  add_node(NULL, &head);                              my_str("\t|\t Adding a node with NULL");my_char('\n');
  debug_int(head); /* still empty */                  my_str("\t|\t The list is empty");my_char('\n');
  add_node(tmp, &head);                               my_str("\t|\t Adding a node with tmp");my_char('\n');
  debug_int(head); /* still empty */                  my_str("\t|\t The list is empty");my_char('\n');
  tmp->elem = &n;
  add_node(tmp, NULL);
  debug_int(head); /* still empty */                  my_str("\t|\t The list is empty");my_char('\n');
  for (i = 0; i < 3; i++)
    {
      add_node(new_node(&arr[i], NULL, NULL), &head); my_str("Adding node number "); my_int(i); my_char('\n');
      debug_int(head);                                my_str("\t|\t"); my_int(i); my_char('\n');
    }
  traverse_int(head); 
  my_str("This should print the list");my_char('\n');
  /* traverse_ should be tested at some point */
 /* technically adding 2 should be enough should test for adding to empty
    and adding to list with only one item. Only 2 cases where things could
    go wrong. They don't need to print after each insertion, one at the end
    would suffice.
 */
  my_str("Emptying a list, passing a NULL");my_char('\n');
  empty_list(NULL); 
  my_str("Emptying a list, passing the non-NULL head");my_char('\n');
  empty_list(&head);
  debug_int(head); my_str("\t|\tdebug_int - The List is empty");my_char('\n');
  traverse_int(head); my_str("\t|\ttraverse_int - The list is empty");my_char('\n');
  debug_string(head); my_str("\t|\tdebug_string - The List is empty");my_char('\n');
  traverse_string(head); /* traverse_ should be tested at some point */
  debug_char(head); /* should print The list is empty */
  traverse_char(head); /* traverse_ should be tested at some point */

  my_str("\nTesting add_elem()\n----------------------------------------------\n");
  my_str("Adding an element with NULL");my_char('\n');
  add_elem(NULL, &head);
  debug_int(head); my_str("\t|\tdebug_int - The List is empty");my_char('\n');
  my_str("Adding a non-NULL element to a NULL head");my_char('\n');
  add_elem(&n, NULL);
  debug_int(head); my_str("\t|\tdebug_int - The List is empty");my_char('\n');
  for (i = 0; i < 3; i++)
    {
      add_elem(&arr[i], &head); my_str("Adding an elem with "); my_int(i); my_char('\n');
      debug_int(head);          my_str("\t|\tprints the list until this point");my_char('\n');
      my_char('\n');
    }

  /* technically adding 2 should be enough should test for adding to empty
     and adding to list with only one item. Only 2 cases where things could
    go wrong. They don't need to print after each insertion, one at the end
    would suffice.
 */
  my_str("Emptying the list");my_char('\n');
  empty_list(&head);
  debug_int(head); my_str("\t|\tdebug_int - The List is empty");my_char('\n');

  my_str("\nTesting append()\n----------------------------------------------\n");
  debug_int(head); my_str("\t|\tdebug_int - The List is empty");my_char('\n');
  my_str("appending a Null to the head (which is null)");my_char('\n');
  append(NULL, &head);
  debug_int(head); my_str("\t|\tdebug_int - The List is empty");my_char('\n');
  my_str("assigning tmp->elem to NULL then appending tmp to the head");my_char('\n');
  tmp->elem = NULL;
  append(tmp, &head); 
  debug_int(head); my_str("\t|\tdebug_int - The List is empty");my_char('\n');
  my_str("assigning tmp->elem to non-NULL then appending tmp to a NULL head");my_char('\n');
  tmp->elem = &n;
  append(tmp, NULL);
  debug_int(head); my_str("\t|\tdebug_int - The List is empty");my_char('\n');
  for (i = 0; i < 3; i++)
    {
      append(new_node(&arr[i], NULL, NULL), &head); my_str("appending a new node with "); my_int(i); my_char('\n');
      debug_int(head);                              my_str("\t|\tprints the list until this point");my_char('\n');
      my_char('\n');
    }
  /* same as usual, 2 insertions should suffice */
  my_str("Emptying the list");my_char('\n');
  empty_list(&head);
  debug_int(head); my_str("\t|\tdebug_int - The List is empty");my_char('\n');
  
  my_str("\nTesting add_node_at()\n----------------------------------------------\n");
  add_node_at(NULL, &head, 1);
  debug_int(head); my_str("\t|\tdebug_int - The List is empty");my_char('\n');
  tmp->elem = NULL;
  add_node_at(tmp, &head, 2);
  debug_int(head); my_str("\t|\tdebug_int - The List is empty");my_char('\n');
  tmp->elem = &n;
  add_node_at(tmp, NULL, 3);
  debug_int(head); my_str("\t|\tdebug_int - The List is empty");my_char('\n');
  /* I'm going overboard with these testing with indexes that are at the front and the back. 
I don't expect them to be as extreme. As long as they test 0 once, large number once, empty list once,
list with only one item once, and list with 2 or more items once, I'll be happy enough */
  for (i = 0; i < 3; i++)
    {
      add_node_at(new_node(&arr[i], NULL, NULL), &head, 0); my_str("adding a node at the head");my_char('\n');
      debug_int(head);                                      my_str("\t|\tprints the list until this point");my_char('\n');
      my_char('\n');
    }
  empty_list(&head); my_str("Emptying the list");my_char('\n');
  debug_int(head);   my_str("debug_int - the list is empty");my_char('\n');
  for (i = 0; i < 3; i++)
    {
      add_node_at(new_node(&arr[i], NULL, NULL), &head, 438); my_str("adding at the end of the list with a very large number");my_char('\n');
      debug_int(head);                                        my_str("\t|\tprints the list until this point");my_char('\n');
      my_char('\n');
    }
  empty_list(&head); my_str("Emptying the list");my_char('\n');
  debug_int(head);   my_str("debug_int - the list is empty");my_char('\n');
  /* putting all the ints in order to test the removes later on */
  my_str("Adding all the integers one after the other with add_node_at");my_char('\n');
  for (i = 0; i < 10; i++)
    {
      add_node_at(new_node(&arr[i], NULL, NULL), &head, i);
      debug_int(head);
      my_char('\n');
    }
  add_node_at(tmp, &head, 2);
  debug_int(head);
  //exit(0);
  my_char('\n');

  /* testing count nodes. Technically all they need to do is call it at some point with an empty list
     and with an non-empty one */
  my_str("\nTesting count_nodes()\n----------------------------------------------\n");
  my_int(count_s_nodes(head)); my_str("\t|\t Counting the nodes - 11");my_char('\n');
  my_char('\n');
  my_int(count_s_nodes(NULL)); my_str("\t|\t Counting the nodes with NULL passed- 0");my_char('\n');
  my_char('\n');
  
  /* testing removes: gonna remove a few items with each method, then test each with NULLs and lists of one item only */
  my_str("\nTesting remove_node()\n----------------------------------------------\n");
  debug_int(head); my_str("\t|\tThis should print the list\n");
  ret = remove_node(&head);
  my_int(*((int*)ret));
  my_char('\n');
  debug_int(head); my_str("\t|\tThis should print the list\n");
  my_char('\n');
  my_str("\nTesting remove_last()\n----------------------------------------------\n");
  debug_int(head); my_str("\t|\tThis should print the list\n");
  ret = remove_last(&head);
  my_int(*((int*)ret));
  my_char('\n');
  debug_int(head); my_str("\t|\tThis should print the list\n");
  my_char('\n');
  my_str("\nTesting remove_node_at() with 0\n----------------------------------------------\n");
  debug_int(head); my_str("\t|\tThis should print the list\n");
  ret = remove_node_at(&head, 0);
  my_int(*((int*)ret));
  my_char('\n');
  debug_int(head); my_str("\t|\tThis should print the list\n");
  my_char('\n');
  my_str("\nTesting remove_node_at() with a large number\n----------------------------------------------\n");
  debug_int(head); my_str("\t|\tThis should print the list\n");
  ret = remove_node_at(&head, 243);
  my_int(*((int*)ret));
  my_char('\n');
  debug_int(head); my_str("\t|\tThis should print the list\n");
  my_char('\n');
  my_str("\nTesting remove_node_at with an in range number()\n----------------------------------------------\n");
  debug_int(head);
  ret = remove_node_at(&head, 3);
  my_int(*((int*)ret));
  my_char('\n');
  debug_int(head);
  my_char('\n');

  my_str("Emptying List");my_char('\n');
  empty_list(&head);
  debug_int(head);
  my_str("Adding back some elements and then removing them");my_char('\n');
  add_elem(&n, &head);
  debug_int(head);
  my_char('\n');
  ret = remove_node(&head);
  my_int(*((int*)ret));
  my_char('\n');
  debug_int(head);
  my_char('\n');
  add_elem(&n, &head);
  debug_int(head);
  my_char('\n');
  ret = remove_last(&head);
  my_int(*((int*)ret));
  my_char('\n');
  debug_int(head);
  my_char('\n');
  add_elem(&n, &head);
  debug_int(head);
  my_char('\n');
  ret = remove_node_at(&head, 0);
  my_int(*((int*)ret));
  my_char('\n');
  debug_int(head);
  my_char('\n');
  add_elem(&n, &head);
  debug_int(head);
  my_char('\n');
  ret = remove_node_at(&head, 243);
  my_int(*((int*)ret));
  my_char('\n');
  debug_int(head);
  my_char('\n');

  if (remove_node(&head) == NULL)
    my_str("Passed remove_node from empty\n");
  else
    my_panic("Failed remove_node from empty\n",1);

  if (remove_last(&head) == NULL)
    my_str("Passed remove_last from empty\n");
  else
    my_panic("Failed remove_last from empty\n",1);

  if (remove_node_at(&head, 0) == NULL)
    my_str("Passed remove_node_at 0 from empty\n");
  else
    my_panic("Failed remove_node_at 0 from empty\n",1);

  if (remove_node_at(&head, 3) == NULL)
    my_str("Passed remove_node_at 3 from empty\n");
  else
    my_panic("Failed remove_node_at 3 from empty\n",1);

  if (remove_node(NULL) == NULL)
    my_str("Passed remove_node from NULL\n");
  else
    my_panic("Failed remove_node from NULL\n",1);

  if (remove_last(NULL) == NULL)
    my_str("Passed remove_last from NULL\n");
  else
    my_panic("Failed remove_last from NULL\n",1);

  if (remove_node_at(NULL, 0) == NULL)
    my_str("Passed remove_node_at 0 from NULL\n");
  else
    my_panic("Failed remove_node_at 0 from NULL\n",1);

  if (remove_node_at(NULL, 3) == NULL)
    my_str("Passed remove_node_at 3 from NULL\n");
  else
    my_panic("Failed remove_node_at 3 from NULL\n",1);

  /* testing node_at and elem_at with NULLs */
  my_str("Testing node_at and elem_at with NULLS\n----------------------------------------------\n");
  if (node_at(NULL, 0) == NULL)
    my_str("Passed node_at 0 from empty\n");
  else
    my_panic("Failed node_at 0 from empty\n", 1);
  if (node_at(NULL, 2) == NULL)
    my_str("Passed node_at 2 from empty\n");
  else
    my_panic("Failed node_at 2 from empty\n", 1);
  if (elem_at(NULL, 0) == NULL)
    my_str("Passed elem_at 0 from empty\n");
  else
    my_panic("Failed elem_at 0 from empty\n", 1);
  if (elem_at(NULL, 2) == NULL)
    my_str("Passed elem_at 2 from empty\n");
  else
    my_panic("Failed elem_at 2 from empty\n", 1);

  /* adding strings to list to test these 2 methods and the last debug ones */
  add_elem(str2, &head);
  my_char('\n');
  add_elem(str, &head);
  my_char('\n');
  debug_string(head);
  my_char('\n');
  traverse_string(head);
  my_char('\n');
  debug_char(head);
  my_char('\n');
  traverse_char(head);
  my_char('\n');
  my_str((char*)elem_at(head, 0)); my_str("\t|\tPrinting the elem_at - Hello");
  my_char('\n');
  my_str((char*)elem_at(head, 43)); my_str("\t|\tPrinting the elem_at - World");
  my_char('\n');
  tmp = node_at(head, 0);
  print_string(tmp);
  my_char('\n');
  tmp = node_at(head, 43);
  print_string(tmp);
  my_char('\n');
  empty_list(&head);
  debug_string(head);
  /* this last one is mainly to clear memory */
  return 0;
}

/*
int main(int argc, char const *argv[]){
	t_node* node1;
	t_node* node2;
	t_node* list;
	t_node* list2;

	int num = 12345;
	int num2 = 54321;
	int num3 = -12;
	int num4 = 0;
	int num5 = 17;
	int num6 = -553;
	char* str = my_strdup("TEST");
	char* str2 = my_strdup("HELP");
	char* str3 = my_strdup("-");
	char* str4 = my_strdup("YOOOO");

	//NEW NODE
	node1 = new_node(NULL, NULL, NULL);
	if(node1 == NULL) my_str("[PASSED] - new_node all NULL\n");
	else my_str("[FAILED] - new_node all NULL\n");
	free(node1);

	node1 = new_node(&num, NULL, NULL);
	if(node1->elem == &num && node1->next == NULL && node1-> prev == NULL) my_str("[PASSED] - new_node int* with NULL next and prev\n");
	else my_str("[FAILED] - new_node int* with NULL next and prev\n");

	node2 = new_node(&num6, node1, node1);
	if(node2->elem == &num6 && node2->next == node1 && node2-> prev == node1) my_str("[PASSED] - new_node char* with next and prev\n");
	else my_str("[FAILED] - new_node char* with next and prev\n");

	my_char('\n');
	//ADD NODE
	list = new_node(&num, NULL, NULL);
	add_node(NULL, NULL);
	add_node(node2, NULL);
	add_node(NULL, &list);
	add_node(new_node(&num, NULL, NULL), &list);
	add_node(node2, &list);
	debug_int(list);
	my_str("\n\n");

	//ADD ELEM
	add_elem(&num, NULL);
	add_elem(NULL, &list);
	debug_int(list); my_char('\n');
	add_elem(&num2, &list);
	debug_int(list); my_str("\n\n");

	//APPEND
	append(NULL, NULL);
	append(node1, NULL);
	append(NULL, &list);
	debug_int(list); my_char('\n');
	append(new_node(&num3, NULL, NULL), &list);
	debug_int(list); my_str("\n\n");

	//ADD NODE AT
	add_node_at(NULL, NULL, 0);
	add_node_at(node2, NULL, 0);
	add_node_at(NULL, &list, 0);
	debug_int(list); my_char('\n');
	add_node_at(new_node(&num4, NULL, NULL), &list, 0);
	debug_int(list); my_char('\n');
	add_node_at(new_node(&num4, NULL, NULL), &list, 3);
	debug_int(list); my_char('\n');
	add_node_at(new_node(&num4, NULL, NULL), &list, -1);
	debug_int(list); my_str("\n\n");

	//REMOVE
	remove(NULL);
	my_int(*((int*)remove(&node2))); my_char('\n');
	debug_int(list); my_str("\n");
	my_int(*((int*)remove(&list))); my_char('\n');
	debug_int(list); my_str("\n\n");

	//REMOVE LAST
	remove_last(NULL);
	my_int(*((int*)remove_last(&list))); my_char('\n');
	debug_int(list); my_str("\n\n");

	//REMOVE AT
	remove_node_at(NULL, 0);
	my_str("Okay\n");
	my_int(*((int*)remove_node_at(&list, 0))); my_char('\n');
	debug_int(list); my_char('\n');
	my_int(*((int*)remove_node_at(&list, 2))); my_char('\n');
	debug_int(list); my_char('\n');
	my_int(*((int*)remove_node_at(&list, -1))); my_char('\n');
	debug_int(list); my_str("\n\n");
	
	my_int(count_nodes(NULL)); my_char('\n');
	my_int(count_nodes(list)); my_str("\n\n");

	print_int(node_at(NULL, 0)); my_char('\n');
	print_int(node_at(list, 0)); my_char('\n');
	print_int(node_at(list, 1)); my_char('\n');
	print_int(node_at(list, -1)); my_str("\n\n");
	
	elem_at(NULL, 0); my_char('\n');
	my_int(*((int*)elem_at(list, 0))); my_char('\n');
	my_int(*((int*)elem_at(list, 1))); my_char('\n');
	my_int(*((int*)elem_at(list, -1))); my_str("\n\n");

	//PRINTING

	list2 = new_node(&str, NULL, NULL);
	add_elem(str2, &list2);
	add_elem(str3, &list2);
	add_elem(str4, &list2);

	traverse_int(NULL);
	traverse_int(list); my_str("ti\n");
	
	traverse_char(NULL);
	traverse_char(list2); my_str("tc\n");
	
	traverse_str(NULL); 
	traverse_str(list2); my_str("ts\n\n");
	
	debug_string(NULL);
	debug_string(list2); my_str("\n");
	
	debug_int(NULL);
	debug_int(list); my_str("\n");
	
	debug_char(NULL);
	debug_char(list2); my_str("\n\n");
	
	print_char(NULL);
	print_char(list2); my_str("\n");
	
	print_string(NULL);
	print_string(list2); my_str("\n");
	
	print_int(NULL);
	print_int(list); my_str("\n\n");

	empty_list(NULL);
	empty_list(&list);
	debug_int(list);


	return 0;
}

//t_node* new_node(void* e, t_node* n, t_node* p);  // /\
//void add_node(t_node* n, t_node** ph);	// /\
//void add_elem(void* e, t_node** ph);  //  /\
//void append(t_node*, t_node** ph);  // []
//void add_node_at(t_node*, t_node**, unsigned int n); // []
//void* remove(t_node**); // /\ returns elem and frees node
//void* remove_last(t_node**); // []
//void* remove_node_at(t_node**, unsigned int); // []
//unsigned int count_nodes(t_node*);
//void empty_list(t_node**); //2 lines?
//void* node_at(t_node*, unsigned int);
//void* elem_at(t_node*, unsigned int);
//void traverse_int(t_node*); // Print list is empty
//void traverse_char(t_node*); // Print list is empty
//void traverse_str(t_node*); // Print list is empty
//void debug_string(t_node*);
//void debug_int(t_node*);
//void debug_char(t_node*);
//void print_char(t_node*);
//void print_string(t_node*);
//void print_int(t_node*);
*/
