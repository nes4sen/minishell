/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 10:53:41 by nosahimi          #+#    #+#             */
/*   Updated: 2025/08/12 12:37:23 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void print_token(t_token *token)
{
	while (token)
	{
		printf("[%s  %d]\n",token->str , token->type);
		token = token->next;
	}
}
int	parser(t_shell *shell)
{
	tokenizer(shell);
	// print_token(shell->tokens);
	if (!syntax_error(shell->tokens))
	{	
		expand_env_vars(shell);
		build_cmd(shell);
	// scan_for_heredoc(shell);
	}
	else 
		return (1);
	return (0);
}
