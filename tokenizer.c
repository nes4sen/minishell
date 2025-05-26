/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 10:42:31 by nosahimi          #+#    #+#             */
/*   Updated: 2025/05/25 19:06:02 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_node	*creat_node(void *content)
{
	t_node *node;
	
	node = malloc(node);
	if (!node)
	{
		// free
	}
	node->content = content;
	node->next = NULL;
	return (node);
}

void	add_back(t_node **head, void *content)
{
	t_node *tmp;

	tmp = *head;
	if (!*head)
	{
		*head = creat_node(content);
	}
	else
	{
		while(tmp->next)
		{
			tmp = tmp->next;
		}
		tmp = creat_node(content);
	}
}

t_token	*creat_token(char *str, t_type type)
{
	t_token *token;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		//free;
	}
	token->str = str;
	token->type = type;
	return (token);
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
	t_node	*node;
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

