/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:54:23 by nosahimi          #+#    #+#             */
/*   Updated: 2025/08/05 12:28:28 by nosahimi         ###   ########.fr       */
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
	dst[i] = '\0';
}

t_env	*creat_node_env(char *name, char *value, int i)
{
	t_env  *env;
	
	// if name or value is null
	 
	env = malloc(sizeof(t_env));
	if (!env)
	{
		//free
	}
	env->next = NULL;
	env->name = malloc(ft_strlen(name) + 1);
	if (!env->name)
	{
		//free
	}
	ft_strcpy(env->name, name);
	env->value = malloc(ft_strlen(value) + 1);
	if (!env->value)
	{
		//free
	}
	ft_strcpy(env->value, value);
	env->index = i;
	return (env);
}

void	add_back_env(t_env **head, char *name,char *value, int i)
{
	t_env *tmp;
	
	if (!*head)
	{
		*head = creat_node_env(name, value, i);
	}
	else 
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = creat_node_env(name, value, i);
	}
}

char *get_env_name(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '=')
		i++;
	return (ft_substr(0, i, str));
}
char	*get_env_value(char *str)
{
	int i;
	
	if (!str)
		return (NULL);
	while(*str != '=')
		str++;
	i = 0;
	while (str[i])
		i++;
	return (ft_substr(1, i, str));
}

t_env *get_env(char **envp)
{
	int i;
	char *name;
	char *value;
	t_env *head;
	
	head = NULL;
	i = 0;
	while (envp[i])
	{
		name = get_env_name(envp[i]);
		value = get_env_value(envp[i]);
		add_back_env(&head,name, value, i);
		i++;
	}
	
	return head;
}


// int main()
// {
// 	t_env *env;
	
	
// 	env = get_env(__environ);
// 	while (env)
// 	{
// 		printf("name = [%s]\nvakue = [%s]\nindex = [%d]\n",env->name, env->value, env->index);
// 		env = env->next;
// 	}
// }
