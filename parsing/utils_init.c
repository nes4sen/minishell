/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 10:47:05 by nosahimi          #+#    #+#             */
/*   Updated: 2025/08/16 17:17:48 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_address_track *address_tracker(void)
{
	static t_address_track p = {0};
	return (&p);
}

void	init_env(char **envp, t_shell *shell)
{
	t_address_track *track;

	track = address_tracker();
	track->env = get_env(envp);
	shell->env = track->env; 
}


void init_structs_after_free(t_shell *shell)
{
	shell->line = NULL;
    shell->tokens = NULL;
    shell->cmd = NULL;
    shell->mmtrack = NULL;
	// shell->cmd->heredox = NULL;
}