/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 10:42:31 by nosahimi          #+#    #+#             */
/*   Updated: 2025/06/03 12:01:05 by nosahimi         ###   ########.fr       */
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
int	ft_strlen(char *str)
{
	int i;
	
	if(!str)
		return (0);
	i = 0;
	while(str[i])
		i++;
	return (i);
}
char ft_strjoin(char *s1, char *s2)
{
	int len1;
	int len2;
	char *p;
	int i;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	p = malloc(len1+ len2 + 1);
	if (!p)
		return (NULL);
	i = 0;
	while(i < len1)
	{
		p[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < len2)
	{
		p[len1 + i] = s2[i];
		i++;
	}
	p[len1 + len2] = '\0';
	return (p);
}
char	*get_expand(char *str)
{
	int		i;
	int		j;
	char	*s1;
	char 	*s2;
	
	i = 0;
	j = 0;
	while (str[i])
	{
		
	}
}

char *get_token(char *str, int *quote)
{
	int i;
	
	i = 0;
	while(str[i])
	{
		if (is_symbole(str[i]))
		{
			if (is_symbole(str[i++]))
				break;
			break;
		}
		if (str[i] == '$')
			return (get_expand(str));
		i++;
	}
	return(ft_substr(0, i, str));
}
t_token *tokenizer(char *str)
{
	t_token *token;
	int		quote;


	quote = 0;

	// str = echo hello"echo" 
	while (*str)
	{
		if (*str == '\"' || *str == '\'')
			quote = *str;
		while(is_space(*str) && !quote)
			str++;
		token->str = get_token(str, &quote)
	}
	
	
}

