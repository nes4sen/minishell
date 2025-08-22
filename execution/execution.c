/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-laf <aait-laf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:26:11 by aait-laf          #+#    #+#             */
/*   Updated: 2025/08/22 16:04:29 by aait-laf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	execute_command(t_cmd *cmd, t_env **env, int status)
{
	t_cmd	*current;

	current = NULL;
	if (!cmd || !env)
		return (status);
	current = cmd;
	while (current)
	{
		if (current->next)
		{
			status = execute_whith_pipe(current, env, status);
			return (status);
		}
		status = command_args(current, env, status);
		current = current->next;
	}
	return (status);
}

int	execute_with_redirection(t_cmd *current, t_env **env, int status)
{
	int			result;
	t_fd_fils	fils;

	result = 0;
	initial_fd_fils(&fils);
	result = open_check_file(current, &fils);
	if (result == -1 || result == 1)
	{
		restore_fd(&fils);
		return (result);
	}
	if (current && current->arg)
		result = execute_simple_command(current, env, status);
	restore_fd(&fils);
	return (result);
}

int	open_check_file(t_cmd *cmd, t_fd_fils *fil)
{
	t_rdr	*red;
	int		status;

	red = cmd->rdr;
	while (red)
	{
		if (red->type == RDRIN)
			status = rdrin(red, fil);
		else if (red->type == RDROUT)
			status = rdrrout(red, fil);
		else if (red->type == APPND)
			status = appnd(red, fil);
		else if (red->type == HEREDOC)
			status = heredoc(red);
		else
			return (-1);
		red = red->next;
	}
	return (status);
}

int	child_process(t_cmd *cmd, t_env **env)
{
	if (!cmd || !env || !cmd->arg || !cmd->arg[0])
		return (-1);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
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

int	execute_simple_command(t_cmd *cmd, t_env **env, int status)
{
	pid_t	pid;

	if (!env || !cmd || !cmd->arg || !cmd->arg[0])
		return (-1);
	if (is_builin_command(cmd->arg[0]))
		return (execute_builtin(cmd, env, status));
	else
	{
		pid = fork();
		if (pid == -1)
			return (perror("fork"), -1);
		if (pid == 0)
		{
			if (child_process(cmd, env) == -1)
				return (-1);
		}
		else if (pid > 0)
		{
			status = part_parent(pid, status);
		}
	}
	return (status);
}
