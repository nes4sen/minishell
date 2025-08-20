/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdelhak <abdelhak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 17:52:26 by nosahimi          #+#    #+#             */
/*   Updated: 2025/08/20 15:39:37 by abdelhak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	syntax_err_msg(char	*err)
{
	if (!ft_strcmp(err, "operator"))
		write(2, "minishell: syntax error, invalid operator\n", 42);
	else if (!ft_strcmp(err, "newline"))
		write(2, "minishell: syntax error near unexpected token `newline'\n", 56);
	else if (*err && (*err == '"' || *err == '\''))
	{
		write(2, "minishell: syntax error, unclosed ", 34);
		write(2, err, 1);
		write(2, " quote \n", 8);
	}
	else if (*err)
		write(2, "minishell: syntax error too many operators\n", 43);
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

int	symbol_err(char *str)
{
	if (is_symbole(*str))
	{
		if (def_type(str) == 0)
			return (syntax_err_msg("operator"));
	}
	return (0);
}
int close_up_operatores(t_token *token)
{
	if (token->str && is_oprt(token->str))
	{
		if (!token->next)
			return (syntax_err_msg("newline"));
		if (token->type != PIPE && is_oprt(token->next->str)) 
			return (syntax_err_msg("P"));
	}
	return (0);
}
int	syntax_error(t_shell *shell)
{
    t_token *tokens;

    if (!shell || !shell->tokens) 
        return (0);
    tokens = shell->tokens;
    if (tokens->type == PIPE)
        return (syntax_err_msg("|"));
    while (tokens)
    {
        if (tokens->str && quote_err(tokens->str)) 
            return (2);
        if (tokens->str && symbol_err(tokens->str))
            return (2);
		if (tokens->str && is_oprt(tokens->str))
		{
			if (!tokens->next)
				return (syntax_err_msg("newline"));
			if (tokens->type != PIPE && is_oprt(tokens->next->str)) 
				return (syntax_err_msg("|"));
		}
        tokens = tokens->next;
    }
    return (0);
}
