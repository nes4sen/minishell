/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-laf <aait-laf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 10:53:41 by nosahimi          #+#    #+#             */
/*   Updated: 2025/08/17 10:28:19 by aait-laf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	parser(t_shell *shell)
{
	int		syntax_exit;

	tokenizer(shell);
	syntax_exit = syntax_error(shell);
	if (!syntax_exit)
	{
		expand_env_vars(shell);
		build_cmd(shell);
		scan_for_heredoc(shell);
	}
	else
		return (shell->exit_s = 2, shell->exit_s);
	return (0);
}
