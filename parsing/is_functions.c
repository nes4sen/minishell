/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 11:09:49 by nosahimi          #+#    #+#             */
/*   Updated: 2025/08/12 22:42:49 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_symbole(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (c);
	return (0);
}
int	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0); 
}
int is_seperator(char c)
{
	if (is_symbole(c) || white_space(c))
		return (1);
	return (0);
}
int is_oprt(char *op)
{
	if ((def_type(op) >= 1  && def_type(op) <= 5))
		return (1);
	return (0);	
}