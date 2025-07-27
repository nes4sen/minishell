/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 10:56:18 by nosahimi          #+#    #+#             */
/*   Updated: 2025/07/27 17:39:33 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int main(int ac, char **av, char **envp)
{
	t_cmd	*cmd;
	t_env	*env;
	char	*line;

	(void)ac;
	(void)av;
	env = get_env(envp);
	while (1)
	{
		line = readline("minishell $> ");
		if (line && *line)
			add_history(line);
		cmd = parsing(line, env); //parsing function
		if (!cmd)
		{
			//free all
			exit(1);
		} 
		free(line);
		// rl_clear_history();
	}
}