/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmtracker.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 12:37:39 by nosahimi          #+#    #+#             */
/*   Updated: 2025/08/01 23:15:56 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_mmtrack
{
    void *ptr;
    struct s_mmtracker *next;
} t_mmtrack;

t_mmtrack *create_mm_node(void *ptr)
{
    t_mmtrack *new_node;

    new_node = malloc(sizeof(t_mmtrack));
    if (!new_node)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    new_node->ptr = ptr;
    new_node->next = NULL;
    return (new_node);
}


void *mm_alloc(size_t size, t_mmtrack **mm_head)
{
    void *ptr;
    t_mmtrack *new_node;
    t_mmtrack *tmp;

    ptr = malloc(size);
    if (!ptr)
    {
        perror("Memory allocation failed");
        // free all
        exit(EXIT_FAILURE);
    }
    if (!*mm_head)
    {
        *mm_head = create_mm_node(ptr);
    }
    else
    {
        tmp = *mm_head;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = create_mm_node(ptr);
    }
    return (ptr);
}

void mm_free(t_mmtrack **mm_head)
{
    t_mmtrack *tmp;
    t_mmtrack *next_node;

    tmp = *mm_head;
    while (tmp)
    {
        next_node = tmp->next;
        free(tmp->ptr);
        free(tmp);
        tmp = next_node;
    }
    *mm_head = NULL;   
}