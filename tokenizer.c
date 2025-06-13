/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 10:42:31 by nosahimi          #+#    #+#             */
/*   Updated: 2025/06/08 20:30:07 by nosahimi         ###   ########.fr       */
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
char *ft_strjoin(char *s1, char *s2)
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
	p[len1 + i] = '\0';
	// free(s1);
	//free(s2);
	return (p);
}
char	*get_expand(char *str)
{
	int		i;
	int		j;
	char	*s1;
	char 	*s2;
	char 	*s3;
	
	i = 0;
	j = 0;
	while (str[i] != '$')
		i++;
	s1 = malloc(i + 1);
	if (!s1)
	{
		//free
	}
	while (str[j] != '$')
	{
		s1[j] = str[j];
		j++;
	}
	s1[j] = '\0';
	i = j + 1;
	while (str[i] && str[i] != '\"')
		i++;
	s2 = malloc((i - j) + 1);
	if (!s2)
	{
		//free
	}
	i = j + 1;
	j = 0;
	while(str[i] && str[i] != '\"')
	{
		s2[j] = str[i];
		i++;
		j++;
	}
	s2[j] = '\0';
	s3 = getenv(s2);
	return(ft_strjoin(s1, s3));
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
int	get_type()
{
	
}
t_token *tokenizer(char *str)
{
	t_token *token;
	char	*token_str;
	int		quote;


	quote = 0;
	token = NULL;

	// str = echo hello"echo" 
	while (*str)
	{
		while(is_space(*str) && !quote)
		{
			if (*str == '\"' || *str == '\'')
				quote = *str;
			str++;
		}
		token_str = get_token(str, &quote);
		token_add_back(&token, token_str, 1); // echo hello toto etc"$HOME"
		printf("token %s\n", token->str);
		str++;
	}
	
	
}
int main()
{
	char str[] = " hello world\"$HOME\"hh";
	t_token *tok = tokenizer(str);
}

