/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 10:53:41 by nosahimi          #+#    #+#             */
/*   Updated: 2025/08/16 17:40:39 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	parser(t_shell *shell)
{
	int		syntax_exit;

	tokenizer(shell);
	syntax_exit = syntax_error(shell);
	shell->exit_s = syntax_exit;
	if (!syntax_exit)
	{
		expand_env_vars(shell);
		build_cmd(shell);
		scan_for_heredoc(shell);
	}
	else 
		return (shell->exit_s);
	return (0);
}
