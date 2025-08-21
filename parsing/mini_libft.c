/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_libft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 11:20:46 by nosahimi          #+#    #+#             */
/*   Updated: 2025/08/21 17:17:27 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_strcpy(char *dst, char *src)
{
	int	i;

	if (!dst || !src)
		return ;
	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

char	*ft_substr(int start, int end, char *str)
{
	int		len;
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

static size_t	int_len(int nb)
{
	size_t	len;
	long	n;

	n = (long)nb;
	len = 0;
	if (nb <= 0)
		len++;
	if (n < 0)
		n *= -1;
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int nb)
{
	size_t	len;
	char	*p;
	size_t	i;
	long	n;

	n = (long)nb;
	len = int_len(n);
	p = ll_alloc(sizeof(char) * len + 1);
	p[len] = '\0';
	i = 0;
	if (n < 0)
	{
		p[0] = '-';
		n *= -1;
		i = 1;
	}
	while (len-- > i)
	{
		p[len] = (n % 10) + 48;
		n /= 10;
	}
	return (p);
}
