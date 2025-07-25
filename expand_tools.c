/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:16:13 by nosahimi          #+#    #+#             */
/*   Updated: 2025/07/25 11:30:43 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// in the fucntion bellow , i dont check if !var cuz i cant acces to this function only f the var is true
char *find_env_var(t_env *env, char *var)
{
	while (env)
	{
		if (!ft_strcmp(var, env->name))
			return (env->value);
		env = env->next;
	}
	return (ft_substr(0 , 1, ""));
}

char is_valid_env_var_name(char c)
{
	if (!(c >= 'a' && c <= 'z') && !(c >= 'A' && c <= 'Z')
		&& c != '_')
		return (0);
	return (1);
}

char *extract_var_name(char *str)
{
	int		i;

	i = 1;
	if (!is_valid_env_var_name(str[i])
		|| str[i] >= '0' && str[i] <= '9')
		return (NULL);
	while (str[i])
	{
		if (!is_valid_env_var_name(str[i]))
			break;
		i++;
	}
	return (ft_substr(1 , i, str + 1));
}