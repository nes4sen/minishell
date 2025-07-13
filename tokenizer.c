/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:53:10 by nosahimi          #+#    #+#             */
/*   Updated: 2025/07/13 19:02:00 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int		*quote_stat()
{
	static int quote = 0;
	return (&quote);
}

int	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0); 
}
int is_seperator(char c)
{
	if (!is_quote(c) && is_symbole(c) && is)
		return (1);
	return (0);
}
char	*get_token(char **str,int *stat)
{
	int		quote;
	char 	*s;
	int		i;
	int 	start;

	start = 0;
	quote  = 0;
	s = *str;
	i = 0;
	if (!is_quote(s[i]) )
	{
		while (s[i] && !is_quote(s[i]))
			i++;
	}
	else if (is_quote(s[i]))
	{
		*stat = assigne_stat(s[i]);
		if (!quote && is_quote(s[i]))
			quote = s[i++];
		s++;
		while (s[i] && s[i] != quote)
			i++;
	}
	*str = (s + i);
	return (ft_substr(start, i, s));
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
		if (white_space(*str))
		{
			token_add_back(&head, " ", SEPR, stat);
			while (white_space(*str))
				str++;
		}
		if (is_symbole(*str))
			token = get_token_symbole(&str);
		else if (!*str)
			return (head);
		else
			token = get_token(&str, &stat);
		token_add_back(&head, token, 0, stat);
	}
	get_type(head);
	/*----------------------------------------------------------------*/
	printf("\033[1m\n\n----TOKENIZER----\n\n\033[0m\n");
	t_token *tmp = head;
	while (tmp)
	{
		printf("token->str	:[%s]\ntype->type	:[%u]  token->state : [%d]\n",tmp->str, tmp->type, tmp->stat);
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