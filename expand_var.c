/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:46:42 by nosahimi          #+#    #+#             */
/*   Updated: 2025/06/26 12:00:24 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
	<---  the plane ---> 
	
	there is 3 types of $var :

	1_ "$var"	-->	this type gonna expanded with no seperator, the string is literal.	
	2_  $var	-->	this type should treated the same as the prompt,
					 it shold be tokenized and added to the tokenizer list 
	3_ '$var'	--> this is not a variable
	
 
*/

// char *catch_var(char )
// {
	
// }

void	get_expand(t_token *ptr)
{
	int		i;
	char	*str;
	int		*quote;
	
	i = 0;
	quote = global_quote();
	*quote = 0;
	str = ptr->str;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			quote = str[i];
		if (str[i] == '$')
		{
			catch_var();
		}
		i++;	
	}	
}

t_token *find_expand(t_token *tokens_list)
{
	t_token *ptr;
	char 	*str;
	int		i;
	
	ptr = tokens_list;
	while (ptr)
	{
		str = ptr->str;
		i = 0;
		while (str[i])
		{
			if (str[i] == '$')
			{
				get_expand(ptr);
			}
			i++;
		}
		ptr = ptr->next;
	}	
}
