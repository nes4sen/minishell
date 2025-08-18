/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-laf <aait-laf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:19:45 by aait-laf          #+#    #+#             */
/*   Updated: 2025/08/18 16:20:12 by aait-laf         ###   ########.fr       */
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
    int pipefd[2];         // Un seul pipe à la fois
    int prev_pipe = -1;    // Pour stocker le descripteur de lecture du pipe précédent
    pid_t pid;
    int child_status;
    int final_status = 0;
    t_cmd *current = cmd;
    
    if (!cmd)
        return (-1);
    
    // Pour chaque commande dans le pipeline
    while (current)
    {
        // Créer un nouveau pipe si ce n'est pas la dernière commande
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
        
        if (pid == 0) // Processus enfant
        {
            signal(SIGINT, SIG_DFL);
            signal(SIGQUIT, SIG_DFL);
            
            // 1. D'abord, configurer l'entrée depuis le pipe précédent si nécessaire
            if (prev_pipe != -1)
            {
                dup2(prev_pipe, STDIN_FILENO);
                close(prev_pipe);
            }
            
            // 2. Configurer la sortie vers le nouveau pipe si ce n'est pas la dernière commande
            if (current->next)
            {
                dup2(pipefd[1], STDOUT_FILENO);
                close(pipefd[0]);
                close(pipefd[1]);
            }
            
            // 3. Appliquer les redirections pour cette commande
            if (current->rdr)
            {
                t_fd_fils fils;
                int stus;

                initial_fd_fils(&fils);
                stus = open_check_file(current, &fils);
                if (stus == -1 || stus == 1)
                    exit(1);
            }
            
            // 4. Exécuter la commande
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
                // Ajouter ici le code qui exécute la commande non-builtin
                // ...
                exit(1); // En cas d'échec d'exécution
            }
        }
        else // Processus parent
        {
            // Fermer le descripteur de lecture du pipe précédent s'il existe
            if (prev_pipe != -1)
                close(prev_pipe);
            
            // Si ce n'est pas la dernière commande, fermer l'écriture du pipe actuel
            // et sauvegarder la lecture pour la prochaine itération
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
    
    // Attendre tous les processus enfants
    current = cmd;
    while (current)
    {
        signal(SIGINT, SIG_IGN);
        wait(&child_status);
        
        if (WIFEXITED(child_status))
            final_status = WEXITSTATUS(child_status);
        else if (WIFSIGNALED(child_status))
        {
            if (WTERMSIG(child_status) == SIGINT)
            {
                write(2, "\n", 1);
                final_status = 130;
            }
            else if (WTERMSIG(child_status) == SIGQUIT)
            {
                write(2, "Quit\n", 5);
                final_status = 131;
            }
        }
        
        current = current->next;
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
    if(!path || !*path)
    {
        printf("%s: No such file or directory\n", cmd);
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