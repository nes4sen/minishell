/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:11:56 by aait-laf          #+#    #+#             */
/*   Updated: 2025/08/21 17:50:26 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*find_home_repert(t_env *env, char *str)
{
	while (env)
	{
		if (ft_strcmp(env->name, str) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int	cd_zero_arg(char *tmp, char *pwd_now, char *cur, t_env *env)
{
	tmp = find_home_repert(env, "HOME");
	if (tmp != NULL)
	{
		if (chdir(tmp) == -1)
		{
			ft_putstr_fd("cd: no such file or directory: ", 2);
			ft_putstr_fd(tmp, 2);
			ft_putstr_fd("\n", 2);
			return (-1);
		}
		if (pwd_now)
			update_env(&env, "OLDPWD", pwd_now);
		else
			update_env(&env, "OLDPWD", "");
		cur = getcwd(NULL, 0);
		if (!cur)
			return (perror("getcwd"), -1);
		update_env(&env, "PWD", cur);
		free(cur);
	}
	else
		return (ft_putstr_fd("cd: HOME not set\n", 2), -1);
	return (0);
}

int	cd_whith_1p(char *pwd_now, char *cur, t_env *env)
{
	if (pwd_now)
		update_env(&env, "OLDPWD", pwd_now);
	else
		update_env(&env, "OLDPWD", "");
	cur = getcwd(NULL, 0);
	if (!cur)
	{
		perror("getcwd");
		return (free(pwd_now), -1);
	}
	update_env(&env, "PWD", cur);
	free(cur);
	return (0);
}

int	cd_whith_2p(char *pwd_now, char *cur, t_env *env)
{
	if (chdir("..") == -1)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putstr_fd("..", 2);
		ft_putstr_fd("\n", 2);
		return (-1);
	}
	if (pwd_now)
		update_env(&env, "OLDPWD", pwd_now);
	else
		update_env(&env, "OLDPWD", "");
	cur = getcwd(NULL, 0);
	if (!cur)
	{
		perror("getcwd");
		return (-1);
	}
	update_env(&env, "PWD", cur);
	free(cur);
	return (0);
}

int	cd_with_arg(char **arg, char *pwd_now, char *cur, t_env *env)
{
	int	status;

	status = 0;
	if (chdir(arg[1]) == -1)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		(ft_putstr_fd(arg[1], 2)), (ft_putstr_fd("\n", 2));
		return (-1);
	}
	if (pwd_now)
		update_env(&env, "OLDPWD", pwd_now);
	else
		update_env(&env, "OLDPWD", "");
	cur = getcwd(NULL, 0);
	if (!cur)
	{
		perror("getcwd");
		return (-1);
	}
	update_env(&env, "PWD", cur);
	free(cur);
	return (status);
}
