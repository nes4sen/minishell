/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:53:10 by nosahimi          #+#    #+#             */
/*   Updated: 2025/07/15 18:26:22 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// int		*quote_stat()
// {
// 	static int quote = 0;
// 	return (&quote);
// }


char	*get_token(char **str)
{
	int		quote;
	char 	*s;
	int		i;

	quote  = 0;
	s = *str;
	i = 0;
	while (s[i])
	{
		if(!quote && is_seperator(s[i]))
			break;
		if (!quote && is_quote(s[i]))
			quote = s[i];
		else if (quote == s[i])
			quote = 0;
		i++;
	}
	*str = (s + i);
	return (ft_substr(0, i, s));
}

char *get_token_symbole(char **str)
{
	char	*s;
	int		i;

	i = 0;
	s = *str;
	while (is_symbole(s[i]))
		i++;
	*str = (s + i);
	return (ft_substr(0, i, s));
} 

// echo hello >>>>>>>>> >>  kfkf kdkf
t_token *tokenizer(char *str)
{
	t_token	*head;
	char	*token;
	int		stat;

	stat = 0;
	head = NULL;
	while (*str)
	{	
		while (white_space(*str))
			str++;
		if (is_symbole(*str))
			token = get_token_symbole(&str);
		else if (!*str)
			return (head);
		else
			token = get_token(&str);
		token_add_back(&head, token, 0);
	}
	get_type(head);
	/*----------------------------------------------------------------*/
	printf("\033[1m\n\n----TOKENIZER----\n\n\033[0m\n");
	t_token *tmp = head;
	while (tmp)
	{
		printf("token->str	:[%s]\ntype->type	:[%u]  \n",tmp->str, tmp->type);
		remove_quote(head);
		tmp = tmp->next;
	}
	return (head);
}
// int main()
// {
// 	char str[] = " one  >\"$var\">>   <<  \" > three \"\' for \'";
// 	t_token *token = tokenizer(str);
// 	// t_token *tmp;
	
// 	while (token)
// 	{
// 		printf("[str -> %s			| type -> %d]\n", token->str, token->type);
// 		token= token->next;
// 	}
// }