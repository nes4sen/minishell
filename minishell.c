/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-laf <aait-laf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 10:56:18 by nosahimi          #+#    #+#             */
/*   Updated: 2025/08/17 11:19:18 by aait-laf         ###   ########.fr       */
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
			// printf("-----sig----%d---\n", g_sigint);
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, SIG_IGN);
			if (g_sigint)
			{
				printf("-----2----%d---\n", shell.exit_s);
				shell.exit_s = 130;
				printf("-----3----%d---\n", shell.exit_s);
				g_sigint= 0;
				// init_structs_after_free(&shell);
				// continue ;
			}
			shell.exit_s = execute_command(shell.cmd, &shell.env, shell.exit_s);
		}
		mm_free(FREE_ALL_EXCEPT_ENV);
		init_structs_after_free(&shell);
	}
	return (shell.exit_s);
}
