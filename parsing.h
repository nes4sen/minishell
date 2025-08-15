/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 10:48:18 by nosahimi          #+#    #+#             */
/*   Updated: 2025/08/14 11:32:24 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>

#define NO_QUOTE 0
#define SINGLE_QUOTE 1
#define DOUBLE_QUOTE 2

#define FREE_ALL 1
#define FREE_ALL_EXCEPT_ENV 2 

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
	struct s_rdr	*next;
}t_rdr;

typedef struct s_cmd
{
	char			**arg;
	t_rdr			*rdr;
	char			*heredox;
	struct s_cmd	*next;
} t_cmd;


typedef struct s_extoken
{
	char	*str;
	int		stat;         
	struct s_extoken *next;
}t_extoken;

typedef struct s_env
{
	char			*name;
	char			*value;
	int				index;
	struct s_env	*next;
}t_env;

typedef struct s_mmtrack
{
	void				*ptr;
	struct s_mmtrack	*next;
} t_mmtrack;

typedef struct s_address_track
{
	t_mmtrack	*head; 
	t_mmtrack	*tail;  
	t_env		*env; 
}t_address_track;

typedef struct s_shell
{
	char		*line;
	t_token		*tokens;
	t_env		*env;
	t_cmd		*cmd;
	t_mmtrack	*mmtrack;
	int			exit_s;
}t_shell;

/*-------------------------------- PARSING -------------------------------------*/
int		parser(t_shell *shell);


/*--- PARSING ENV -------------------------------------------------------------*/
void 	add_back_env(t_env **head, char *name,char *value, int i);
t_env	*creat_node_env(char *name, char *value, int i);
t_env	*get_env(char **envp);
char 	*get_env_name(char *str);
char	*get_env_value(char *str);
void	init_env(char **envp, t_shell *shell);
int		idx_nod(t_env *env);


/*--- TOKENIZER ---------------------------------------------------------------*/
t_token	*create_token(char *token, t_type type);
void	token_add_back(t_token **head, char *token, t_type type);
void	tokenizer(t_shell *shell);
char	*get_token(char **str);
void	get_type(t_token *tokens);
void	get_next_type(t_token *tokens);


/*--- SYNTAX ERROR ------------------------------------------------------------*/
int				syntax_error(t_shell *shell);
int				syntax_err_msg(char	*err, t_shell *shell);
unsigned int	def_type(char *str);


/*--- EXPAND ------------------------------------------------------------------*/
void	expand_env_vars(t_shell *shell);
char	*remove_quote(char *str);
char 	*extract_var_name(char *str);
char 	*find_env_var(t_shell *shell, char *var);
int 	is_expandable(char *str);


/*--- EXTOKENIZER -------------------------------------------------------------*/
void 		build_exlist(t_extoken **exhead, t_token *token);
void 		add_back_extoken(t_extoken **head, char *str, int stat);
t_extoken	*create_extoken_list(char *str, int stat);


/*--- COMMAND -----------------------------------------------------------------*/
void	build_cmd(t_shell *shell);
void	add_back_cmd(t_cmd **head, char **cmd, t_rdr *rdr);
t_cmd 	*create_node_cmd(char **cmd, t_rdr *rdr);


/*--- COMMAND ARGS ------------------------------------------------------------*/
char	*alloc_word(char *str);
int		args_len(t_token *token);
char	**space_for_args(t_token *token);
void	get_args(char **args, t_token *token, int *arg_i);


/*--- COMMAND RDRS-------------------------------------------------------------*/
t_rdr	*create_node_rdr(char *file, int type);
void	add_back_rdr(t_rdr **head, char *file, int type);
void 	get_rdr(t_rdr **rdr, t_token *token, unsigned int type);


/*--- HEREDOC -----------------------------------------------------------------*/
void	scan_for_heredoc(t_shell *shell);
char	*prepare_to_heredoc(char *delemetre, t_shell *shell);
void	heredoxing(char **fname, char *dlmtr,int exflag, t_shell *shell);
void	expand_heredoc(char **line, t_shell *shell);
char	*generate_filename(int len);


/*--- ALLOCATION TRACKER ------------------------------------------------------*/
t_address_track	*address_tracker(void);
t_mmtrack		*create_mm_node(void *ptr);
void 			*mm_alloc(size_t size);
void			mm_free(int	which_free);
void 			free_others(void);
void			free_env(void);
void	init_structs_after_free(t_shell *shell);


/*--- PARSING UTILS ------------------------------------------------------*/
int		ft_strlen(char *str);
void	ft_strcpy(char *dst, char *src);
char	*ft_substr(int start, int end, char *str);
int		ft_strcmp(char *s1, char *s2);
char	*str_join(char *old, char *new);
char	*char_join(char *old, char c, int *index);
int		white_space(char c);
int		is_symbole(char c);
int		is_seperator(char c);
int		is_oprt(char *op);
int		is_quote(char c);
int 	is_quoted_str(char *str);

#endif
