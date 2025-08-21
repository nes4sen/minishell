/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:43:28 by nosahimi          #+#    #+#             */
/*   Updated: 2025/08/21 10:27:06 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_token	*create_token(char *token, t_type type)
{
	t_token	*p;

	p = mm_alloc(sizeof(t_token));
	p->str = token;
	p->type = type;
	p->subtoken = NULL;
	p->next = NULL;
	return (p);
}

void	token_add_back(t_token **head, char *token, t_type type)
{
	t_token	*ptr;

	ptr = *head;
	if (!*head)
		*head = create_token(token, type);
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = create_token(token, type);
	}
}
