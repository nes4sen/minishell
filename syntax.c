/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 17:52:26 by nosahimi          #+#    #+#             */
/*   Updated: 2025/08/12 13:05:16 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int	syntax_err_msg(char	*err)
{
	if (!ft_strcmp(err, "operator"))
		write(1, "minishell: syntax error, invalid operator\n", 42);
	else if (*err && (*err == '\'' || *err == '"'))
	{
		if (*err == '\'')
			write(1, "minishell: syntax error, unclosed (\') Quote\n", 44);
		if (*err == '\"')
			write(1, "minishell: syntax error, unclosed (\") Quote\n", 44);
		
	}
	else if (!err || *err)
	{
		write(1, "minishell: syntax error near unexpected token operator", 54);
	}
	else 
		return (0);
	return (1);
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
	
	while (tokens)
	{
		if (quote_err(tokens->str))
			return (1);
		if (symbol_err(tokens->str))
			return (1);
		
		if (is_oprt(tokens->str))
		{
				if ((tokens->next == NULL || is_oprt(tokens->next->str)))
				{
					syntax_err_msg(tokens->next->str);
					// printf("[toto]\n");
					return (1);
				}
		}
		tokens = tokens->next; 
	}
	return (0);
}
