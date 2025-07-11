/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:46:42 by nosahimi          #+#    #+#             */
/*   Updated: 2025/07/11 12:05:34 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int *global_quote_stat()
{
	static int quote = 0;
	return (&quote);
}
// get_expand
ft_exstrlen(char *str)
{
	int	i;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i])
	}
}
ft_exstrcpy()
{
	
}
ft_exsubstr()
{
	
}
t_token *expand_token(t_env *env, char *str)
{
	int 	i;
	int		quote;
	t_token *head;
	int		j;

	j = 0;
	quote = 0;
	i = 0;
	head = NULL;
	while (str[i])
	{
		if (!quote && (str[i] == '\'' || str[i] == '"'))
			quote = str[i++];		
		else if (quote == str[i])
			quote = 0;
		if (str[i] == '$' && quote != '\'')
		{
			token_add_back(&head, ft_substr(j, i, str), 0);
			get_expand();
		}
		j = i;
	}
}


/* 
							var="1   2     3  "
build anouther tokenizer that split tokens by quotes and give them a stat

example 	echo hello"$var"'$var'" "    

normal tokenizer 		[echo] [hello"$var toto"'$var'$var" "]

expand_tokenizer 		[echo] [hello] ["$var toto"] ['$var'] [$var] [" "]

						[echo] [hello] ["1  2  3  toto"] ['$var'] [1   2   3] [" "]	

*/