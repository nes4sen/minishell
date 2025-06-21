/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_tokinezer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:53:10 by nosahimi          #+#    #+#             */
/*   Updated: 2025/06/21 19:08:39 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int white_space(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (c);
	return (0);
}
void	get_token(char **str, int *quote)
{
	char 	*s;
	int		i;
	int		j;
	
	i = 0;
	s = *str;
	if (s[i] == quote) //to skip the quote that passed from the func
		i++;
	while (s[i] && s[i] == quote)
	{
		j = i;
		// add the tokens in nodes 
		i++;
	}
}
t_token *tokenizer(char *str)
{
	t_token	*tokens;
	int		quote;
	int		i;

	i = 0;
	while (str[i])
	{
		if(str[i] == '\'' || str[i] == '\"')
			quote = str[i];
		while(white_space(str[i]))
			i++;
		get_token(&str, &quote);
	}
}