#ifndef MINISHELL_H
#define MINISHELL_H



#include "parsing.h"

typedef struct s_fd_fils
{
	int	infil;
	int	outfil;
	int save_stdout;
	int save_strdint;
}t_fd_fils;

typedef struct s_mmenv
{
	void			*ptr;
	struct s_mmev	*next;
}t_mmenv;

extern int g_sigint;

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



int     fonc_cd(char **arg, t_env *env);
void    update_env(t_env **env, const char *name, const char *value);
int     get_nbr_arg(char    **arg);
int    cd_zero_arg(char *tmp, char *pwd_now, char *cur,t_env *env);
int    cd_whith_1p(char *pwd_now, char *cur, t_env *env);
int    cd_whith_2p(char *pwd_now, char *cur, t_env *env);
int    cd_with_arg(char **arg, char *pwd_now, char *cur, t_env *env);
char   *find_home_repert(t_env *env);

// echo 
int     echo_fonc(char **arg, int status);
int     echo_check_n(char **arg, int *flag_newline, int i);

// env
int     env_fonc(char **arg, t_env *env);
int     help_env_fonc(t_env *env);

// exit
int     exit_fonc(char **arg, int last_code);
int    help_exit_fonc(char **arg, int exit_code);

// export
int     fonc_export(char **arg,  t_env **env);
char    *get_var_name(char *str);
int     check_var_exist_env(t_env *env, char *name);
char    *get_var_value(char *str);
int     mak_as_export(t_env **env, char *str);
void    export_error(char *str);
int     is_valid_name(char *str);
int     has_equal_sign(char *str);
void    updat_env(t_env **env, char *name, char *value);
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
void	delete_var_env(char *name, t_env **env);
void    delete_first_node(t_env **env);

/*__________PIPE________*/
int     execute_whith_pipe(t_cmd *cmd, t_env **env, int status);
int     count_nuber_cmd(t_cmd *cmd);
void    close_other_fil(int pipe[][2], int nbr_pipe, int fd1, int fd2);
char    *get_path(t_env **env);
char    *get_path_cmd(char *cmd, t_env **env);
int     red_in_pipe(t_cmd *cmd, t_env **env);

/*__________SPLIT________*/
int     word_count(char const *s, char c);
char    *alloc_words(char const *s, char c);
char    **f_free(char **p);

/*__________Redirection________*/
int     execute_with_redirection(t_cmd *current, t_env **env, int status);
int     open_check_file(t_cmd *cmd, t_fd_fils *fil);
void    initial_fd_fils(t_fd_fils *fil);

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

int     ft_strchr(char *str, char c);

#endif  