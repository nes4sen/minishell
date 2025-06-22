/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_tokinezer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:53:10 by nosahimi          #+#    #+#             */
/*   Updated: 2025/06/22 20:27:43 by nosahimi         ###   ########.fr       */
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

int white_space(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (c);
	return (0);
}

int	is_symbole(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (c);
	return (0);
}
char	*get_token(char **str)
{
	char 	*s;
	int		i;
	int		quote;
	
	i = 0;
	s = *str;
	// if (s[i] == quote) //to skip the quote that passed from the func
	// 	i++;
	while (s[i])
	{
		if (is_symbole(s[i++]))
		{
			if(is_symbole(s[i++]))
				break;
			break;
		}
		i++;
	}
	*str = (s + i);
	return (ft_substr(0, i, s));
}

int ft_strcmp(char *s1, char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
int	get_type(char *str)
{
	if (!ft_strcmp(str, "|"))
		retrun (1);
	if (!ft_strcmp(str, "<"))
		return (2);
	if (!ft_strcmp(str, ">"))
		retrun (3);
	if (!ft_strcmp(str, "<<"))
		return (4);
	if (!ft_strcmp(str, ">>"))
		return (5);
	return (0);
}
t_token *tokenizer(char *str)
{
	t_token	*head;
	int		quote;
	char	token;
	int		i;

	i = 0;
	head = NULL;
	quote = 0;
	while (str[i])
	{
		if(str[i] == '\'' || str[i] == '\"')
			quote = str[i];
		while(white_space(str[i]))
			i++;
		token = get_token(&str);
		token_add_back(&head, token, get_type(token));
		i++;
		if (str[i] == quote)
			quote = 0;
	}
}
