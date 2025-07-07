/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:42:26 by nosahimi          #+#    #+#             */
/*   Updated: 2025/07/07 20:23:13 by nosahimi         ###   ########.fr       */
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


void	get_type(t_token *tokens)
{
	unsigned int	prev_type;

	while (tokens)
	{
		prev_type = tokens->type;
		if (tokens->type && prev_type >= 2 && prev_type <= 5)	
		{
			if (tokens->next)
			{
			
				tokens->next->type = prev_type;
			
			}
		}
		else if (!ft_strcmp(tokens->str, "|"))
			tokens->type = PIPE;
		else if (!ft_strcmp(tokens->str, "<<"))
			tokens->type = HEREDOC;
		else if (!ft_strcmp(tokens->str, ">>"))
			tokens->type = APPND;
		else if (!ft_strcmp(tokens->str, "<"))
			tokens->type = RDRIN;
		else if (!ft_strcmp(tokens->str, ">"))
			tokens->type = RDRIN;
		else
			tokens->type = CMD;
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
