CC = cc
CFLAGS = -Wall -Wextra -Werror -g
# -lreadline

CFILES= build_cmd.c env.c  is_functions.c \
		token_list.c  minishell.c join.c  \
		expand_tools.c extoken_list.c     \
		extokenizer.c    \
		rdrs_list.c parsing.c expand.c    \
		syntax.c tokenizer.c utils.c      \
		mini_libft.c \

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




push:
	git add . && git commit -m "scripted commit" && git push




.PHONY: clean