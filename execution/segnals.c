/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segnals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-laf <aait-laf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:39:49 by aait-laf          #+#    #+#             */
/*   Updated: 2025/08/21 14:46:04 by aait-laf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	g_sigint = 0;

void	handler_ctrl_c(int sig)
{
	if (sig == SIGINT)
	{
		g_sigint = SIGINT;
		rl_on_new_line();
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

// Fonction pour configurer les gestionnaires de signaux
void	setup_signals(void)
{
	signal(SIGINT, handler_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}

t_shell	*get_shell(t_shell *shell)
{
	static t_shell	*save;

	if (shell)
		save = shell;
	return (save);
}

int	idx_nod(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		env->index = i++;
		env = env->next;
	}
	return (i);
}

int	ft_strchr(char *str, char c)
{
	int	i;

	if (!str)
		return (1);
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (0);
		i++;
	}
	return (1);
}
