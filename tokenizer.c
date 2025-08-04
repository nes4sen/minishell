/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:53:10 by nosahimi          #+#    #+#             */
/*   Updated: 2025/08/04 19:09:25 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_token(char **str)
{
	int		quote;
	char 	*s;
	int		i;

	quote  = 0;
	s = *str;
	i = 0;
	while (s[i])
	{
		if(!quote && is_seperator(s[i]))
			break;
		if (!quote && is_quote(s[i]))
			quote = s[i];
		else if (quote == s[i])
			quote = 0;
		i++;
	}
	*str = (s + i);
	return (ft_substr(0, i, s));
}

char *get_token_symbole(char **str)
{
	char	*s;
	int		i;

	i = 0;
	s = *str;
	while (is_symbole(s[i]))
		i++;
	*str = (s + i);
	return (ft_substr(0, i, s));
} 

void	tokenizer(t_shell *shell)
{
	char	*token;
	char 	*str;
	
	str = shell->line;
	while (*str)
	{	
		while (white_space(*str))
			str++;
		if (is_symbole(*str))
			token = get_token_symbole(&str);
		else if (!*str)
			break ;
		else
			token = get_token(&str);
		token_add_back(&shell->tokens, token, 0);
	}
	get_type(shell->tokens);
}
