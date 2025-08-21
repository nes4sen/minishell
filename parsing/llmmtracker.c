/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llmmtracker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 20:31:05 by nosahimi          #+#    #+#             */
/*   Updated: 2025/08/21 17:17:08 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/*
ll stands for long life,
this memory allocater used when something related to env is allocated
*/
void	*create_llmm_node(void *ptr)
{
	t_lltrack	*new_node;

	new_node = malloc(sizeof(t_lltrack));
	if (!new_node)
		alloc_faild_cleanup();
	new_node->ptr = ptr;
	new_node->next = NULL;
	return (new_node);
}

void	*ll_alloc(size_t size)
{
	t_address_track	*track;
	void			*ptr;

	track = address_tracker();
	ptr = malloc(size);
	if (!ptr)
		alloc_faild_cleanup();
	if (!track->lhead)
	{
		track->lhead = create_llmm_node(ptr);
		track->ltail = track->lhead;
	}
	else
	{
		track->ltail->next = create_llmm_node(ptr);
		track->ltail = track->ltail->next;
	}
	return (ptr);
}

void	free_lltrack(void)
{
	t_address_track	*track;
	t_lltrack		*head;
	void			*tmp_next;

	track = address_tracker();
	head = track->lhead;
	while (head)
	{
		tmp_next = head->ptr;
		free(head->ptr);
		free(head);
		head = tmp_next;
	}
	track->head = NULL;
	track->tail = NULL;
	track = NULL;
}
