COMPLILER = gcc
FLAGS = -Wall -Werror --pedantic -std=c99 -lmy -llist -lcurses -D_POSIX_SOURCE
NAME = nsminishell
LIB = ../../lib
INCLUDE = ../../include

all:
	$(COMPLILER) $(NAME).c -o $(NAME) $(FLAGS) -I$(INCLUDE) -L$(LIB)

clean:
	rm -f $(NAME)
	
fclean: clean
	
re: fclean all
