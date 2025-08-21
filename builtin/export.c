/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:11:36 by aait-laf          #+#    #+#             */
/*   Updated: 2025/08/21 17:50:33 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	fonc_export(char **arg, t_env **env)
{
	int	i;
	int	status;
	int	final_status;

	if (!arg)
		return (-1);
	if (!arg[1])
	{
		print_env(*env);
		return (0);
	}
	i = 1;
	final_status = 0;
	while (arg[i])
	{
		if (has_equal_sign(arg[i]))
			status = var_with_equal(arg, i, env);
		else
			status = var_no_value(arg, i, env);
		if (status != 0)
			final_status = status;
		i++;
	}
	return (final_status);
}

char	*get_var_name(char *str)
{
	char	*name;
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	name = ft_substr(0, i, str);
	return (name);
}

int	check_var_exist_env(t_env *env, char *name)
{
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
			return (1);
		env = env->next;
	}
	return (-1);
}

void	updat_env(t_env **env, char *name, char *value)
{
	t_env	*current;

	if (!env || !name)
		return ;
	current = *env;
	while (current)
	{
		if (ft_strcmp(name, current->name) == 0)
		{
			if (value)
				current->value = ft_strdup(value);
			return ;
		}
		current = current->next;
	}
}

void	add_double_quotes(char *value, char *name, t_env *env)
{
	char	*new_str;

	int (i), (j);
	if (!value || !name || !env)
		return ;
	new_str = mm_alloc(ft_strlen(value) + 1);
	if (!new_str)
		return ;
	(1) && (i = 1, j = 0);
	while (value[j])
		new_str[i++] = value[j++];
	new_str[i] = '\0';
	while (env)
	{
		if (ft_strcmp(name, env->name) == 0)
			return ;
		env = env->next;
	}
	free(new_str);
}
