/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmtracker.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 12:37:39 by nosahimi          #+#    #+#             */
/*   Updated: 2025/08/04 21:41:22 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mmtrack *create_mm_node(void *ptr, t_mmtrack *head)
{
    t_mmtrack *new_node;

    new_node = malloc(sizeof(t_mmtrack));
    if (!new_node)
    {
        mm_alloc(0, FREE_ALL);
        exit(EXIT_FAILURE);
    }
    new_node->ptr = ptr;
    new_node->next = NULL;
    return (new_node);
}

void mm_alloc(size_t size, int free_flag)
{
	static t_mmtrack	*mm_head = NULL;
	static t_mmtrack	*mm_tail = NULL;
    void 				*ptr;

	if (free_flag == FREE_ALL)
	{
		mm_free(mm_head);
		allocat_env(1);
	}
	else if(free_flag == FREE_ALL_EXCEPT_ENV)
		mm_free(mm_head);
    ptr = malloc(size);
    if (!ptr)
		//free
    if (!mm_head)
        mm_head = create_mm_node(ptr, mm_head);
    else
	{
		mm_tail = mm_head->next;
        mm_tail = create_mm_node(ptr, mm_head);
	}
}

void mm_free(t_mmtrack *mm_head)
{
    t_mmtrack *tmp;
    t_mmtrack *next_node;

    tmp = mm_head;
    while (tmp)
    {
        next_node = tmp->next;
        free(tmp->ptr);
        free(tmp);
        tmp = next_node;
    } 
}

void mm_free_env(t_mmenv *mm_head)
{
	t_mmenv		*tmp;
    t_mmenv		*next_node;

    tmp = mm_head;
    while (tmp)
    {
        next_node = tmp->next;
        free(tmp->ptr);
        free(tmp);
        tmp = next_node;
    }
}

t_mmtrack *create_mmenv_node(void *ptr, t_mmenv *head)
{
    t_mmenv *new_node;

    new_node = malloc(sizeof(t_mmenv));
    if (!new_node)
    {
        mm_alloc(0, FREE_ALL);
        exit(EXIT_FAILURE);
    }
    new_node->ptr = ptr;
    new_node->next = NULL;
    return (new_node);
}
	
void	allocat_env(size_t size, int free_flag)
{
	static t_mmenv	*head = NULL;
	static t_mmenv	*tail = NULL;
	void			*ptr;

	if (free_flag)
		mm_free_env(head);
	ptr = malloc(size);
	if (!ptr)
	{
		mm_alloc(0, FREE_ALL);
        exit(EXIT_FAILURE);
	}
	if (!head)
		head = create_mmenv_node()
}
/*


*/