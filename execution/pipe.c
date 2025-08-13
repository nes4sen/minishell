/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-laf <aait-laf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:19:45 by aait-laf          #+#    #+#             */
/*   Updated: 2025/08/13 05:02:57 by aait-laf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
    int     nbr_pipe;
    int     i = 0;
    char    *path = NULL;
    int     (*pipes)[2];
    pid_t   *pids;
    pid_t   id;

    if(!cmd)
        return(-1);
    
    nbr_pipe = count_nuber_cmd(cmd) - 1;
    if (nbr_pipe <= 0)
        return execute_simple_command(cmd, env, status);

    // Allouer mémoire pour pipes et PIDs
    pipes = malloc(sizeof(int[2]) * nbr_pipe);
    pids = malloc(sizeof(pid_t) * (nbr_pipe + 1));
    if(!pipes || !pids)
        return(-1);

    // Créer tous les pipes
    i = 0;
    while(i < nbr_pipe)
    {
        if(pipe(pipes[i]) == -1)
        {
            perror("pipe");
            free(pipes);
            free(pids);
            return(-1);
        }
        i++;
    }

    // Créer tous les processus
    i = 0;
    t_cmd *current = cmd;
    while(current && i <= nbr_pipe)
    {
        id = fork();
        if(id == -1)
        {
            perror("fork");
            free(pipes);
            free(pids);
            return(-1);
        }
        
        if(id == 0) // Processus enfant
        {
            signal(SIGINT, SIG_DFL);
            signal(SIGQUIT, SIG_DFL);
            
            // Configuration des pipes selon la position
            if(i == 0) // Premier processus
            {
                if(nbr_pipe > 0)
                {
                    dup2(pipes[0][1], STDOUT_FILENO);
                }
            }
            else if(i == nbr_pipe) // Dernier processus
            {
                dup2(pipes[i-1][0], STDIN_FILENO);
            }
            else // Processus du milieu
            {
                dup2(pipes[i-1][0], STDIN_FILENO);
                dup2(pipes[i][1], STDOUT_FILENO);
            }
            
            // Fermer TOUS les descripteurs de pipes dans l'enfant
            int j = 0;
            while(j < nbr_pipe)
            {
                close(pipes[j][0]);
                close(pipes[j][1]);
                j++;
            }
            
            // Gérer les redirections
            if(current->rdr)
            {
                // t_rdr *red = current->rdr;
                execute_with_redirection(cmd, env, status);
                // while(red)
                // {
                //     if(open_check_file(red) == -1)
                //     {
                //         free(pipes);
                //         free(pids);
                //         exit(1);
                //     }
                //     red = red->next;
                // }
            }
            
            // Exécuter la commande
            if(is_builin_command(current->arg[0]))
            {
                int builtin_status = execute_builtin(current, env, status);
                free(pipes);
                free(pids);
                exit(builtin_status);
            }
            else
            {
                if(!ft_strchr(current->arg[0], '/'))
                {
                    struct  stat buf;
                    if(stat(current->arg[0], &buf) == 0)
                    {
                        if(S_ISDIR(buf.st_mode))
                        {
                            write(2, "Is a directory\n",15);
                            free(pipes);
                            free(pids);
                            exit(126);
                        }
                    }
                    if(access(current->arg[0], F_OK) != 0)
                    {
                        printf("%s: Nosuch file or directory\n", current->arg[0]);
                        free(pipes);
                        free(pids);
                        exit(127);
                    }
                    if(access(current->arg[0], X_OK) != 0)
                    {
                        printf("%s: Permission denied\n", current->arg[0]);
                        free(pipes);
                        free(pids);
                        exit(127);
                    }
                    char **env_array = env_to_char_array(*env);
                    if(execve(current->arg[0], current->arg, env_array) == -1)
                    {
                        perror("");
                        free(pipes);
                        free(pids);
                        exit(127);
                    }
                }
                else
                {
                    
                    path = get_path_cmd(current->arg[0], env);
                    if(!path)
                    {
                        fprintf(stderr, "Command not found: %s\n", current->arg[0]);
                        free(pipes);
                        free(pids);
                        exit(127);
                    }
                    else if(!ft_strcmp(path, current->arg[0]))
                    {
                        fprintf(stderr, "%s: Permission denied\n", cmd->arg[0]);
                        free(pipes);
                        free(pids);
                        exit(127);
                    }
                    char **env_array = env_to_char_array(*env);
                    execve(path, current->arg, env_array);
                    
                    // Si on arrive ici, execve a échoué
                    perror("execve");
                    free(path);
                    free_env_array(env_array);
                    free(pipes);
                    free(pids);
                    exit(1);
                }
            }
        }
        else // Processus parent
        {
            pids[i] = id;
            current = current->next;
            i++;
        }
    }
    
    // IMPORTANT: Fermer tous les pipes dans le parent
    i = 0;
    while(i < nbr_pipe)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
        i++;
    }
    
    // Attendre tous les processus enfants
    int final_status = 0;
    i = 0;
    while(i <= nbr_pipe)
    {
        signal(SIGINT, SIG_IGN);
        int child_status;
        waitpid(pids[i], &child_status, 0);
        
        // Le status de retour est celui du dernier processus
        
            if(WIFEXITED(child_status))
                final_status = WEXITSTATUS(child_status);
            else 
            {
                if (WTERMSIG(child_status) == SIGINT)
                { 
                    write(2, "\n", 1);
                    final_status = 130;
                    setup_signals();
                    return (final_status);

                }
                else if (WTERMSIG(child_status) == SIGQUIT)
                {
                    write(2, "Quit\n", 5);
                    final_status = 131;   
                    setup_signals();
                    return (final_status);
                }
            }
        i++;
    }
    setup_signals();
    return(final_status);
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

// pour pipe mais la methode de cree chaque pipe 



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
    if(!path)
    {
        printf("%s: Nosuch file or directory\n", cmd);
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
            {
                return (full_path);
            }
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