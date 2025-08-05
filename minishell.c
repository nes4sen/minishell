/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 10:56:18 by nosahimi          #+#    #+#             */
/*   Updated: 2025/08/05 13:40:55 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_adress_track *adress_tracker(void)
{
	static t_adress_track p = {0};
	return (&p);
}

void	init_env(char **envp, t_shell *shell)
{
	t_adress_track *track;

	track = adress_tracker();
	track->env = get_env(envp);
	shell->env = track->env; 
}

int main(int ac, char **av, char **envp)
{
	t_shell			shell;
	t_adress_track	*mmtrack;

	(void)ac;
	(void)av;
	shell = (t_shell){0}; // compound literal
	init_env(envp, &shell);
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
		// mm_free(shell.line);
	}
	
	return (shell.exit_s);
}
