/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 10:56:18 by nosahimi          #+#    #+#             */
/*   Updated: 2025/08/17 11:59:36 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing/minishell.h"


int main(int ac, char **av, char **envp)
{
	t_shell		shell;

	(void)ac;
	(void)av;
	shell = (t_shell){0}; // compound literal
	init_env(envp, &shell);
	
	setup_signals();
	while (1)
	{
		setup_signals();
		shell.line = readline("minishell $> ");
		if (!shell.line)
		{
			write(1, "exit\n", 5);
			mm_free(FREE_ALL);
			exit(shell.exit_s);
		}
		if (shell.line && *shell.line)
		add_history(shell.line);
		if (!parser(&shell))
		{	
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, SIG_IGN);
			shell.exit_s = execute_command(shell.cmd, &shell.env, shell.exit_s);
			setup_signals();
		}
		mm_free(FREE_ALL_EXCEPT_ENV);
		init_structs_after_free(&shell);
	}
	return (shell.exit_s);
}