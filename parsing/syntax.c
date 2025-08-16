/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 17:52:26 by nosahimi          #+#    #+#             */
/*   Updated: 2025/08/16 16:31:57 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int	syntax_err_msg(char	*err, t_shell *shell)
{
	if (!ft_strcmp(err, "operator"))
		write(1, "minishell: syntax error, invalid operator\n", 42);
	else if (*err)
	{
		write(1, "minishell: syntax error near unexpected token ", 46);
		write(1, err, ft_strlen(err));
		write(1, "\n", 1);
	}
	if (shell)
		shell->exit_s = 2;
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
		return (syntax_err_msg(&quote, NULL));
	return (0);
}

int	symbol_err(char *str)
{
	if (is_symbole(*str))
	{
		if (def_type(str) == 0)
			return (syntax_err_msg("operator", NULL));
	}
	return (0);
}

int	syntax_error(t_shell *shell)
{
    t_token *tokens;

    if (!shell || !shell->tokens) 
        return (1);
    tokens = shell->tokens;
    if (tokens->type == PIPE)
        return (syntax_err_msg("|", shell));
    while (tokens)
    {
        if (tokens->str && quote_err(tokens->str)) 
            return (1);
        if (tokens->str && symbol_err(tokens->str))
            return (1);
        if (tokens->str && is_oprt(tokens->str)) 
        {
            if (!tokens->next) 
                return (syntax_err_msg("newline", shell));
            else if (tokens->next->str && is_oprt(tokens->next->str))
            	return (syntax_err_msg(tokens->next->str, shell));
        }
        tokens = tokens->next;
    }
    return (0);
}
