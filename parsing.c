/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 10:53:41 by nosahimi          #+#    #+#             */
/*   Updated: 2025/05/23 10:42:54 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"




t_cmd *parsing(char *line)
{
	int		err;
	t_token	*token;
		
	err = syntax_error(line);
	if (err)
	{
		if (err == 39 || err == 34)
			printf("minishell: syntax error near unexpected token '%c'\n", err);
		else
			printf("minishell: syntax error near unexpected token '%c'\n", line[err]);
		//free and exit
	}
	token = tokenizer(line);
	
}



