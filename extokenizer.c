/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extokenizer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:07:19 by nosahimi          #+#    #+#             */
/*   Updated: 2025/07/28 11:18:57 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void get_no_quoted_extoken(t_extoken **exhead, char **s)
{
	int		i;
	char	*token;
	char	*str;
	
	i = 0;
	str = *s;
	while (str[i] && !is_quote(str[i]))
		i++;
	token = ft_substr(0 , i, str);
	add_back_extoken(exhead, token, 0);
	*s += i;
}

void get_quoted_extoken(t_extoken **exhead, char **s)
{
	//this function remove target the quoted sring , remove it quotes and flag the token

	char	*token;
	char	*str;
	int		quote;
	int		i;
	int		stat;

	stat = 0;
	i = 0;
	str = *s;
	quote = str[i++];
	while (str[i] && str[i] != quote)
		i++;
	token = ft_substr(1 , i, str);
	if (quote == '\'')
		stat = SINGLE_QUOTE;
	else if (str[i] == '"')
		stat = DOUBLE_QUOTE;
	add_back_extoken(exhead, token, stat);
	*s = *s + i;
}

void build_exlist(t_extoken **exhead, t_token *token)
{
	char *str;
	
	str = token->str;
	while (*str)
	{
		if (is_quote(*str))
			get_quoted_extoken(exhead, &str);
		else
			get_no_quoted_extoken(exhead, &str);
	}
}