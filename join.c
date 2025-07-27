/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:02:11 by nosahimi          #+#    #+#             */
/*   Updated: 2025/07/27 11:31:02 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *str_join(char *old, char *new)
{
    char *result;
    int old_len;
    int new_len;
    
    if (!old && !new)
        return (NULL);
    old_len = ft_strlen(old);
    new_len = ft_strlen(new);
    result = malloc(old_len + new_len + 1);
    if (!result)
        //free
    ft_strcpy(result, old);
    ft_strcpy(result + old_len, new);
    return (result);
}

char *char_join(char *old, char c, int *index)
{
    char *result;
    int old_len;

    if (!old)
        return (NULL);
    old_len = ft_strlen(old);
    result = malloc(old_len + 2);
    if (!result)
        //free
    ft_strcpy(result, old);
    result[old_len] = c;
    result[old_len + 1] = '\0';
	*index += 1;
    return (result);
}
