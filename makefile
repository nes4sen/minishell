CC = cc
CFLAGS = -Wall -Wextra -Werror -g
# -lreadline

CFILES= build_cmd.c env.c  \
		token_list.c  minishell.c \
		 rdrs_list.c parsing.c\
		syntax.c tokenizer.c utils.c

OBJ_FILES = $(CFILES:.c=.o)

NAME=minishell


all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $(NAME) -lreadline 

%.o:%.c minishell.h
	$(CC) $(CFLAGS) -c $< 

clean:
	rm -f $(OBJ_FILES);
fclean: clean
	rm -f $(NAME);
re: fclean all

.PHONY: clean