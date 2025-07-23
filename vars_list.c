/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:13:43 by nosahimi          #+#    #+#             */
/*   Updated: 2025/07/23 13:24:42 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.c"

t_vars *create_node_var(char *value, int s, int e)
{
	t_vars *p;
	
	p = malloc(sizeof(t_vars));
	if (!p)
		//free
	p->start = s;
	p->end = e;
	p->value = value;
	p->next = NULL;
	
	return (p);
}
void add_back_var(t_vars **head, char *val, int s, int e)
{
	t_vars *tmp;
	
	if (!*head)
		*head = create_node_var(val, s, e);
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = create_node_var(val, s, e);
	}
	
}