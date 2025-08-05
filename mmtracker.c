/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmtracker.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 12:37:39 by nosahimi          #+#    #+#             */
/*   Updated: 2025/08/05 19:25:01 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_mmtrack *create_mm_node(void *ptr)
{
    t_mmtrack *new_node;

    new_node = malloc(sizeof(t_mmtrack));
    if (!new_node)
    {
        // free_all
        exit(EXIT_FAILURE);
    }
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
	{
		//free all
	}
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


void	free_env(void)
{
	t_address_track *track;
	t_env			*head;
	t_env			*tmp;

	track = address_tracker();
	head = track->env;
	while (head)
	{
		tmp = head->next;	
		free(head->value);
		free(head->name);
		free(head);
		head = tmp;	
	}
}

void free_others(void)
{
	t_address_track	*track;
	t_mmtrack		*head;
	void			*pointer_inside;

	track = address_tracker();
	head = track->head;
	while (head)
	{
		pointer_inside = head->next;
		free(head->ptr);
		free(head);
		head = pointer_inside;
	}
}

void	mm_free(int	which_free)
{
	if (which_free == FREE_ALL)
	{
		free_env();
		free_others();
		// free fd
	}
	else if (which_free == FREE_ALL_EXCEPT_ENV)
	{
		free_others();
		//free fd
	}
}
