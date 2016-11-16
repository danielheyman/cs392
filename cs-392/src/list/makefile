COMPLILER      = gcc
FLAGS = -Wall -Werror --pedantic -std=c99
LIB = ../../lib
INCLUDE = ../../include
TEST = ../../test

all:
	$(COMPLILER) -c *.c $(FLAGS) -I$(INCLUDE)
	ar -rc liblist.a *.o
	ranlib liblist.a
	mv liblist.a $(LIB)
clean:
	rm -f *.o
	rm -f *.o
fclean: clean
	rm -f $(LIB)/liblist.a
re: fclean all
testlist:
	$(COMPLILER) $(TEST)/testlist.c -o $(TEST)/testlist $(FLAGS) -I$(INCLUDE) -L$(LIB) -llist -lmy
	$(TEST)/testlist
	#valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes $(TEST)/testlist
