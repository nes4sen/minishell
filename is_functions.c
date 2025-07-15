/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 11:09:49 by nosahimi          #+#    #+#             */
/*   Updated: 2025/07/14 17:02:44 by nosahimi         ###   ########.fr       */
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
	if ((def_type(op) >= 1  && def_type(op) <= 4))
		return (1);
	return (0);	
}