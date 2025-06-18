/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:54:23 by nosahimi          #+#    #+#             */
/*   Updated: 2025/06/15 12:12:06 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen(char *str)
{
	int i;
	
	if(!str)
		return (0);
	i = 0;
	while(str[i])
		i++;
	return (i);
}

void	ft_strcpy(char *dst, char *src)
{
	int i;
	
	if (!dst || !src)
		return ;
	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
}

t_env	*creat_node_env(char *str)
{
	t_env  *env;
	
	env = malloc(sizeof(t_env));
	if (!env)
	{
		//free
	}
	env->next = NULL;
	env->str = malloc(ft_strlen(str) + 1);
	if (!env->str)
	{
		//free
	}
	ft_strcpy(env->str, str);
	return (env);
}

void	add_back_env(t_env **head, char *str)
{
	t_env *tmp;
	
	if (!*head)
	{
		*head = creat_node_env(str);
	}
	else 
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = creat_node_env(str);
	}
}

t_env *get_env(char **envp)
{
	int i;
	
	t_env *head;
	
	head = NULL;
	i = 0;
	while (envp[i])
	{
		add_back_env(&head, envp[i]);
		i++;
	}
	return head;
}



