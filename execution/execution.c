

#include "../parsing/minishell.h"

int     execute_command(t_cmd *cmd, t_env **env, int status)
{
    t_cmd   *current = NULL;

    if(!cmd || !env)
        return(status);
    current = cmd;
    while(current)
    {
        if(current->arg)
        {
            status = command_args(current, env, status);
            return(status);
        }
        else if((current->rdr && (current->rdr->type == RDRIN || 
            current->rdr->type == RDROUT || 
            current->rdr->type == APPND || current->rdr->type == HEREDOC)))
            {
                status = execute_with_redirection(current, env, status);
                return(status); 
            }
        current = current->next;
    }
    return(status);
}

void    initial_fd_fils(t_fd_fils *fil)
{
    fil->infil = -1;
    fil->outfil = -1;
    fil->save_stdout = dup(1);
    fil->save_strdint = dup(0);
}

void    restore_fd(t_fd_fils *fils)
{
    dup2(fils->save_stdout, 0);
    dup2(fils->save_strdint, 1);
    close(fils->save_stdout);
    close(fils->save_strdint);
}

int     execute_with_redirection(t_cmd *current, t_env **env, int status)
{
    int result;
    t_fd_fils   fils;

    result = 0;
    initial_fd_fils(&fils);
    result = open_check_file(current, &fils);
    if(result == -1 || result == 1)
    {
        restore_fd(&fils);
        return(result);
    }
    if(current && current->arg)
        result = execute_simple_command(current, env, status);
    restore_fd(&fils);
    return(result);
}


int     open_check_file(t_cmd *cmd, t_fd_fils *fil)
{
	t_rdr *red = cmd->rdr;
    int status;

    while (red)
    {
        if(red->type == RDRIN)
            status = rdrin(red, fil);
        else if(red->type == RDROUT)
            status = rdrrout(red, fil);
        else if(red->type == APPND)
            status = appnd(red, fil);
        else if(red->type == HEREDOC)
            status = heredoc(red);
        else
            return(-1);
        red = red->next;
    }
    return(status);
}

int     child_process(t_cmd *cmd, t_env **env)
{
    if(!cmd || !env)
        return(-1);
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    if(!ft_strchr(cmd->arg[0], '/'))
    {
        if(help1_red_in_pipe(cmd, env) == -1)
            return(-1);
    }
    else
    {
        if(help2_red_in_pipe(cmd, env) == -1)
            return(-1);
    }
    return(0);
}

int     execute_simple_command(t_cmd *cmd, t_env **env, int status)
{
    pid_t   pid;

    if(!env || !cmd || !cmd->arg || !cmd->arg[0])
        return(-1);
    if(is_builin_command(cmd->arg[0]))
        return (execute_builtin(cmd, env, status));
    else
    {
        pid = fork();
        if(pid == -1)
            return(perror("fork"), -1);
        if(pid == 0) // partie d'enfant 
        {
            if(child_process(cmd, env) == -1)
                return(-1);
        }
        else if(pid > 0) //parent
        {
            waitpid(pid, &status, 0);
            if(WIFEXITED(status))
                status = WEXITSTATUS(status);
            else if(WIFSIGNALED(status))
                status = 128 + WTERMSIG(status);
        }
    }
    return(status);
}

int     execute_builtin(t_cmd *cmd, t_env **env , int last_code)
{
    int     status; //

    status = last_code; // initialiser le status avec le dernier code de sortie
    if(!cmd->arg || !env || !cmd->arg[0])
        return(-1);
    if(ft_strcmp(cmd->arg[0], "echo") == 0)
        status = echo_fonc(cmd->arg, last_code);
    else if(ft_strcmp(cmd->arg[0], "cd") == 0)
        status = fonc_cd(cmd->arg, *env);
    else if(ft_strcmp(cmd->arg[0], "pwd") == 0)
        status = fonc_pwd(cmd->arg, *env);
    else if(ft_strcmp(cmd->arg[0], "export") == 0)
        status = fonc_export(cmd->arg, env);
    else if(ft_strcmp(cmd->arg[0], "unset") == 0)
        status = unset_fonc(cmd->arg, env);
    else if(ft_strcmp(cmd->arg[0], "env") == 0)
        status = env_fonc(cmd->arg, *env);
    else if(ft_strcmp(cmd->arg[0], "exit") == 0)
        status = exit_fonc(cmd->arg, last_code);
    return(status);
}

int     is_builin_command(char *cmd)
{
    if(ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0 || 
       ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0 || 
       ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0 || 
       ft_strcmp(cmd, "exit") == 0)
        return(1);
    return(0);
}

