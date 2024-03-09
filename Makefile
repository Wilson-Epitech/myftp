##
## MYFTP PROJECT, 2024
## [Conteneur de développement : C @ desktop-linux]
## File description:
## Makefile
##

CC ?= gcc

SRC	=	main.c				\
		src/init.c			\
		src/server.c 		\

OBJ	=	$(SRC:.c=.o)

RM = rm -f

CPPFLAGS += -iquote./include

CFLAGS += -Wall -Wextra -g3

NAME	=	myftp

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CPPLAGS) $(CFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re:	 fclean all

.PHONY = all clean fclean re
