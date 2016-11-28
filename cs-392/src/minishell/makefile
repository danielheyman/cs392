COMPLILER = gcc
FLAGS = -Wall -Werror --pedantic -std=c99 -lmy -llist -D_POSIX_SOURCE
NAME = minishell
LIB = ../../lib
INCLUDE = ../../include

all:
	$(COMPLILER) $(NAME).c -o $(NAME) $(FLAGS) -I$(INCLUDE) -L$(LIB)

clean:
	rm -f $(NAME)
	
fclean: clean
	
re: fclean all
