#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "parsing.h"

typedef struct s_pipe_data
{
    int *prev_pipe;
    int pipefd[2];
    pid_t *pids;
    int *cmd_index;
} t_pipe_data;


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
	struct s_mmenv	*next;
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
char	*ft_strcat(char *dest, const char *src);



int     fonc_cd(char **arg, t_env *env);
void    update_env(t_env **env, const char *name, const char *value);
int     get_nbr_arg(char    **arg);
int    cd_zero_arg(char *tmp, char *pwd_now, char *cur,t_env *env);
int    cd_whith_1p(char *pwd_now, char *cur, t_env *env);
int    cd_whith_2p(char *pwd_now, char *cur, t_env *env);
int    cd_with_arg(char **arg, char *pwd_now, char *cur, t_env *env);
char   *find_home_repert(t_env *env, char *str);
void    ft_putstr_fd(char *s, int fd);
int 	count_len(t_env *temp);

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
void     indx_nods(t_env **env);
void	delete_var_env(char *name, t_env **env);
void    delete_first_node(t_env **env);

/*__________PIPE________*/
int     execute_whith_pipe(t_cmd *cmd, t_env **env, int status);
int     count_number_cmd(t_cmd *cmd);
void    close_other_fil(int pipe[][2], int nbr_pipe, int fd1, int fd2);
char    *get_path(t_env **env);
char    *get_path_cmd(char *cmd, t_env **env);
int     red_in_pipe(t_cmd *cmd, t_env **env);
int    help2_red_in_pipe(t_cmd *cmd, t_env **env);
int   help1_red_in_pipe(t_cmd *cmd, t_env **env);
int create_pipe_if_needed(t_cmd *current, int pipefd[2], int prev_pipe);
void setup_child_redirections(t_cmd *current, int prev_pipe, int pipefd[2]);
void execute_child_command(t_cmd *current, t_env **env, int status);
int     child_process(t_cmd *cmd, t_env **env);


/*__________SPLIT________*/
int     word_count(char const *s, char c);
char    *alloc_words(char const *s, char c);
char    **f_free(char **p);

/*__________Redirection________*/
int     execute_with_redirection(t_cmd *current, t_env **env, int status);
int     open_check_file(t_cmd *cmd, t_fd_fils *fil);
void    initial_fd_fils(t_fd_fils *fil);
int     rdrin(t_rdr *red, t_fd_fils *fil);
int     rdrrout(t_rdr *red, t_fd_fils *fil);
int     appnd(t_rdr *red, t_fd_fils *fil);
int     heredoc(t_rdr *red);

/*__________execution________*/
int     execute_command(t_cmd *cmd, t_env **env, int status);
int     execute_simple_command(t_cmd *cmd, t_env **env, int status);
int     execute_builtin(t_cmd *cmd, t_env **env , int last_code);
int     is_builin_command(char *cmd);
char    **env_to_char_array(t_env *env);
int		command_args(t_cmd *current, t_env **env, int status);
void    restore_fd(t_fd_fils *fils);
int		part_parent(int pid, int status);

/*__________signal handlers________*/
void    handler_ctrl_c(int sig);
void    setup_signals(void);
void 	handle_segnal_herd(int sig);

int     ft_strchr(char *str, char c);

/*__________additional utility functions________*/
int     idx_nod(t_env *env);
void    add_back_env(t_env **env, char *name, char *value, int index);
int     ft_strcmp(char *s1, char *s2);

#endif
