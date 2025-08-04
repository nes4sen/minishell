

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <ctype.h>
#include <readline/readline.h>
#include <readline/history.h>


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





typedef struct s_mmtrack
{
	void *ptr;
	struct s_mmtrack *next;
} t_mmtrack;

typedef struct s_mmenv
{
	void			*ptr;
	struct s_mmev	*next;
}t_mmenv;

typedef struct s_shell
{
	char		*line;
	t_token		*tokens;
	t_env		*env;
	t_cmd		*cmd;
	t_mmtrack	*mmtrack;
	int			exit_s;
}t_shell;

/*-----------mmtracker----------*/
t_mmtrack *create_mm_node(void *ptr);
void *mm_alloc(size_t size, t_mmtrack **mm_head);
void mm_free(t_mmtrack **mm_head);

/*-----------expand----------*/
void	expand_env_vars(t_shell *shell);
void	remove_quote(t_token *token);
char 	*extract_var_name(char *str);
char 	*find_env_var(t_env *env, char *var);
int 	is_expandable(char *str);


/*-----------join-------------*/
char *str_join(char *old, char *new);
char *char_join(char *old, char c, int *index);


/*----------extoken_list----------*/
void build_exlist(t_extoken **exhead, t_token *token);
void add_back_extoken(t_extoken **head, char *str, int stat);
t_extoken *create_extoken_list(char *str, int stat);




int		ft_strlen(char *str);
void	ft_strcpy(char *dst, char *src);
void	parser(t_shell *shell);
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
int		idx_nod(t_env *env);


/*-------|>---token list---<|--------*/
void 	token_add_back(t_token **head, char *token, t_type type);
t_token	*creat_token(char *token, t_type type);


/*_______|---tokenizer---|_________*/
void	tokenizer(t_shell *shell);
char	*get_token(char **str);
void	get_type(t_token *tokens);
void	get_next_type(t_token *tokens);



/*________|---token utils---|_________*/
char	*ft_substr(int start, int end, char *str);
int		ft_strcmp(char *s1, char *s2);
int		white_space(char c);

/*________|---utility functions---|_________*/
char	*ft_strjoin(char *dest, char *src);
char	*ft_strdup(const char *s1);
int		ft_strncmp(char *s1, char *s2, size_t n);
int		ft_atoi(const char *str);
char	**ft_split(const char *s, char c);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
void	print_str(char *str);
char	*ft_strcat(char *dest, const char *src);


/*_________|---rdr list---|__________*/
t_rdr	*create_node_rdr(char *file, int type, int fd);
void	add_back_rdr(t_rdr **head, char *file, int type, int fd);
void 	get_rdr(t_rdr **rdr, t_token *token, unsigned int type);


/*_________|---command list---|________*/
void	build_cmd(t_shell *shell);
void	add_back_cmd(t_cmd **head, char **cmd, t_rdr *rdr);
t_cmd 	*create_node_cmd(char **cmd, t_rdr *rdr);

/*------------cmd_args---------------*/
char *alloc_word(char *str);
int args_len(t_token *token);
char **space_for_args(t_token *token);
void	get_args(char **args, t_token *token, int *arg_i);


/*__________is_functions________*/

int	is_symbole(char c);
int	is_seperator(char c);
int	is_oprt(char *op);
int	is_quote(char c);

/*__________builtins________*/
// cd 
int     fonc_cd(char **arg, t_env *env);
void    update_env(t_env **env, const char *name, const char *value);
int     get_nbr_arg(char    **arg);
int    cd_zero_arg(char *tmp, char *pwd_now, char *cur,t_env *env);
int    cd_whith_1p(char *pwd_now, char *cur, t_env *env);
int    cd_whith_2p(char *pwd_now, char *cur, t_env *env);
int    cd_with_arg(char **arg, char *pwd_now, char *cur, t_env *env);
char   *find_home_repert(t_env *env);

// echo 
int     echo_fonc(char **arg);
int     echo_check_n(char **arg, int *flag_newline, int i);

// env
int     env_fonc(char **arg, t_env *env);
int     help_env_fonc(t_env *env);

// exit
int     exit_fonc(char **arg, int last_code);
void    help_exit_fonc(char **arg, int exit_code);

// export
int     fonc_export(char **arg,  t_env **env);
char    *get_var_name(char *str);
int     check_var_exist_env(t_env *env, char *name);
char    *get_var_value(char *str);
int     mak_as_export(t_env **env, char *str);
void    export_error(char *str);
int     is_valid_name(char *str);
int     has_equal_sign(char *str);
void    updat_env(t_env *env, char *name, char *value);
void    add_double_quotes(char *value, char *name, t_env *env);
void    print_env(t_env *env);
int     var_with_equal(char **arg, int i, t_env **env);
int     var_no_value(char **arg, int i, t_env **env);
// pwd
int		fonc_pwd(char **arg, t_env *env);
void	print_repert(t_env *env);

//unset
int     unset_fonc(char **arg, t_env **env);
int     find_idex_var_env(char *str, t_env *env);
void     indx_nods(t_env **env);
void	delete_var_env(int idx, t_env **env);
void    delete_first_node(t_env **env);

/*__________PIPE________*/
int     execute_whith_pipe(t_cmd *cmd, t_env **env, int status);
int     count_nuber_cmd(t_cmd *cmd);
void    close_other_fil(int pipe[][2], int nbr_pipe, int fd1, int fd2);
char    *get_path(t_env **env);
char    *get_path_cmd(char *cmd, t_env **env);

/*__________SPLIT________*/
int     word_count(char const *s, char c);
char    *alloc_words(char const *s, char c);
char    **f_free(char **p);

/*__________Redirection________*/
int     execute_with_redirection(t_cmd *current, t_env **env, int status);
int     open_check_file(t_rdr *red);

/*__________execution________*/
int     execute_command(t_cmd *cmd, t_env **env, int status);
int     execute_simple_command(t_cmd *cmd, t_env **env, int status);
int     execute_builtin(t_cmd *cmd, t_env **env , int last_code);
int     is_builin_command(char *cmd);
char    **env_to_char_array(t_env *env);
void    free_env_array(char **env_array);

/*__________signal handlers________*/
void    handler_ctrl_c(int sig);
void    handler_ctrl_d(int sig);
void    handler_ctrl_slash(int sig);
void    setup_signals(void);

#endif  