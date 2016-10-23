COMPLILER = gcc-4.8
FLAGS = -Wall -Werror --pedantic -std=c99 -lmy -llist
NAME = client
OBJ = $(NAME).c
LIB = ../../lib
INCLUDE = ../../include

all: $(OBJ)
	$(COMPLILER) $(NAME).c -o $(NAME) $(FLAGS) -I$(INCLUDE) -L$(LIB)

clean:
	rm -f $(NAME)
	
fclean: clean
	
re: fclean all
