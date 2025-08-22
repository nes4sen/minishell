/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llmmtracker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 20:31:05 by nosahimi          #+#    #+#             */
/*   Updated: 2025/08/22 23:52:08 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*ll_substr(int start, int end, char *str)
{
	int		len;
	char	*s;
	int		i;

	len = (end - start);
	s = ll_alloc(len + 1);
	i = 0;
	while (start < end)
	{
		s[i] = str[start];
		i++;
		start++;
	}
	s[i] = '\0';
	return (s);
}

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
	t_lltrack		*tmp_next;

	track = address_tracker();
	head = track->lhead;
	if (!head)
		return ;
	while (head)
	{
		tmp_next = head->next;
		free(head->ptr);
		free(head);
		head = tmp_next;
	}
	track->lhead = NULL;
	track->ltail = NULL;
}
