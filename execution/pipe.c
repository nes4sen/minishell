/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-laf <aait-laf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:19:45 by aait-laf          #+#    #+#             */
/*   Updated: 2025/08/21 19:55:02 by aait-laf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	close_other_fil(int pipes[][2], int nbr_pipe, int fd1, int fd2)
{
	int	i;

	i = 0;
	while (i < nbr_pipe)
	{
		if (pipes[i][0] != fd1 && pipes[i][0] != fd2)
			close(pipes[i][0]);
		if (pipes[i][1] != fd1 && pipes[i][1] != fd2)
			close(pipes[i][1]);
		i++;
	}
}

char	*get_path(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, "PATH", 4) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

static char	*search_cmd_in_path(char *cmd, char **arg)
{
	int		i;
	char	*full_path;
	char	*save;

	i = 0;
	full_path = NULL;
	save = NULL;
	while (arg[i])
	{
		full_path = ft_strjoin(arg[i], "/");
		full_path = ft_strjoin(full_path, cmd);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK) == 0)
		{
			if (access(full_path, X_OK) == 0)
				return (full_path);
			else
				save = cmd;
		}
		i++;
	}
	return (save);
}

char	*get_path_cmd(char *cmd, t_env **env)
{
	char	*path;
	char	**arg;

	path = get_path(env);
	if (!path || !*path)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		mm_free(FREE_ALL);
		exit(127);
	}
	arg = ft_split(path, ':');
	if (!arg || !cmd[0])
		return (NULL);
	return (search_cmd_in_path(cmd, arg));
}

int	count_number_cmd(t_cmd *cmd)
{
	int	count;

	if (!cmd)
		return (0);
	if (!cmd->next)
		return (1);
	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}
