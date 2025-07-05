/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:53:10 by nosahimi          #+#    #+#             */
/*   Updated: 2025/07/05 14:20:22 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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
		if (!quote && (s[i] == '\'' || s[i] == '\"'))
			quote = s[i];
		else if (s[i] == quote)
			quote = 0;
		if ((white_space(s[i]) || is_symbole(s[i])) && !quote)
			break;
		i++;
	}
	*str = (s + i);
	return (ft_substr(0, i, s));
}

char *get_token_symbole(char **str)
{
	int		i;
	char	*s;
	
	i = 0;
	s = *str;
	if (is_symbole(s[i]))
	{
		if (is_symbole(s[i + 1]))
			i++;
		i++;
	}
	*str = (s + i);
	return (ft_substr(0, i, s));
}

char *encounter_str(char **str, char *token)
{
	if (is_symbole(**str))
		token = get_token_symbole(str);
	else
		token = get_token(str);
	return (token);
}

t_token *tokenizer(char *str)
{
	t_token	*head;
	char	*token;
	int 	type;

	head = NULL;
	type = 0;
	while (*str)
	{
		while (white_space(*str))
			str++;
		token = encounter_str(&str, token);
		if (type < 3)
		{
			type = get_type(token);
			token_add_back(&head, token, type);
		}
		else
		{
			token_add_back(&head, token, 6);
			type = 0;
		}
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