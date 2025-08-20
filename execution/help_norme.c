#include "../parsing/minishell.h"

int    command_args(t_cmd *current, t_env **env, int status)
{
    int     result;

    result = status;
    if(current->next)
    {
        result = execute_whith_pipe(current, env, status);
        return(result); // <-- Ajoute ce break pour ne pas exécuter plusieurs fois la pipeline
    }
    else if((current->rdr && (current->rdr->type == RDRIN || 
    current->rdr->type == RDROUT || 
    current->rdr->type == APPND || current->rdr->type == HEREDOC)))
    {
        result = execute_with_redirection(current, env, status);
    }
    else
    {
        if(is_builin_command(current->arg[0]))
            result = execute_builtin(current, env, status);
        else
            result = execute_simple_command(current, env, status);
    }
    return(result);
}

int   help1_red_in_pipe(t_cmd *cmd, t_env **env)
{
    char    *tmp;
    char   **env_array = NULL;

    struct  stat buf;
    if(!cmd || !env || cmd->arg[0] == NULL)
        return(-1);
    if(stat(cmd->arg[0], &buf) == 0)
    {
        if(S_ISDIR(buf.st_mode))
            write(2, "Is a directory\n", 15), exit(126);
    }
    if(access(cmd->arg[0], F_OK) != 0)
    {   
        tmp = ft_strjoin(cmd->arg[0], " : No such file or directory\n");
        write(2, tmp, ft_strlen(tmp)), exit(127);
    }
    if(access(cmd->arg[0], X_OK) != 0)
    {
        tmp = ft_strjoin(cmd->arg[0], " : Permission denied\n");
        write(2, tmp, ft_strlen(tmp)), exit(127);
    }
    env_array = env_to_char_array(*env);
    if(execve(cmd->arg[0], cmd->arg, env_array) == -1)
        perror("execve"), exit(127);
    return(0);
}

int    help2_red_in_pipe(t_cmd *cmd, t_env **env)
{
    char    *path = NULL;
    char    **env_array = NULL;
    char    *tmp = NULL;

    if(!cmd || !env || cmd->arg[0] == NULL)
        return(-1);
    path = get_path_cmd(cmd->arg[0], env);
    if(!path)
    {
        tmp = ft_strjoin(cmd->arg[0]," : Command not found\n");
        write(2, tmp, ft_strlen(tmp)), exit(127);
    }
    else if(!ft_strcmp(path, cmd->arg[0]))
    {
        tmp = ft_strjoin(cmd->arg[0], " : Permission denied\n");
        write(2, tmp, ft_strlen(tmp)), exit(127);
    }
    env_array = env_to_char_array(*env);
    if(!env_array)
        return(free(path), -1);
    if(execve(path, cmd->arg, env_array) == -1)
        perror("execve"), exit(127);
    return(0);
}