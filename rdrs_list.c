/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdrs_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:18:47 by nosahimi          #+#    #+#             */
/*   Updated: 2025/07/02 11:56:05 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_rdr *create_node_rdr( char *str, int type)
{
	t_rdr *ptr;
	char	*file;
	
	ptr = malloc(sizeof(t_rdr));
	if (!ptr)
	{
		//free
	}
	file = malloc(ft_strlen(str) + 1);
	if (!file)
	{
		//free;
	}
	ft_strcpy(file, str);
	ptr->next = NULL;
	ptr->file = file;
	ptr->type = type;
	// printf("[ptr->file %s	|	ptr->type = %d]\n",ptr->file, ptr->type);
	return (ptr);
}

void	add_back_rdr(t_rdr **head, char *file, int type)
{
	t_rdr *ptr;

	if (!*head)
	{
		*head = create_node_rdr(file, type);
	}
	else
	{
		ptr = *head;
		while (ptr->next)
		{
			// printf("[ptr->file = %s\n]",ptr->file);
			ptr = ptr->next;
		}
		ptr->next = create_node_rdr(file, type); // --> the segv from here 
	}
}
