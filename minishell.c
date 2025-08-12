/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 10:56:18 by nosahimi          #+#    #+#             */
/*   Updated: 2025/08/12 12:08:50 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_address_track *address_tracker(void)
{
	static t_address_track p = {0};
	return (&p);
}

void	init_env(char **envp, t_shell *shell)
{
	t_address_track *track;

	track = address_tracker();
	track->env = get_env(envp);
	shell->env = track->env; 
}


void init_structs_after_free(t_shell *shell)
{
	shell->cmd = NULL;
	shell->mmtrack = NULL;
	shell->tokens = NULL;
}

int main(int ac, char **av, char **envp)
{
	t_shell			shell;

	(void)ac;
	(void)av;
	shell = (t_shell){0}; // compound literal
	init_env(envp, &shell);
	setup_signals();
	while (1)
	{
		shell.line = readline("minishell $> ");
		if (!shell.line) // Ctrl+D (EOF)
		{
			write(1, "exit\n", 5);
			// mm_free(FREE_ALL);
			exit(1);
		}
		if (shell.line && *shell.line)
			add_history(shell.line);
		if (!parser(&shell)) //parsing function 
			shell.exit_s = execute_command(shell.cmd, &shell.env, shell.exit_s); // Corriger signature et récupérer status
		init_structs_after_free(&shell);
		mm_free(FREE_ALL_EXCEPT_ENV);
	}
	return (shell.exit_s);
}
/*


*/
