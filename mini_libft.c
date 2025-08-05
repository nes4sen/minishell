/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_libft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 11:20:46 by nosahimi          #+#    #+#             */
/*   Updated: 2025/08/05 19:28:29 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	is_alpha(char c)
{
	return ((c >= 'a' && c <= 'z') && (c >= 'A' && c <= 'Z'));
}

int is_digit(char c)
{
	return ((c >= '0' && c <= '9'));
}
char *ft_substr(int start, int end, char *str)
{
	int 	len;
	char	*s;
	int		i;

	len = (end - start);
	s = mm_alloc(len + 1);
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
int ft_strcmp(char *s1, char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}