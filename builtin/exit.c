/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:11:24 by aait-laf          #+#    #+#             */
/*   Updated: 2025/08/21 18:48:30 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	exit_fonc(char **arg, int last_code)
{
	int	exit_code;

	exit_code = last_code;
	ft_putstr_fd("exit\n", 1);
	if (arg[1] && arg[2])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	if (arg[1])
		exit_code = help_exit_fonc(arg, exit_code);
	mm_free(FREE_ALL);
	exit(exit_code);
}

int	help_exit_fonc(char **arg, int exit_code)
{
	int	i;

	i = 0;
	if (arg[1][i] == '-' || arg[1][i] == '+')
		i++;
	if (!arg[1][i])
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(arg[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		mm_free(FREE_ALL), exit(2);
	}
	while (arg[1][i])
	{
		if (!ft_isdigit(arg[1][i]))
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(arg[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			mm_free(FREE_ALL), exit(2);
		}
		i++;
	}
	exit_code = ft_atoi(arg[1]);
	return ((unsigned char)exit_code);
}
