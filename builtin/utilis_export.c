/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:11:52 by aait-laf          #+#    #+#             */
/*   Updated: 2025/08/21 17:50:33 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	print_env(t_env *env)
{
	while (env)
	{
		if (ft_strcmp("_", env->name) == 0)
			env = env->next;
		else if (env->value == NULL)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(env->name, 1);
			ft_putstr_fd("\n", 1);
			env = env->next;
		}
		else
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(env->name, 1);
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(env->value, 1);
			ft_putstr_fd("\"\n", 1);
			env = env->next;
		}
	}
}

int	var_with_equal(char **arg, int i, t_env **env)
{
	char	*name;
	char	*value;

	name = NULL;
	value = NULL;
	name = get_var_name(arg[i]);
	value = get_var_value(arg[i]);
	if (!is_valid_name(name))
	{
		export_error(arg[1]);
		return (127);
	}
	if (check_var_exist_env(*env, name) == -1)
		add_back_env(env, name, value, (idx_nod(*env) + 1));
	else
		updat_env(env, name, value);
	return (0);
}

int	is_valid_name(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	var_no_value(char **arg, int i, t_env **env)
{
	char	*name;

	if (!is_valid_name(arg[i]))
	{
		export_error(arg[i]);
		return (-1);
	}
	name = get_var_name(arg[i]);
	if (check_var_exist_env(*env, name) == -1)
		add_back_env(env, name, NULL, (idx_nod(*env) + 1));
	else
		mak_as_export(env, arg[i]);
	return (0);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
}
