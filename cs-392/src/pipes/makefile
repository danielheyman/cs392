COMPLILER      = gcc-4.8
FLAGS = -Wall -Werror --pedantic -std=c99
LIB = ../../lib
INCLUDE = ../../include
TEST = ../../test

all:
	$(COMPLILER) -c *.c $(FLAGS) -I$(INCLUDE)
	ar -rc libpipes.a *.o
	ranlib libpipes.a
	mv libpipes.a $(LIB)
clean:
	rm -f *.o
	rm -f *.o
fclean: clean
	rm -f $(LIB)/libpipes.a
re: fclean all