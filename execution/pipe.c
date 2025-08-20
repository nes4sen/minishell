/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdelhak <abdelhak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:19:45 by aait-laf          #+#    #+#             */
/*   Updated: 2025/08/20 18:06:22 by abdelhak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int     count_nuber_cmd(t_cmd *cmd)
{
    int     count;

    if(!cmd)
        return(0);
    if(!cmd->next)
        return(1);
    count = 0;
    while(cmd)
    {
        count++;
        cmd = cmd->next;
    }
    return(count);
}

int execute_whith_pipe(t_cmd *cmd, t_env **env, int status)
{
    int pipefd[2];
    int prev_pipe = -1;
    pid_t pid;
    int child_status;
    int final_status = 0;
    t_cmd *current = cmd;
    
    
    int nb_cmd = count_nuber_cmd(cmd);
    pid_t pids[nb_cmd];
    int i = 0;
    if (!cmd)
        return (-1);
    while (current)
    {
        if (current->next)
        {
            if (pipe(pipefd) == -1)
            {
                perror("pipe");
                if (prev_pipe != -1)
                    close(prev_pipe);
                return (-1);
            }
        }
        
        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            if (prev_pipe != -1)
            close(prev_pipe);
            if (current->next)
            {
                close(pipefd[0]);
                close(pipefd[1]);
            }
            return (-1);
        }
        if (pid == 0) 
        {
            signal(SIGINT, SIG_DFL);
            signal(SIGQUIT, SIG_DFL);
            if (prev_pipe != -1)
            {
                dup2(prev_pipe, STDIN_FILENO);
                close(prev_pipe);
            }
            if (current->next)
            {
                dup2(pipefd[1], STDOUT_FILENO);
                close(pipefd[0]);
                close(pipefd[1]);
            }
            if (current->rdr)
            {
                t_fd_fils fils;
                int stus;
                
                initial_fd_fils(&fils);
                stus = open_check_file(current, &fils);
                if (stus == -1 || stus == 1)
                    exit(1);
            }
            if (is_builin_command(current->arg[0]))
            {
                int builtin_status = execute_builtin(current, env, status);
                exit(builtin_status);
            }
            else
            {
                if (red_in_pipe(current, env) != 0)
                {
                    int red_status = red_in_pipe(current, env);
                    exit(red_status);
                }
                exit(1);
            }
        }
        else
        {
            pids[i++] = pid;
            if (prev_pipe != -1)
                close(prev_pipe);
            if (current->next)
            {
                close(pipefd[1]);
                prev_pipe = pipefd[0];
            }
            else
                prev_pipe = -1;
            
            current = current->next;
        }
    }
    i = 0;
    while (i < nb_cmd) 
    {
        waitpid(pids[i], &child_status, 0);
        if (i == nb_cmd - 1) 
        {
            if (WIFEXITED(child_status)) 
            {
                final_status = WEXITSTATUS(child_status);
            } 
            else if (WIFSIGNALED(child_status)) 
            {
                if (WTERMSIG(child_status) == SIGINT)
                    write(2, "\n", 1);
                else if (WTERMSIG(child_status) == SIGQUIT)
                    write(2, "Quit\n", 5);
                final_status = 128 + WTERMSIG(child_status);
            }
        }
        i++;
    }
    setup_signals();
    return (final_status);
}

void    close_other_fil(int pipes[][2], int nbr_pipe, int fd1, int fd2)
{
    int     i = 0;
    while(i < nbr_pipe)
    {
        if(pipes[i][0] != fd1 && pipes[i][0] != fd2)
            close(pipes[i][0]);
        if(pipes[i][1] != fd1 && pipes[i][1] != fd2)
            close(pipes[i][1]);
        i++;
    }
}

char    *get_path(t_env **env)
{
    t_env   *tmp;
    
    tmp = *env;
    while(tmp)
    {
        if(ft_strncmp(tmp->name, "PATH", 4) == 0)
        return (tmp->value);
        tmp = tmp->next;
    }
    return (NULL);
}



char   *get_path_cmd(char *cmd, t_env **env)
{
    int i;
    char *path;
    char *full_path = NULL;
    char *save = NULL;
    char **arg;

    path = get_path(env);
    if(!path || !*path)
    {
        ft_putstr_fd(cmd, 2), ft_putstr_fd(": No such file or directory\n", 2);
        exit(127);
    }
    arg = ft_split(path, ':');
    if(!arg || !cmd[0])
        return (NULL);
    i = 0;
    while (arg[i])
    {
        full_path = ft_strjoin(arg[i], "/");
        full_path = ft_strjoin(full_path, cmd);
        if(!full_path)
            return(NULL);
        if(access(full_path, F_OK) == 0)
        {
            if(access(full_path, X_OK) == 0)
                return (full_path);            
            else
                save = cmd;
            // f_free(arg);
        }
        i++;
    }
    return (save);
}


// Pourquoi le status est géré dans le parent ?
// Le processus enfant exécute la commande (avec execve).
// Quand il termine, il quitte avec un code de sortie (exit(n)).

// Le processus parent (celui qui a fait le fork) utilise waitpid pour attendre la fin de l’enfant et récupérer son code de sortie dans la variable status.

// Pourquoi ?

// Le parent doit savoir si la commande s’est bien exécutée ou non (pour afficher le bon code de retour, gérer les erreurs, etc).
// Le shell (le parent) doit retourner le code de la dernière commande exécutée à l’utilisateur.
// En résumé :
// L’enfant : exécute la commande et termine avec un code de sortie.
// Le parent : récupère ce code avec waitpid et le met dans status.
// C’est le comportement standard d’un shell Unix :
// Le shell (parent) affiche ou utilise le code de sortie des commandes (enfants).














// int    execute_whith_pipe(t_cmd *cmd, t_env **env, int status)
// {
//     int pipe_fd[2];
//     pid_t pid;
//     char *path;

//     if(pipe(pipe_fd) == -1)
//     {
//         perror("pipe");
//         return (-1);
//     }
//     id = fork();
//     if (id == -1)
//     {
//         perror("fork");
//         return (-1);
//     }
//     else if(id == 0)
//     {
//         // pour premier pipe , infil rénisialise à -1
//         if(cmd->infil == -1)
//         {
//             dup2(pipe_fd[1], STDOUT_FILENO);
//             cmd->infil = pipe_fd[0];
//             cmd->outfil = pipe_fd[1];
//             close(pipe_fd[0]);
//             close(pipe_fd[1]);
//         }
//         // pour pipe milieu
//         else if(cmd->infil != -1 && cmd->next)
//         {
//             dup2(cmd->infil, STDIN_FILENO);
//             dup2(cmd->outfil, STDOUT_FILENO);
//             cmd->infil = pipe_fd[0];
//             cmd->outfil = pipe_fd[1];
//             close(pipe_fd[0]);
//             close(pipe_fd[1]);
//         }
//         // pour pipe dernier    
//         else
//         {
//             dup2(cmd->infil, STDIN_FILENO);
//             close(pipe_fd[0]);
//             close(pipe_fd[1]);
//         }
//         path = get_path_cmd(cmd->arg[0]);
//         if(!path)
//         {            
//             fprintf(stderr, "Command not found: %s\n", cmd->arg[0]);
//             exit(1);
//         }
        // if(execve(path, cmd->arg, env) == -1)
        // {
        //     perror("execve");
        //     exit(1);
        // }
//     }
//     else
//     {
//         if(i < nbr_pipe)
//         {
//             close(pipes[0]);
//             close(pipes[1]);
//         }
//         waitpid(id, NULL, 0);
//         cmd = cmd->next;
//         i++;
//     }
    
// }