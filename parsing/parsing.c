/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 10:53:41 by nosahimi          #+#    #+#             */
/*   Updated: 2025/08/16 16:33:09 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	parser(t_shell *shell)
{
	tokenizer(shell);
	// print_tokens(shell->tokens);
	if (!syntax_error(shell))
	{	
		expand_env_vars(shell);
		build_cmd(shell);
		// print_cmd_struct(shell->cmd);
		scan_for_heredoc(shell);
	}
	else 
		return (shell->exit_s);
	return (0);
}
