/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 10:47:05 by nosahimi          #+#    #+#             */
/*   Updated: 2025/08/22 23:06:43 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_address_track	*address_tracker(void)
{
	static t_address_track	p = {0};

	return (&p);
}

void	init_env(char **envp, t_shell *shell)
{
	t_address_track	*track;

	track = address_tracker();
	shell->env = get_env(envp);
}

void	init_structs_after_free(t_shell *shell)
{
	shell->line = NULL;
	shell->tokens = NULL;
	shell->cmd = NULL;
	shell->mmtrack = NULL;
}

void	handle_segnal_herd(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	mm_free(FREE_ALL);
	exit(130);
}
