/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 10:56:18 by nosahimi          #+#    #+#             */
/*   Updated: 2025/08/04 19:09:49 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int main(int ac, char **av, char **envp)
{
	t_shell		shell;

	shell = (t_shell){0}; // compound literal
	(void)ac;
	(void)av;
	shell.env = get_env(envp);
	while (1)
	{
		shell.line = readline("minishell $> ");
		if (!shell.line) // Ctrl+D (EOF)
		{
			printf("exit\n");
			break;
		}
		if (shell.line && *shell.line)
			add_history(shell.line);
		parser(&shell); //parsing function 
		//  shell.exit_s = execute_command(shell.cmd, &shell.env, shell.exit_s); // Corriger signature et récupérer status
		free(shell.line);
	}
	return (shell.exit_s);
}
