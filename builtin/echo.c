/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:11:16 by aait-laf          #+#    #+#             */
/*   Updated: 2025/08/22 23:39:03 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	echo_fonc(char **arg, int status)
{
	int	i;
	int	flag_newline;

	i = 1;
	flag_newline = 1;
	if (!arg || !arg[0])
		return (-1);
	if (!arg[i])
		return (write(1, "\n", 1), 0);
	i = echo_check_n(arg, &flag_newline, i);
	while (arg[i])
	{
		ft_putstr_fd(arg[i], 1);
		if (arg[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (flag_newline)
		ft_putstr_fd("\n", 1);
	status = 0;
	return (status);
}

int	echo_check_n(char **arg, int *flag_newline, int i)
{
	int	j;
	int	flag_valid;

	while (arg[i] && arg[i][0] == '-' && arg[i][1] && arg[i][1] == 'n')
	{
		j = 1;
		flag_valid = 1;
		while (arg[i][j])
		{
			if (arg[i][j] != 'n')
			{
				flag_valid = 0;
				break ;
			}
			j++;
		}
		if (flag_valid && j > 1)
		{
			*flag_newline = 0;
			i++;
		}
		else
			break ;
	}
	return (i);
}
