/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 10:56:18 by nosahimi          #+#    #+#             */
/*   Updated: 2025/08/19 09:40:52 by nosahimi         ###   ########.fr       */
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
	while (1)
	{
		// get_shell(&shell);
		setup_signals();
		shell.line = readline("minishell $> ");
		if (g_sigint)
		{
			shell.exit_s = 130;
			g_sigint = 0;
		}
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
			if(shell.exit_s == -1)
			{
				init_structs_after_free(&shell);	
				continue;
			}
			setup_signals();
		}
		if (g_sigint)
		{
			shell.exit_s = 130;
			g_sigint = 0;
		}
		mm_free(FREE_ALL_EXCEPT_ENV);
		init_structs_after_free(&shell);
	}
	return (shell.exit_s);
}
