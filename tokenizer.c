/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:53:10 by nosahimi          #+#    #+#             */
/*   Updated: 2025/06/24 18:35:38 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int *global_quote(void)
{
	static int quote = 0;
	return (&quote);
}

char	*get_token(char **str)
{
	int		*quote;
	char 	*s;
	int		i;
	
	quote = global_quote();
	s = *str;
	i = 0;
	while (s[i] && !(white_space(s[i]) && !*quote)) // means not seperator
	{
		if (s[i] == '\'' || s[i] == '\"')
			*quote = s[i];
		if (is_symbole(s[++i]) && !*quote)
		{
			if(is_symbole(s[i]))
				break;
			break;
		}
		if (s[++i] == *quote)
		{
			*quote = 0;
			i++;
		}
	}
	*str = (s + i);
	return (ft_substr(0, i, s));
}

t_token *tokenizer(char *str)
{
	t_token	*head;
	char	*token;

	head = NULL;
	while (*str)
	{
		while (white_space(*str))
			str++;
		token = get_token(&str);
		token_add_back(&head, token, get_type(token));
	}
	return (head);
}

int main()
{
	char str[] = " ee \"eho hel\"    > |   \" > hel \"\' w \'";
	t_token *token = tokenizer(str);
	// t_token *tmp;
	
	while (token)
	{
		printf("[str -> %s			| type -> %d]\n", token->str, token->type);
		token= token->next;
	}
}