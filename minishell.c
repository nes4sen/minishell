/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 10:56:18 by nosahimi          #+#    #+#             */
/*   Updated: 2025/07/01 16:35:51 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*
this is the start of everything and here is the steps of everything :abort

1_ t_cmd is the linked list that the executer should expect

*/
// int main(int ac, char **av, char **envp)
// {
// 	t_cmd	*cmd;
// 	t_env	*env;
// 	char	*line;
	
// 	env = get_env(envp);
// 	while (1)
// 	{
// 		line = readline("minishell $>");
// 		if (line && *line)
// 			add_history(line);
// 		cmd = parsing(line); //parsing function
// 		if (!cmd)
// 		{
// 			//free all
// 			exit(1);
// 		} 
// 		free(line);
// 		rl_clear_history();
		
// 	}
// 	// line = read_line();
// 	// head = parsing(line);
// }