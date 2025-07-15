/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 17:52:26 by nosahimi          #+#    #+#             */
/*   Updated: 2025/07/14 18:50:48 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	syntax_err_msg(char	*err)
{
	if (!ft_strcmp(err, "operator"))
		printf("minishell: syntax error, invalid operator\n");
	else if (*err && (*err == '\'' || *err == '"'))
		printf("minishell: syntax error, unclosed (%c) Quote\n", *err);
	else
		printf("minishell: syntax error near unexpected token `%s'\n", err);
	exit(1);
}
void	quote_err(char *str)
{
	char	quote;
 
	quote = 0;
	while (*str)
	{
		if (!quote)
		{
			if (*str == '\'' || *str == '"')
				quote = *str;
		}
		else if (quote == *str)
			quote = 0;
		str++;
	}
	if (quote)
		syntax_err_msg(&quote);
}

/*this function check if the first char is a symbole but the token type is a cmd*/
void	symbol_err(char *str)
{
	if (is_symbole(*str))
	{
		if (def_type(str) == 0)
			syntax_err_msg("operator");
	}
}



void	syntax_error(t_token *tokens)
{
	while (tokens)
	{
		quote_err(tokens->str);
		symbol_err(tokens->str);
		if (tokens->next)
		{
			if (is_oprt(tokens->str) && is_oprt(tokens->next->str))
				syntax_err_msg(tokens->next->str);
		}
		tokens = tokens->next;
	}
}
