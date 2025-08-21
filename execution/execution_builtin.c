/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_builtin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-laf <aait-laf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:25:09 by aait-laf          #+#    #+#             */
/*   Updated: 2025/08/21 15:13:17 by aait-laf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	execute_builtin(t_cmd *cmd, t_env **env, int last_code)
{
	int	status;

	status = last_code;
	if (!cmd->arg || !env || !cmd->arg[0])
		return (-1);
	if (ft_strcmp(cmd->arg[0], "echo") == 0)
		status = echo_fonc(cmd->arg, last_code);
	else if (ft_strcmp(cmd->arg[0], "cd") == 0)
		status = fonc_cd(cmd->arg, *env);
	else if (ft_strcmp(cmd->arg[0], "pwd") == 0)
		status = fonc_pwd(cmd->arg, *env);
	else if (ft_strcmp(cmd->arg[0], "export") == 0)
		status = fonc_export(cmd->arg, env);
	else if (ft_strcmp(cmd->arg[0], "unset") == 0)
		status = unset_fonc(cmd->arg, env);
	else if (ft_strcmp(cmd->arg[0], "env") == 0)
		status = env_fonc(cmd->arg, *env);
	else if (ft_strcmp(cmd->arg[0], "exit") == 0)
		status = exit_fonc(cmd->arg, last_code);
	return (status);
}

int	is_builin_command(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

void	initial_fd_fils(t_fd_fils *fil)
{
	fil->infil = -1;
	fil->outfil = -1;
	fil->save_stdout = dup(1);
	fil->save_strdint = dup(0);
}

void	restore_fd(t_fd_fils *fils)
{
	dup2(fils->save_stdout, 0);
	dup2(fils->save_strdint, 1);
	close(fils->save_stdout);
	close(fils->save_strdint);
}

int	part_parent(int pid, int status)
{
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		status = 128 + WTERMSIG(status);
	return (status);
}
