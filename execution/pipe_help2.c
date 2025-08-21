/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_help2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-laf <aait-laf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:40:45 by aait-laf          #+#    #+#             */
/*   Updated: 2025/08/21 14:44:29 by aait-laf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	create_pipe_if_needed(t_cmd *current, int pipefd[2], int prev_pipe)
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
	return (0);
}

// 2. Fonction pour configurer les redirections dans le processus enfant
void	setup_child_redirections(t_cmd *current, int prev_pipe, int pipefd[2])
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
}

// 3. Fonction pour exécuter la commande dans le processus enfant
void	execute_child_command(t_cmd *current, t_env **env, int status)
{
	t_fd_fils	fils;
	int			stus;
	int			builtin_status;
	int			red_status;

	if (current->rdr)
	{
		(initial_fd_fils(&fils)), (stus = open_check_file(current, &fils));
		if (stus == -1 || stus == 1)
			exit(1);
	}
	if (is_builin_command(current->arg[0]))
	{
		builtin_status = execute_builtin(current, env, status);
		exit(builtin_status);
	}
	else
	{
		if (red_in_pipe(current, env) != 0)
		{
			red_status = red_in_pipe(current, env);
			exit(red_status);
		}
		exit(1);
	}
}

char	*ft_strcat(char *dest, const char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j])
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

char	*ft_strjoin(char *dest, char *src)
{
	char	*p;
	size_t	i;
	size_t	j;

	if (!dest || !src)
		return (NULL);
	i = 0;
	j = 0;
	p = mm_alloc(ft_strlen((char *)dest) + ft_strlen((char *)src) + 1);
	if (!p)
		return (NULL);
	while (dest[i] != '\0')
	{
		p[i] = dest[i];
		i++;
	}
	while (src[j] != '\0')
	{
		p[i + j] = src[j];
		j++;
	}
	p[i + j] = '\0';
	return (p);
}
