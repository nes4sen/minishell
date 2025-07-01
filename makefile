CC = cc
CFLAGS = -Wall -Wextra -Werror 
# -lreadline

CFILES= command.c env.c  \
		list_utils.c  minishell.c \
		 rdrs_list.c \
		syntax.c tokenizer.c utils.c

OBJ_FILES = $(CFILES:.c=.o)

NAME=minishell


all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $(NAME)

%.o:%.c minishell.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJ_FILES);
fclean: clean
	rm -f $(NAME);
re: fclean all

.PHONY: clean