/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:11:43 by aait-laf          #+#    #+#             */
/*   Updated: 2025/08/21 17:50:36 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	fonc_pwd(char **arg, t_env *env)
{
	if (!arg || !env)
	{
		return (1);
	}
	if (arg[1])
	{
		ft_putstr_fd("pwd: too many arguments\n", 2);
		return (1);
	}
	print_repert(env);
	return (0);
}

void	print_repert(t_env *env)
{
	char	*result;

	if (!env)
	{
		ft_putstr_fd("No environment variables set.\n", 2);
		return ;
	}
	result = getcwd(NULL, 0);
	if (!result)
	{
		perror("getcwd");
		return ;
	}
	ft_putstr_fd(result, 1);
	ft_putstr_fd("\n", 1);
	free(result);
}

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	if (!s1 || !s2)
		return (1);
	i = 0;
	while (i < n && s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	if (i < n)
		return (s1[i] != s2[i]);
	return (0);
}
