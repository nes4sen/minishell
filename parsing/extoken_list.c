/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extoken_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 11:45:03 by nosahimi          #+#    #+#             */
/*   Updated: 2025/08/21 17:12:51 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_extoken	*create_extoken_list(char *str, int stat)
{
	t_extoken	*token;

	token = mm_alloc(sizeof(t_extoken));
	token->str = str;
	token->stat = stat;
	token->next = NULL;
	return (token);
}

void	add_back_extoken(t_extoken **head, char *str, int stat)
{
	t_extoken	*tmp;

	if (!*head)
		*head = create_extoken_list(str, stat);
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = create_extoken_list(str, stat);
	}
}
