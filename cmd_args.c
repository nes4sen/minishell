/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:26:52 by nosahimi          #+#    #+#             */
/*   Updated: 2025/07/31 11:34:44 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char *alloc_word(char *str)
{
	char *arg;

	arg = malloc(sizeof(str) + 1);
	if (!arg)
	{
	//free
	}
	ft_strcpy(arg, str);
	return (arg);
}

int args_len(t_token *token)
{
	int len;
	t_token *tmp;

	len = 0;
	while (token)
	{
		if (token->subtoken)
		{
			tmp = token->subtoken;
			while (tmp)
			{
				len++;
				tmp = tmp->next;	
			}
		}else if (token->type == CMD)
			len++;
		token = token->next;
	}
	return (len);
}

char **space_for_args(t_token *token)
{
	int len;
	char **args;
	int i;

	len = args_len(token);
	if (len == 0)
		return (NULL);
	i = 0;
	args = malloc(sizeof(char *) * (len + 1));
	if (!args)
	{
		//free
	}
	while (i < len)
	{
		args[i] = NULL;
		i++;
	}
	return (args);
}

void get_args(char ***args, t_token *token)
{
	int i;

	i = 0;
	if (token->subtoken)
	{
		while (token->subtoken)
		{
			(*args)[i] = alloc_word(token->subtoken->str);
				i++;
			token->subtoken = token->subtoken->next;
		}
	}
	else if (token->type == CMD)
	{
		(*args)[i] = alloc_word(token->str);
		i++;
	}
}