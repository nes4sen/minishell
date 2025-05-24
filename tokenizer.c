/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 10:42:31 by nosahimi          #+#    #+#             */
/*   Updated: 2025/05/24 12:28:45 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	*creat_node(size_t size, void *content)
{
	void	*node;

	node = malloc(size);
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
		while(str[i] == ' ' || (str[i] >= 9 && str[i] <= 13) && !quote)
			i++;
		// token = malloc(sizeof(t_token));
		// 	if ()
		add_back(&node, )
	}
	
	
}
