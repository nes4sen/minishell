/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 10:53:41 by nosahimi          #+#    #+#             */
/*   Updated: 2025/07/01 16:36:08 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_cmd *parsing(char *line)
{
	int		err;
	t_token	*token;
	t_cmd	cmd;
		
	err = syntax_error(line);
	if (err)
	{
		if (err == 39 || err == 34)
			printf("minishell: syntax error near unexpected token '%c'\n", err);
		else
			printf("minishell: syntax error near unexpected token '%c'\n", line[err]);
		// int herdoc = get_heredoc(line, err); || --> the function take the index of the synax error its stop when it countred it , otherwise it do the herdoc 
		//free and exit
	}
	token = tokenizer(line);
	// cmd = build_cmd_list(token):
}
