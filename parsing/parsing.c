/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 10:53:41 by nosahimi          #+#    #+#             */
/*   Updated: 2025/08/19 09:40:24 by nosahimi         ###   ########.fr       */
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
		if (build_cmd(shell))
			return (130);
	}
	else
	{

		return (shell->exit_s = 2, shell->exit_s);
	}
	return (0);
}
