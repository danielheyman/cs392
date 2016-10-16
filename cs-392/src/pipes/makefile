NAME = pipes

SRC = pipes.c
OBJ = $(SRC:.c=.o)

CFLAGS = -I../../include -Wall -Werror -pedantic
LDFLAGS =

all: $(OBJ)
	cc -L../../lib $(OBJ) -o $(NAME) -lmy -llist -lmy -Wall -Werror -pedantic

clean:
	rm -f $(OBJ)
	rm -f $(NAME)