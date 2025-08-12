/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 17:52:26 by nosahimi          #+#    #+#             */
/*   Updated: 2025/08/12 14:29:31 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int	syntax_err_msg(char	*err)
{
	if (!ft_strcmp(err, "operator"))
		write(1, "minishell: syntax error, invalid operator\n", 42);
	else if (*err)
	{
		write(1, "minishell: syntax error near unexpected token ", 46);
		write(1, err, ft_strlen(err));
		write(1, "\n", 1);
	}
	return (2);
}
int	quote_err(char *str)
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
		return (syntax_err_msg(&quote));
	return (0);
}

/*this function check if the first char is a symbole but the token type is a cmd*/
int	symbol_err(char *str)
{
	if (is_symbole(*str))
	{
		if (def_type(str) == 0)
			return (syntax_err_msg("operator"));
	}
	return (0);
}


int	syntax_error(t_token *tokens)
{
	if (tokens && tokens->type == PIPE)
		return (syntax_err_msg("|"));
	while (tokens)
	{
		if (quote_err(tokens->str))
			return (1);
		if (symbol_err(tokens->str))
			return (1);
		
		if (is_oprt(tokens->str))
		{
				if ((tokens->next == NULL))
					return (syntax_err_msg("newline"));
				else if (is_oprt(tokens->next->str))
					return (syntax_err_msg(tokens->next->str));
		}
		tokens = tokens->next; 
	}
	return (0);
}
