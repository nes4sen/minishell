

#include "../parsing/minishell.h"

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
            else if((current->rdr && (current->rdr->type == RDRIN || 
            current->rdr->type == RDROUT || 
            current->rdr->type == APPND)) || current->rdr->type == HEREDOC)
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
        //Gérer les redirections
        else if((current->rdr && (current->rdr->type == RDRIN || 
            current->rdr->type == RDROUT || 
            current->rdr->type == APPND)) || current->rdr->type == HEREDOC)
            {
                status = execute_with_redirection(current, env, status);
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
    int result = 0;
    //  int save_fd;
    // t_rdr *red;
    t_fd_fils   fils;

    // red = current->rdr;
    initial_fd_fils(&fils);
    result = open_check_file(current, &fils);
    if(result == -1 || result == 1)
    {
        restore_fd(&fils);
        return(result);
    }
    //     red = red->next;
    // }
    if(current && current->arg)
        result = execute_simple_command(current, env, status);
    restore_fd(&fils);
    return(result);
}


int     open_check_file(t_cmd *cmd, t_fd_fils *fil)
{
	t_rdr *red = cmd->rdr;
    struct stat info;
    int fd;

    // printf("%s | %d\n", cmd->heredox, red->type);
    // printf("salam\n");
    // printf("%s\n", cmd->heredox);
    while (red)
    {
        if(red->type == RDRIN)
        {
            if(stat(red->file, &info) != 0)
                return(printf("%s :no such file or directory\n", red->file), 1);
            fil->outfil = open(red->file, O_RDONLY);
            if(fil->outfil == -1)
            {
                perror("open");
                return(-1);
            }
            // fil->save_stdout = dup(0);
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
            // fil->save_strdint = dup(1);
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
            // fil->save_strdint = dup(1);
            dup2(fil->infil, 1);
            close(fil->infil);
        }
        else if(red->type == HEREDOC)
        {
            fd = open(red->file, O_RDONLY);
            // printf("test\n");
	    	if(fd == -1)
	    	{
	    		perror("open");
	    		return(-1);
	    	}
            // printf("fd = %d\n", fd);
	    	// fil->save_stdout = dup(0);
	    	dup2(fd, 0);
	    	close(fd);
        }
        else
            return(-1);
        red = red->next;
    }
    
    return(0);
}

int     execute_simple_command(t_cmd *cmd, t_env **env, int status)
{
    pid_t   pid;
    char    *path = NULL;
    char    **env_array = NULL;

    if(!env || !cmd )
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

            if(!ft_strchr(cmd->arg[0], '/'))
            {
                struct  stat buf;
                if(stat(cmd->arg[0], &buf) == 0)
                {
                    if(S_ISDIR(buf.st_mode))
                    {
                        write(2, "Is a directory\n",15);
                        exit(126);
                    }
                }
                if(access(cmd->arg[0], F_OK) != 0)
                {
                    printf("%s: Nosuch file or directory\n", cmd->arg[0]);
                    exit(127);
                }
                if(access(cmd->arg[0], X_OK) != 0)
                {
                    printf("%s: Permission denied\n", cmd->arg[0]);
                    exit(127);
                }
                env_array = env_to_char_array(*env);
                if(execve(cmd->arg[0], cmd->arg, env_array) == -1)
                {
                    perror("");
                    exit(127);
                }
            }
            else
            {
                path = get_path_cmd(cmd->arg[0], env);
                if(!path)
                {
                    fprintf(stderr, "Command not found: %s\n", cmd->arg[0]);
                    exit(127);
                }
                else if(!ft_strcmp(path, cmd->arg[0]))
                {
                    fprintf(stderr, "%s: Permission denied\n", cmd->arg[0]);
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