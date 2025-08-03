/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:01:13 by nosahimi          #+#    #+#             */
/*   Updated: 2025/08/03 12:06:08 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void hanldle_heredoc(t_shell *shell)
{
	t_token *token;
	t_token *last_heredoc;

	token = shell->tokens;
	while (token)
	{
		if (token->type == HEREDOC)
			last_heredoc = token->type;
		token = token->next;
	}
	
}

