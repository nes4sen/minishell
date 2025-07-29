/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 10:43:52 by nosahimi          #+#    #+#             */
/*   Updated: 2025/07/29 11:09:16 by nosahimi         ###   ########.fr       */
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


#define NO_QUOTE 0
#define SINGLE_QUOTE 1
#define DOUBLE_QUOTE 2

typedef enum e_type
{
	CMD,
	PIPE,
	HEREDOC,
	RDRIN,
	RDROUT,
	APPND,
	file,
	DLMTR
}t_type;


typedef struct s_extoken
{
	char	*str;
	int		stat;         
	struct s_extoken *next;
}t_extoken;


typedef struct s_token
{
	char			*str;
	t_type			type;
	struct s_token *subtoken;
	struct s_token	*next;
}t_token;

typedef struct s_rdr
{
	char			*file;
	t_type			type;
	int				fd; // only for heredoc
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
	char			*name;
	char			*value;
	int				index;
	struct s_env	*next;
}t_env;

// typedef struct s_trash
// {
// 	void *ptr;
// 	struct s_trash *next;
// }t_trash;

typedef struct s_vars
{
	char	*value;
	int		start;
	int		end;
	struct s_vars *next;
}t_vars;


/*-----------expand----------*/
void	expand_env_vars(t_token *token, t_env *env);
void remove_quote(t_token *token);
char *extract_var_name(char *str);
char *find_env_var(t_env *env, char *var);
int is_expandable(char *str);


/*-----------join-------------*/
char *str_join(char *old, char *new);
char *char_join(char *old, char c, int *index);


/*----------extoken_list----------*/
void build_exlist(t_extoken **exhead, t_token *token);
void add_back_extoken(t_extoken **head, char *str, int stat);
t_extoken *create_extoken_list(char *str, int stat);




int		ft_strlen(char *str);
void	ft_strcpy(char *dst, char *src);
t_cmd	*parsing(char *line, t_env *env);
// int		assigne_stat(char c);


/*-------|>---syntax error---<|--------*/
void			syntax_error(t_token *tokens);
void			syntax_err_msg(char	*err);
unsigned int	def_type(char *str);


/*-------|>---env list---<|--------*/
void 	add_back_env(t_env **head, char *name,char *value, int i);
t_env	*creat_node_env(char *name, char *value, int i);
t_env	*get_env(char **envp);
char 	*get_env_name(char *str);
char	*get_env_value(char *str);


/*-------|>---token list---<|--------*/
void 	token_add_back(t_token **head, char *token, t_type type);
t_token	*creat_token(char *token, t_type type);


/*_______|---tokenizer---|_________*/
t_token *tokenizer(char *str);
char	*get_token(char **str);
void	get_type(t_token *tokens);
void	get_next_type(t_token *tokens);



/*________|---token utils---|_________*/
char	*ft_substr(int start, int end, char *str);
int		ft_strcmp(char *s1, char *s2);
int		white_space(char c);


/*_________|---rdr list---|__________*/
t_rdr	*create_node_rdr(char *file, int type, int fd);
void	add_back_rdr(t_rdr **head, char *file, int type, int fd);


/*_________|---command list---|________*/
t_cmd 	*build_cmd_list(t_token *tokens);

int		count_words(t_token *tokens);
void 	get_rdr(t_rdr **rdr, char *str, unsigned int type);
void	add_back_cmd(t_cmd **head, char **cmd, t_rdr *rdr);
char	**alloc_arg(t_token *tokens);
t_cmd 	*create_node_cmd(char **cmd, t_rdr *rdr);

/*__________is_functions________*/

int	is_symbole(char c);
int	is_seperator(char c);
int	is_oprt(char *op);
int	is_quote(char c);

#endif  