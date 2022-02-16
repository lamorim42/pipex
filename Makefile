### Organizer
SEP ="\n\e[0;36m--------------------------------------------------------\e[0m\n"

### Names
NAME		= pipex

### Compilation configuration
CC			= gcc
CFLAGS		= -g3 -Wall -Werror -Wextra

SRC			= \
				pipex.c \
				handle_cmd.c \
				handle_cmd_utils.c \
				handle_data.c \
				handle_pipex.c \
				check_functions.c \
				ft_split.c \
				ft_strdup.c \
				ft_strjoin.c \
				ft_strlen.c \
				ft_substr.c \
				ft_strchr.c \
				ft_strrchr.c \
				ft_strnstr.c \
				ft_strncmp.c \
				ft_bzero.c \
				ft_memset.c \
				ft_putstr_fd.c

OBJ			= $(SRC:.c=.o)

### Git mensage
MSG = Update

### Default goal
.DEFAULT_GOAL	= all

### Rules
obj/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

check:
	./pipex

norma:
	norminette

git: fclean
	git status
	@echo $(SEP)
	git add .
	@echo $(SEP)
	git commit -m "$(MSG)"
	@echo $(SEP)
	git log | head -n 5

run:
	rm -f outfile
	./pipex infile cat "wc -l" outfile

runv:
	valgrind ./pipex infile cat "wc -l" outfile

.PHONY: all clean fclean re norma git
