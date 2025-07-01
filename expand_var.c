/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:46:42 by nosahimi          #+#    #+#             */
/*   Updated: 2025/06/29 18:44:54 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
	<---  the plane ---> 
	
	there is 3 types of $var :

	1_ "$var"	-->	this type gonna expanded with no seperator, the string is literal.	
	2_  $var	-->	this type should treated the same as the prompt,
					 it shold be tokenized and added to the tokenizer list
					 in this case
					 			 |-> the $var shold be split
	3_ '$var'	--> this is not a variable
	
 
*/

// char *catch_var(char )
// {
	
// }



void	get_expand(t_token *ptr, int i)
{
	char	*str;
	int		i;
	
	str = ptr->str;
	i = 0;
	while (str[i])
	{
		
	}
	
}
//this function below loop into the strings and find the expandable var 
t_token *find_expand(t_token *tokens_list)
{
	t_token	*ptr;
	int		i;
	int		quote;
	
	ptr = tokens_list;
	quote = 0;
	while (ptr)
	{
		i = 0;
		while(ptr->str[i])
		{
			if (!quote)
			{	
				if (ptr->str[i] == '\'' || ptr->str[i] == '\"')
					quote = ptr->str[i];
			}
			if (ptr->str[i] == quote)
				quote = 0;
			if (ptr->str[i] == '$' && quote != '\'')
				get_expand(ptr, i);
			i++;
		}
		ptr = ptr->next;
	}	
}
