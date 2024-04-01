##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Makefile
##

SRC	=	$(wildcard *.c)

OBJS =	$(SRC:.c=.o)

NAME	=	my_sokoban

LIB	=	-L lib/my/ -lmy

CURSELIB	=	-lncurses

HSRC	=	include/sokoban.h

CFLAGS	=	-g3

all: create

create: ${OBJS}
		make -C lib/my
		gcc -o $(NAME) $(OBJS) -I ${HSRC} ${LIB} ${CURSELIB}

clean:
		rm -f *.o
		rm -f lib/my/*.o

fclean:clean
		rm -f $(NAME)

re: fclean all
