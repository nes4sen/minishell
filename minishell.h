/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 10:43:52 by nosahimi          #+#    #+#             */
/*   Updated: 2025/06/24 16:51:46 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <readline/readline.h>
#include <readline/history.h>

#define VOID_MODE 0
#define SINGLE_MODE 1
#define DOUBLE_MODE 2

typedef enum e_type
{
	CMD,
	PIPE,
	RDRIN,
	RDROUT,
	HEREDOC,
	APPND
}t_type;

typedef struct s_token
{
	char			*str;
	t_type			type;
	struct	s_token	*next;
}t_token;

typedef struct s_cmd
{
	char *cmd;

} t_cmd;

typedef struct s_env
{
	char			*str;
	struct s_env	*next;
}t_env;

typedef struct s_trash
{
	void *ptr;
	struct s_trash *next;
}t_trash;

int	ft_strlen(char *str);

/*-------|>---syntax error---<|--------*/
int		syntax_error(char *str);
int		is_valid_quotes(char *str);
int		is_valid_arrows(char *str);
int		is_valid_pipe(char *str);
int		is_symbole(char c);


/*-------|>---env list---<|--------*/
void	add_back_env(t_env **head, char *str);
t_env	*creat_node_env(char *str);
t_env	*get_env(char **envp);


/*-------|>---token list---<|--------*/
void 	token_add_back(t_token **head, char *token, t_type type);
t_token	*creat_token(char *token, t_type type);


/*-------|>---toke nizer---<|--------*/
t_token *tokenizer(char *str);
char	*get_token(char **str);
int		get_type(char *str);


/*-------|>---token utils---<|--------*/
char	*ft_substr(int start, int end, char *str);
int		ft_strcmp(char *s1, char *s2);
int		white_space(char c);

/*-------|>---variable expand---<|--------*/
void	get_expand(t_token *ptr);
t_token *find_expand(t_token *tokens_list);
char 	*catch_var(char );










#endif  