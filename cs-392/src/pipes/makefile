COMPLILER = gcc-4.8
FLAGS = -Wall -Werror --pedantic -std=c99 -lmy -llist
NAME = pipes
LIB = ../../lib
INCLUDE = ../../include

all:
	$(COMPLILER) $(NAME).c -o $(NAME) $(FLAGS) -I$(INCLUDE) -L$(LIB)

clean:
	rm -f $(NAME)
	
fclean: clean
	
re: fclean all
