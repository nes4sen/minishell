/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:33:56 by aait-laf          #+#    #+#             */
/*   Updated: 2025/08/22 17:09:11 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static int	wait_and_get_final_status(pid_t pids[], int nb_cmd)
{
	int	i;
	int	child_status;
	int	final_status;

	(1) && (i = 0, final_status = 0);
	while (i < nb_cmd)
	{
		waitpid(pids[i], &child_status, 0);
		if (i == nb_cmd - 1)
		{
			if (WIFEXITED(child_status))
				final_status = WEXITSTATUS(child_status);
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
	return (setup_signals(), final_status);
}

static int	handle_fork_error(int prev_pipe, t_cmd *current, int pipefd[2])
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

static void	handle_parent_process(pid_t pid, t_pipe_data *data, t_cmd *current)
{
	data->pids[(*(data->cmd_index))++] = pid;
	if (*(data->prev_pipe) != -1)
		close(*(data->prev_pipe));
	if (current->next)
	{
		close(data->pipefd[1]);
		*(data->prev_pipe) = data->pipefd[0];
	}
	else
		*(data->prev_pipe) = -1;
}

static int	process_command(t_cmd *current, t_pipe_data *data, t_env **env,
		int status)
{
	pid_t	pid;

	if (create_pipe_if_needed(current, data->pipefd, *(data->prev_pipe)) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (handle_fork_error(*(data->prev_pipe), current, data->pipefd));
	if (pid == 0)
	{
		setup_child_redirections(current, *(data->prev_pipe), data->pipefd);
		execute_child_command(current, env, status);
	}
	else
		handle_parent_process(pid, data, current);
	return (0);
}

int	execute_whith_pipe(t_cmd *cmd, t_env **env, int status)
{
	int			prev_pipe;
	t_cmd		*current;
	pid_t		*pids;
	int			i;
	t_pipe_data	data;

	pids = mm_alloc (count_number_cmd (cmd) * sizeof(pid_t));
	if (!pids)
		return (-1);
	prev_pipe = -1;
	current = cmd;
	i = 0;
	data.prev_pipe = &prev_pipe;
	data.pids = pids;
	data.cmd_index = &i;
	while (current)
	{
		if (process_command(current, &data, env, status) == -1)
			return (-1);
		current = current->next;
	}
	return (wait_and_get_final_status(pids, count_number_cmd(cmd)));
}
