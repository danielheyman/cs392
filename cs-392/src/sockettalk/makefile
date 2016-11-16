COMPLILER = gcc
FLAGS = -Wall -Werror --pedantic -std=c99 -lmy -llist
NAME = client
NAME2 = server
LIB = ../../lib
INCLUDE = ../../include

all:
	$(COMPLILER) $(NAME).c -o $(NAME) $(FLAGS) -I$(INCLUDE) -L$(LIB)
	$(COMPLILER) $(NAME2).c -o $(NAME2) $(FLAGS) -I$(INCLUDE) -L$(LIB)

clean:
	rm -f $(NAME) $(NAME2)
	
fclean: clean
	
re: fclean all
