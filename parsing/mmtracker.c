/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmtracker.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 12:37:39 by nosahimi          #+#    #+#             */
/*   Updated: 2025/08/22 23:52:15 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_mmtrack	*create_mm_node(void *ptr)
{
	t_mmtrack	*new_node;

	new_node = malloc(sizeof(t_mmtrack));
	if (!new_node)
		alloc_faild_cleanup();
	new_node->ptr = ptr;
	new_node->next = NULL;
	return (new_node);
}

void	*mm_alloc(size_t size)
{
	t_address_track	*tracker;
	void			*ptr;

	tracker = address_tracker();
	ptr = malloc(size);
	if (!ptr)
		alloc_faild_cleanup();
	if (!tracker->head)
	{
		tracker->head = create_mm_node(ptr);
		tracker->tail = tracker->head;
	}
	else
	{
		tracker->tail->next = create_mm_node(ptr);
		tracker->tail = tracker->tail->next;
	}
	return (ptr);
}

void	free_others(void)
{
	t_address_track	*track;
	t_mmtrack		*head;
	t_mmtrack		*tmp_next;

	track = address_tracker();
	head = track->head;
	while (head)
	{
		tmp_next = head->next;
		free(head->ptr);
		free(head);
		head = tmp_next;
	}
	free(track->line);
	track->line = NULL;
	track->head = NULL;
	track->tail = NULL;
	track->line = NULL;
}

void	mm_free(int which_free)
{
	if (which_free == FREE_ALL)
	{
		free_lltrack();
		free_others();
	}
	else if (which_free == FREE_ALL_EXCEPT_ENV)
		free_others();
}
