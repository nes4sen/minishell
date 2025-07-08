/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:42:26 by nosahimi          #+#    #+#             */
/*   Updated: 2025/07/08 19:47:45 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_strcmp(char *s1, char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

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
		tmp = 2;
	if (!ft_strcmp(str, ">"))
		tmp = 4;
	return (tmp);
}
void	get_type(t_token *tokens)
{
	while (tokens)
	{
		tokens->type = def_type(tokens->str);
		tokens = tokens->next;
	}
}

char *ft_substr(int start, int end, char *str)
{
	int 	len;
	char	*s;
	int		i;

	len = (end - start);
	s = malloc(len + 1);
	if (!s)
		return NULL;
	i = 0;
	while (start < end)
	{
		s[i] = str[start];
		i++;
		start++;
	}
	s[i] = '\0';
	return (s);
}
