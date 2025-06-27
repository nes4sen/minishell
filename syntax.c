/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 17:52:26 by nosahimi          #+#    #+#             */
/*   Updated: 2025/06/26 17:30:53 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// fix the pipe in the end of the string 
//
int		is_valid_quotes(char *str)
{
	int	quote;

	quote = -1;
	while(*str)
	{
		if (quote == -1)
		{
			if (*str == '\'' || *str == '\"')
				quote = *str;
		}
		else if (quote == *str)
			quote = -1;
		str++;
	}
	return (quote);
}

int	is_symbole(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (c);
	return (0);
}
int		is_valid_arrows(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '>' || str[i] == '<')
		{
			if (str[i] == str[i + 1])
				i++;
			i++;
			if (str[i] && is_symbole(str[i]))
				return (i);
		}
		i++;
	}
	return (-1);
}

int is_valid_pipe(char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '|')
		return (i);
	while (str[i])
	{
		if (str[i] == '|' && str[i + 1] == '|')
			return (i);
		i++;
	}
	if (str[i - 1] == '|')
		return(i);
	return (-1);
}

int		syntax_error(char *str)
{
	int len;
	
	len = INT_MAX;
	if (is_valid_quotes(str) != -1 && len > is_valid_quotes(str))
		len = is_valid_quotes(str);
	if (is_valid_arrows(str) != -1 && len > is_valid_arrows(str))
		len = is_valid_arrows(str);
	if (is_valid_pipe(str) != -1 && len > is_valid_pipe(str) )
		len = is_valid_pipe(str);
	if (len >= INT_MAX)
		len = -1;
	return (len);
}
// int main()
// {
// 	char str[] = " >> hello >> | toto  |";
// 	int res = syntax_error(str);
// 	printf("%d\n", res);
// 	if (res > -1)
// 	{
// 		if (res == 39 || res == 34)
// 			printf("minishell: syntax error near unexpected token '%c'\n", res);
// 		else 
// 			printf("minishell: syntax error near unexpected token '%c'\n", str[res]);	
// 	}
// }