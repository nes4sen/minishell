/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 11:45:03 by nosahimi          #+#    #+#             */
/*   Updated: 2025/07/20 18:46:49 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_extoken *create_extoken_list(char *str, int stat)
{
	t_extoken *token;
	
	token = malloc(sizeof(t_extoken));
	if (!token)
	{
		//free
	}
	token->str = str;
	token->stat = stat;
	
}
void add_back_extoken(t_extoken **head, char *str, int stat)
{
	t_extoken *tmp;
	
	if (!*head)
		*head = create_extoken_list(str, stat);
	else
	{
		tmp = *head;
		while (tmp)
			tmp = tmp->next;
	}
}

// char *get_extoken()
// {
	
// }
// char *get_quoted_extoken(char **str)
// {
// 	char 	*s;

// 	s = *str;
	
// }
// t_extoken extokenizer(char *str)
// {
// 	int		i;
// 	char	*extoken;
	
// 	i = 0;
// 	extoken = NULL;
// 	while (*str)
// 	{
// 		if (is_quote(*str))
// 			get_quoted_extoken(&str);
// 		else
// 			get_extoken();	
// 	}
// }
// what needed in the expand list 


