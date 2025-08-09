

#include "../minishell.h"

int     execute_command(t_cmd *cmd, t_env **env, int status)
{
    t_cmd   *current = NULL;

    if(!cmd || !env)
        return(-1);
    current = cmd;
    while(current)
    {
        // vérifier si c'est une commande (CMD)
        if(current->arg && current->arg[0])
        {
            // Gérer les pipes (à implémenter plus tard)
            if(current->next)
            {
                status = execute_whith_pipe(current, env, status);
                return(status); // <-- Ajoute ce break pour ne pas exécuter plusieurs fois la pipeline
            }
            // Gérer les redirections
            else if(current->rdr && (current->rdr->type == RDRIN || 
                current->rdr->type == RDROUT || 
                current->rdr->type == APPND || 
                current->rdr->type == HEREDOC))
                {
                    status = execute_with_redirection(current, env, status);
                }
            else
            {
                if(is_builin_command(current->arg[0]))
                    status = execute_builtin(current, env, status);
                else
                    status = execute_simple_command(current, env, status);
            }
        }
        current = current->next;
    }
    return(status);
}

void    initial_fd_fils(t_fd_fils *fil)
{
    fil->infil = -1;
    fil->outfil = -1;
    fil->save_stdout = -1;
    fil->save_strdint = -1;
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
    // int save_fd;
    t_rdr *red;
    t_fd_fils   fils;
    
    red = current->rdr;
    initial_fd_fils(&fils);
    while(red)
    {
        if(open_check_file(red, &fils) ==  -1)
        {
            return(-1);
        }
        red = red->next;
    }
    result = execute_simple_command(current, env, status);
    restore_fd(&fils);
    return(result);
}


int     open_check_file(t_rdr *red, t_fd_fils *fil)
{

    if(red->type == RDRIN)
    {
        fil->outfil = open(red->file, O_RDONLY);
        if(fil->outfil == -1)
        {
            perror("open");
            return(-1);
        }
        fil->save_stdout = dup(0);
        dup2(fil->outfil, 0);
        close(fil->outfil);
    }
    else if(red->type == RDROUT)
    {
        fil->infil = open(red->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if(fil->infil == -1)
        {
            perror("open");
            return(-1);
        }
        fil->save_strdint = dup(1);
        dup2(fil->infil, 1);
        close(fil->infil);
    }
    else if(red->type == APPND)
    {
        fil->infil = open(red->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if(fil->infil == -1)
        {
            perror("open");
            return(-1);
        }
        fil->save_strdint = dup(1);
        dup2(fil->infil, 1);
        close(fil->infil);
    }
    else if(red->type == HEREDOC)
    {
        if(red->fd == -1)
            return(-1);
        fil->save_stdout = dup(0);
        dup2(red->fd, 0);
        close(red->fd);
    }
    else
        return(-1);
    return(0);
}

int     execute_simple_command(t_cmd *cmd, t_env **env, int status)
{
    pid_t   pid;
    char    *path = NULL;
    char    **env_array = NULL;

    if(!env || !cmd)
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
            signal(SIGINT, SIG_DFL);
            signal(SIGQUIT, SIG_DFL);
            path = get_path_cmd(cmd->arg[0], env);
            if(!path)
            {
                fprintf(stderr, "Command not found: %s\n", cmd->arg[0]);
                exit(127);
            }
            env_array = env_to_char_array(*env);
            if(!env_array)
                return(free(path), -1);
            if(execve(path, cmd->arg, env_array) == -1)
            {
                perror("execve");
                // free(path);
                // free_env_array(env_array);
                exit(127);
            }
        }
        else if(pid > 0) //parent
            waitpid(pid, &status, 0);
    }
    // Note: path est alloué et libéré dans le processus enfant
    // Le parent ne doit pas le libérer
    return(status);
}

int     execute_builtin(t_cmd *cmd, t_env **env , int last_code)
{
    int     status; //

    status = last_code; // initialiser le status avec le dernier code de sortie
    if(!cmd || !cmd->arg || !env)
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

int     free_cmd_list(t_cmd *cmd)
{
    t_cmd   *tmp;

    while(cmd)
    {
        tmp = cmd;
        cmd = cmd->next;
        free(tmp->arg);
        free(tmp);
    }
    return(0);
}