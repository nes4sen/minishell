/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 17:52:26 by nosahimi          #+#    #+#             */
/*   Updated: 2025/07/07 19:28:55 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"




int	is_symbole(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (c);
	return (0);
}
void	syntax_err_msg(char	*err)
{
	printf("minishell:  syntax error near unexpected token `%s'\n", err);
}

int	syntax_error(t_token *tokens)
{
	unsigned int prev_type;

	if (tokens->type == 1)
		return (syntax_err_msg(tokens->str), 1);
	while (tokens->next)
	{
		prev_type = tokens->type;
		tokens = tokens->next;
		if (prev_type && tokens->type) 
			return (syntax_err_msg(tokens->str), 1);
	}
	if (tokens->type == 1)
		return (syntax_err_msg(tokens->str), 1);
	return (0);
}