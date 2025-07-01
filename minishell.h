/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 10:43:52 by nosahimi          #+#    #+#             */
/*   Updated: 2025/07/01 17:16:22 by nosahimi         ###   ########.fr       */
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
	HEREDOC,
	RDRIN,
	RDROUT,
	APPND
}t_type;

// typedef enum e_rtype
// {
	
// }t_rtype;

typedef struct s_token
{
	char			*str;
	t_type			type;
	// int				index;
	struct s_token	*next;
}t_token;

typedef struct s_rdr
{
	char			*file;
	t_type			type;
	struct s_rdr	*next;
		
}t_rdr;

typedef struct s_cmd
{
	char			**arg;
	t_rdr			*rdr;
	struct s_cmd	*next;
} t_cmd;

typedef struct s_env
{
	// char			*str;
	char			*name;
	char			*value;
	int				index;
	struct s_env	*next;
}t_env;

typedef struct s_trash
{
	void *ptr;
	struct s_trash *next;
}t_trash;

int	ft_strlen(char *str);
void	ft_strcpy(char *dst, char *src);

/*-------|>---syntax error---<|--------*/
int		syntax_error(char *str);
int		is_valid_quotes(char *str);
int		is_valid_arrows(char *str);
int		is_valid_pipe(char *str);
int		is_symbole(char c);


/*-------|>---env list---<|--------*/
void 	add_back_env(t_env **head, char *name,char *value, int i);
t_env	*creat_node_env(char *name, char *value, int i);
t_env	*get_env(char **envp);
char 	*get_env_name(char *str);
char	*get_env_value(char *str);



/*-------|>---token list---<|--------*/
void 	token_add_back(t_token **head, char *token, t_type type);
t_token	*creat_token(char *token, t_type type);


/*-------|>---toke nizer---<|--------*/
t_token *tokenizer(char *str);
char	*get_token(char **str);
int		get_type(char *str);
// int *global_quote(void);


/*-------|>---token utils---<|--------*/
char	*ft_substr(int start, int end, char *str);
int		ft_strcmp(char *s1, char *s2);
int		white_space(char c);

/*-------|>---variable expand---<|--------*/
void	get_expand(t_token *ptr);
t_token *find_expand(t_token *tokens_list);
// char 	*catch_var(char );

/*-------|>---rdr list---<|--------*/
t_rdr	*create_node_rdr(char *file, int type);
void	add_back_rdr(t_rdr **head, char *file, int type);



/*-------|>---command list---<|--------*/
t_cmd 	*build_cmd_list(t_token *tokens);
void	into_next_cmd(t_token **start);
char 	**get_cmd_arg(t_token *tokens);
int		count_words(t_token *tokens);
t_rdr 	*get_rdr(t_token *tokens);
void	add_back_cmd(t_cmd **head, char **cmd, t_rdr *rdr);
t_cmd 	*create_node_cmd(char **cmd, t_rdr *rdr);



#endif  