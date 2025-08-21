CC = cc
CFLAGS = -Wall -Wextra -Werror -g -Iinclude
# -lreadline

CFILES= parsing/build_cmd.c parsing/env.c  parsing/is_functions.c \
		parsing/token_list.c  minishell.c parsing/join.c  \
		parsing/expand_tools.c parsing/extoken_list.c     \
		parsing/extokenizer.c  parsing/build_cmd_list.c\
		parsing/rdrs_list.c parsing/parsing.c parsing/expand.c    \
		parsing/syntax.c parsing/tokenizer.c parsing/utils.c      \
		parsing/mini_libft.c parsing/cmd_args.c parsing/is_functions_two.c\
		parsing/mmtracker.c parsing/llmmtracker.c parsing/heredoc.c  parsing/utils_init.c\
		builtin/cd.c builtin/echo.c builtin/eenv.c builtin/exit.c builtin/export.c\
		builtin/pwd.c builtin/unset.c builtin/utilis_export.c builtin/utils_cd.c builtin/export_help.c\
		execution/execution.c execution/pipe.c execution/segnals.c execution/split.c \
		execution/utils_ex.c execution/help_norme.c execution/help_red.c execution/pipe_help.c\
		execution/pipe_help2.c execution/execution_builtin.c 

OBJ_FILES = $(CFILES:.c=.o) 
NAME=minishell

all: $(NAME)
$(NAME): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $(NAME) -lreadline 
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJ_FILES)
fclean: clean
	rm -f $(NAME)
re: fclean all

push:
	git add . && git commit -m "$(commit)" && git push


.PHONY: clean