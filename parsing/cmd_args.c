/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:26:52 by nosahimi          #+#    #+#             */
/*   Updated: 2025/08/21 17:09:58 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*alloc_word(char *str)
{
	char	*arg;

	arg = mm_alloc(ft_strlen(str) + 1);
	ft_strcpy(arg, str);
	return (arg);
}

int	args_len(t_token *token)
{
	int		len;
	t_token	*tmp;

	len = 0;
	while (token && token->type != PIPE)
	{
		if (token->subtoken)
		{
			tmp = token->subtoken;
			while (tmp)
			{
				if (*(tmp->str))
					len++;
				tmp = tmp->next;
			}
		}
		else if (token->type == CMD)
		{
			if (*(token->str))
				len++;
		}
		token = token->next;
	}
	return (len);
}

char	**space_for_args(t_token *token)
{
	int		len;
	char	**args;
	int		i;

	len = args_len(token);
	if (len == 0)
		return (NULL);
	i = 0;
	args = mm_alloc(sizeof(char *) * (len + 1));
	while (i <= len)
	{
		args[i] = NULL;
		i++;
	}
	return (args);
}

void	get_args(char **args, t_token *token, int *i)
{
	if (token->subtoken && token->type == CMD)
	{
		while (token->subtoken)
		{
			if (*(token->subtoken->str))
			{
				args[*i] = alloc_word(token->subtoken->str);
				(*i)++;
			}
			token->subtoken = token->subtoken->next;
		}
	}
	else if (token->type == CMD)
	{
		if (*(token->str))
		{
			args[*i] = alloc_word(token->str);
			(*i)++;
		}
	}
}
