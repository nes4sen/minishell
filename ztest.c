/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ztest.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:25:28 by nosahimi          #+#    #+#             */
/*   Updated: 2025/08/07 11:10:01 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0); 
}

int  str_no_quote_len(char *str)
{
	int		len;
	char	quote;

	len = 0;
	quote = 0;
	while (*str)
	{
		if (!quote && is_quote(*str))
			quote = *str;
		else if (*str == quote)
			quote = 0;
		else
			len++;
		str++;
	}
	return len;
}

char	*remove_quote(char *str)
{
	char	*tmp;
	int		i;
	int		quote;
	
	tmp = malloc(str_no_quote_len(str) + 1);
	i = 0;
	quote = 0;
	while(*str)
	{
		if (!quote && is_quote(*str))
			quote = *str;
		else if (quote == *str)
			quote = 0;	
		else
			tmp[i++] = *str;
		str++;
	}
	tmp[i] = '\0';
	return (tmp);
 } 
 int main()
 {
	char *str = "\"hello \" wo\'rld\'";
	remove_quote(str);
	printf("%s\n",str);
 }
