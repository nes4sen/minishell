/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:54:23 by nosahimi          #+#    #+#             */
/*   Updated: 2025/08/21 16:58:46 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_env	*creat_node_env(char *name, char *value, int i)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		alloc_faild_cleanup();
	env->next = NULL;
	env->name = NULL;
	env->value = NULL;
	env->index = i;
	env->next = NULL;
	env->name = malloc(ft_strlen(name) + 1);
	if (!env->name)
		alloc_faild_cleanup();
	ft_strcpy(env->name, name);
	if (value == NULL)
		env->value = NULL;
	else
	{
		env->value = malloc(ft_strlen(value) + 1);
		if (!env->value)
			alloc_faild_cleanup();
		ft_strcpy(env->value, value);
	}
	return (env);
}

void	add_back_env(t_env **head, char *name, char *value, int i)
{
	t_env	*tmp;

	if (!*head)
		*head = creat_node_env(name, value, i);
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = creat_node_env(name, value, i);
	}
}

char	*get_env_name(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '=')
		i++;
	return (ft_substr(0, i, str));
}

char	*get_env_value(char *str)
{
	int	i;

	if (!str)
		return (NULL);
	while (*str != '=')
		str++;
	i = 0;
	while (str[i])
		i++;
	return (ft_substr(1, i, str));
}

t_env	*get_env(char **envp)
{
	int		i;
	char	*name;
	char	*value;
	t_env	*head;

	head = NULL;
	i = 0;
	while (envp[i])
	{
		name = get_env_name(envp[i]);
		value = get_env_value(envp[i]);
		add_back_env(&head, name, value, i);
		i++;
	}
	return (head);
}
