/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 10:42:31 by nosahimi          #+#    #+#             */
/*   Updated: 2025/06/01 19:12:47 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *creat_token(char *token, t_type type)
{
	t_token *p;

	p = malloc(sizeof(t_token));
	if (!p)
	{
	 //free
	}
	p->str = token;
	p->type = type;
	p->next = NULL;
	return (p);
}
void token_add_back(t_token **head, char *token, t_type type)
{
	t_token *ptr;

	ptr = *head;
	if (!*head)
	{
		*head = creat_token(token, type);
		
	}
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr = creat_token(token, type);
	}
}

char *ft_substr(int start, int end, char *str)
{
	int 	len;
	char	*s;
	int		i;
	len = (end - start);
	s = malloc(len + 1);
	if (!s)
		return NULL;
	i = 0;
	while (start < end)
	{
		s[i] = str[start];
		i++;
		start++;
	}
	s[i] = '\0';
	return (s);
}
int is_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}
t_token *tokenizer(char *str)
{
	t_token *token;

	int		i;
	int		j;
	int		quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			quote = str[i];
		while(is_spacce(str[i]) && !quote)
			i++;
		j = 0;
		while(!is_space(str[i + j]))
		{
			if ();//$home/fgdfgd!
			j++;
		
		add_back(&node, creat_token(str, ));
		}
	}
	
	
}

