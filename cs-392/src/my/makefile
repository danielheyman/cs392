COMPLILER      = gcc
FLAGS = -Wall -Werror --pedantic -std=c99
LIB = ../../lib
INCLUDE = ../../include
TEST = ../../test

all:
	$(COMPLILER) -c *.c $(FLAGS) -I$(INCLUDE)
	ar -rc libmy.a *.o
	ranlib libmy.a
	mv libmy.a $(LIB)
clean:
	rm -f *.o
	rm -f *.o
fclean: clean
	rm -f $(LIB)/libmy.a
re: fclean all
testmy:
	$(COMPLILER) $(TEST)/testmy.c -o $(TEST)/testmy $(FLAGS) -I$(INCLUDE) -L$(LIB) -lmy
	$(TEST)/testmy
	#valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes $(TEST)/testmy
testmyTA:
	$(COMPLILER) $(TEST)/testmyTA.c -o $(TEST)/testmyTA $(FLAGS) -I$(INCLUDE) -L$(LIB) -lmy
	$(TEST)/testmyTA
