/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:00:15 by nosahimi          #+#    #+#             */
/*   Updated: 2025/05/18 18:18:58 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *read_line()
{
	char *line;
	// char *tmp;
	 
	line = readline("minishell $>");
	if (line)
		add_history(line);
	
	
}