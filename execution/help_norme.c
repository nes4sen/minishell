/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_norme.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-laf <aait-laf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:27:35 by aait-laf          #+#    #+#             */
/*   Updated: 2025/08/21 15:19:10 by aait-laf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	command_args(t_cmd *current, t_env **env, int status)
{
	int	result;

	result = status;
	if (current->next)
	{
		result = execute_whith_pipe(current, env, status);
		return (result);
	}
	else if ((current->rdr && (current->rdr->type == RDRIN
				|| current->rdr->type == RDROUT || current->rdr->type == APPND
				|| current->rdr->type == HEREDOC)))
	{
		result = execute_with_redirection(current, env, status);
	}
	else
	{
		if (is_builin_command(current->arg[0]))
			result = execute_builtin(current, env, status);
		else
			result = execute_simple_command(current, env, status);
	}
	return (result);
}

int	help1_red_in_pipe(t_cmd *cmd, t_env **env)
{
	char		*tmp;
	char		**env_array;
	struct stat	buf;

	env_array = NULL;
	if (stat(cmd->arg[0], &buf) == 0)
	{
		if (S_ISDIR(buf.st_mode))
			(write(2, "Is a directory\n", 15)), (exit(126));
	}
	if (access(cmd->arg[0], F_OK) != 0)
	{
		tmp = ft_strjoin(cmd->arg[0], " : No such file or directory\n");
		(write(2, tmp, ft_strlen(tmp))), (exit(127));
	}
	if (access(cmd->arg[0], X_OK) != 0)
	{
		tmp = ft_strjoin(cmd->arg[0], " : Permission denied\n");
		(write(2, tmp, ft_strlen(tmp))), (exit(127));
	}
	env_array = env_to_char_array(*env);
	if (execve(cmd->arg[0], cmd->arg, env_array) == -1)
		(perror("execve")), (exit(127));
	return (0);
}

int	help2_red_in_pipe(t_cmd *cmd, t_env **env)
{
	char	*path;
	char	**env_array;
	char	*tmp;

	(1) && (path = NULL), (env_array = NULL), (tmp = NULL);
	if (!cmd || !env || cmd->arg[0] == NULL)
		return (-1);
	path = get_path_cmd(cmd->arg[0], env);
	if (!path)
	{
		tmp = ft_strjoin(cmd->arg[0], " : Command not found\n");
		(write(2, tmp, ft_strlen(tmp))), (exit(127));
	}
	else if (!ft_strcmp(path, cmd->arg[0]))
	{
		tmp = ft_strjoin(cmd->arg[0], " : Permission denied\n");
		(write(2, tmp, ft_strlen(tmp))), (exit(127));
	}
	env_array = env_to_char_array(*env);
	if (!env_array)
		return (free(path), -1);
	if (execve(path, cmd->arg, env_array) == -1)
		(perror("execve")), (exit(127));
	return (0);
}	

char	**env_to_char_array(t_env *env)
{
	t_env	*temp;
	char	**env_array;
	int		i;
	int		len;

	temp = env;
	i = 0;
	if (!env)
		return (NULL);
	env_array = mm_alloc(sizeof(char *) * (count_len(temp) + 1));
	if (!env_array)
		return (NULL);
	temp = env;
	while (temp)
	{
		len = ft_strlen(temp->name) + 1 + ft_strlen(temp->value) + 1;
		env_array[i] = mm_alloc(len);
		if (!env_array[i])
			return (NULL);
		ft_strcpy(env_array[i], temp->name);
		(ft_strcat(env_array[i], "=")), (ft_strcat(env_array[i], temp->value));
		i++;
		temp = temp->next;
	}
	return (env_array[i] = NULL, env_array);
}

int	red_in_pipe(t_cmd *cmd, t_env **env)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!cmd || !env || !cmd->arg || !cmd->arg[0])
		return (-1);
	if (!ft_strchr(cmd->arg[0], '/'))
	{
		if (help1_red_in_pipe(cmd, env) == -1)
			return (-1);
	}
	else
	{
		if (help2_red_in_pipe(cmd, env) == -1)
			return (-1);
	}
	return (0);
}
