/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmtracker.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 12:37:39 by nosahimi          #+#    #+#             */
/*   Updated: 2025/08/05 14:17:25 by nosahimi         ###   ########.fr       */
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

void	mm_alloc(size_t size)
{
	t_mmtrack		*head;
	t_mmtrack		*tail;
	t_adress_track	*tracker;
	
	tracker = adress_tracker();
	head = tracker->head;
	tail = tracker->tail;
	if (!head)
		head = create_mm_node(size);
	else
	{
		tail = head->next;
		tail = create_mm_node(size);
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

void	free_env()
{
	t_adress_track *track;
	t_env			*head;
	t_env			*tmp;

	track = adress_tracker();
	while (head)
	{
		tmp = head->next;	
		free(head->value);
		free(head->name);
		free(head);
		head = tmp;	
	}
}

void free_others()
{
	t_adress_track	*track;
	t_mmtrack		*head;
	void			*pointer_inside;

	
	while (head)
	{
		pointer_inside = head->next;
		free(head->ptr);
		free(head);
		head = pointer_inside;
	}

}

/*

char **ptr1 = mm_alloc(size);
int *ptr2 = mm_alloc(size);
char *ptr3 = mm_alloc(size);

garbage_collector --> [ptr1]--[ptr2]--[ptr3]

*/
