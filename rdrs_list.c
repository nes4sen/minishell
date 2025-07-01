/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdrs_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:18:47 by nosahimi          #+#    #+#             */
/*   Updated: 2025/07/01 17:16:50 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_rdr *create_node_rdr( char *file, int type)
{
	t_rdr *ptr;
	
	ptr = malloc(sizeof(t_rdr));
	if (!ptr)
	{
		//free
	}
	ptr->next = NULL;
	ptr->file = file;
	ptr->type = type;
	return (ptr);
}

void	add_back_rdr(t_rdr **head, char *file, int type)
{
	t_rdr *ptr;

	if (!*head)
	{
		*head = create_node_rdr( file, type);
	}
	else
	{
		ptr = *head;
		while (ptr)
			ptr = ptr->next;
		ptr->next = create_node_rdr(file, type);
	}
}
