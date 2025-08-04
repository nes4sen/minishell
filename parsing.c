/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 10:53:41 by nosahimi          #+#    #+#             */
/*   Updated: 2025/08/04 19:10:35 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void parser(t_shell *shell)
{
	tokenizer(shell);
	syntax_error(shell->tokens);
	expand_env_vars(shell);
	// handle_heredoc(shell);
	build_cmd(shell);
}