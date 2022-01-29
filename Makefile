### Names
NAME		= pipex

### Paths
VPATH		= src include

### Compilation configuration
CC			= gcc
CFLAGS		= -g3 -Wall -Werror -Wextra -I include

SRC			= \
				pipex.c \
				ft_split.c \
				ft_strdup.c \
				ft_strjoin.c \
				ft_strlen.c \
				ft_substr.c \

OBJ			= $(SRC:.c=.o)
OBJ_PATH	= $(addprefix obj/, $(OBJ))

### Git mensage
MSG = "Update"

### Default goal
.DEFAULT_GOAL	= all

### Rules
obj/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ_PATH)
		$(CC) $(CFLAGS) $(OBJ_PATH) -o $(NAME)

clean:
	rm -f $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all

norma:
	norminette src include

git:
	echo $(MSG)

.PHONY: all clean fclean re git
