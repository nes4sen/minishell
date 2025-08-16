/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:42:26 by nosahimi          #+#    #+#             */
/*   Updated: 2025/08/14 12:08:45 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int white_space(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (c);
	return (0);
}

void	get_next_type(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type >= 3 && tokens->type <= 5)
		{
			if (tokens->next)
				tokens->next->type = file;
		}
		if (tokens->type == 2)
		{
			if (tokens->next)
				tokens->next->type = DLMTR;
		}
		tokens = tokens->next;
	}	
}
unsigned int	def_type(char *str)
{
	unsigned int	tmp;

	tmp = 0;
	if (!ft_strcmp(str, "|"))
		tmp = 1;
	if (!ft_strcmp(str, "<<"))
		tmp = 2;
	if (!ft_strcmp(str, ">>"))
		tmp = 5;
	if (!ft_strcmp(str, "<"))
		tmp = 3;
	if (!ft_strcmp(str, ">"))
		tmp = 4;
	return (tmp);
}
void	get_type(t_token *tokens)
{
	t_token *tmp;

	tmp = tokens;
	while (tokens)
	{
		tokens->type = def_type(tokens->str);
		tokens = tokens->next;
	}
	get_next_type(tmp);
}




