/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:42:26 by nosahimi          #+#    #+#             */
/*   Updated: 2025/07/01 17:19:10 by nosahimi         ###   ########.fr       */
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

// int	is_symbole(char c)
// {
// 	if (c == '>' || c == '<' || c == '|')
// 		return (c);
// 	return (0);
// }
int	get_type(char *str)
{
	if (!ft_strcmp(str, "|"))
		return (1);
	if (!ft_strcmp(str, "<<"))
		return (2);
	if (!ft_strcmp(str, ">"))
		return (3);
	if (!ft_strcmp(str, "<"))
		return (4);
	if (!ft_strcmp(str, ">>"))
		return (5);
	return (0);
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
