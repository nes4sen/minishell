/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extoken_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 11:45:03 by nosahimi          #+#    #+#             */
/*   Updated: 2025/07/27 17:25:43 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_extoken *create_extoken_list(char *str, int stat)
{
	t_extoken *token;
	
	token = malloc(sizeof(t_extoken));
	if (!token)
	{
		//free
	}
	token->str = str;
	token->stat = stat;
	return (token);
}
void add_back_extoken(t_extoken **head, char *str, int stat)
{
	t_extoken *tmp;
	
	if (!*head)
		*head = create_extoken_list(str, stat);
	else
	{
		tmp = *head;
		while (tmp)
			tmp = tmp->next;
	}
}