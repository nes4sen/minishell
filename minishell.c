/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 10:56:18 by nosahimi          #+#    #+#             */
/*   Updated: 2025/08/21 21:34:10 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

static int	read_and_handle_input(t_shell *shell)
{
	shell->line = readline("minishell $> ");
	if (g_sigint == SIGINT)
	{
		shell->exit_s = 130;
		g_sigint = 0;
	}
	if (!shell->line)
	{
		write(1, "exit\n", 5);
		mm_free(FREE_ALL);
		free(shell->line);
		exit(shell->exit_s);
	}
	address_tracker()->line = shell->line;
	if (shell->line && *shell->line)
		add_history(shell->line);
	return (0);
}

static int	parse_and_execute(t_shell *shell)
{
	if (!parser(shell))
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		shell->exit_s = execute_command(shell->cmd, &shell->env, shell->exit_s);
		if (shell->exit_s == -1)
		{
			init_structs_after_free(shell);
			return (1);
		}
		setup_signals();
	}
	return (0);
}

static void	cleanup_and_reset(t_shell *shell)
{
	if (g_sigint == SIGINT)
	{
		shell->exit_s = 130;
		g_sigint = 0;
	}
	mm_free(FREE_ALL_EXCEPT_ENV);
	init_structs_after_free(shell);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	shell = (t_shell){0};
	init_env(envp, &shell);
	setup_signals();
	while (1)
	{
		read_and_handle_input(&shell);
		if (parse_and_execute(&shell) == 1)
			continue ;
		cleanup_and_reset(&shell);
	}
	return (shell.exit_s);
}
