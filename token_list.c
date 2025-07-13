/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:43:28 by nosahimi          #+#    #+#             */
/*   Updated: 2025/07/13 17:19:51 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	assigne_stat(char c)
{
	int stat;
	
	stat = NO_QUOTE;
	if (c == '\'')
		stat = SINGLE_QUOTE;
	else if (c == '"')
		stat = DOUBLE_QUOTE;
	return (stat);
}

t_token *creat_token(char *token, t_type type, int stat)
{
	t_token *p;

	p = malloc(sizeof(t_token));
	if (!p)
	{
	 //free
	}
	p->str = token;
	p->type = type;
	p->stat = stat;
	p->next = NULL;
	return (p);
}

void token_add_back(t_token **head, char *token, t_type type, int stat)
{
	t_token *ptr;

	ptr = *head;
	if (!*head)
	{
		*head = creat_token(token, type, stat);
	}
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = creat_token(token, type, stat);
	}
}
