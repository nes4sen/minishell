/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eenv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:11:20 by aait-laf          #+#    #+#             */
/*   Updated: 2025/08/21 17:50:33 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	env_fonc(char **arg, t_env *env)
{
	int	status;

	if (!env || !arg)
		return (-1);
	if (arg[1])
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(arg[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (127);
	}
	status = help_env_fonc(env);
	return (status);
}

int	help_env_fonc(t_env *env)
{
	char	*name_value;
	char	*temp;

	while (env != NULL)
	{
		if (env->value == NULL)
			env = env->next;
		else
		{
			temp = ft_strjoin(env->name, "=");
			if (!temp)
				return (-1);
			name_value = ft_strjoin(temp, env->value);
			if (!name_value)
				return (-1);
			printf("%s\n", name_value);
			env = env->next;
		}
	}
	return (0);
}
