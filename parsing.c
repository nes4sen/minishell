/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 10:53:41 by nosahimi          #+#    #+#             */
/*   Updated: 2025/07/20 20:15:38 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//this function creat the extoken list

void get_quoted_extoken(t_extoken **exhead, char **s)
{
	char	*token;
	char	*str;
	int		quote;
	int		i;
	int		stat;
	
	i = 0;
	str = *s;
	quote = str[i++];
	while (str[i] && str[i] != quote)
		i++;
	token = ft_substr(1 , i, str);
	if (quote == '\'')
		stat = SINGLE_QUOTE;
	else if (str[i] == '"')
		stat = DOUBLE_QUOTE;
	add_back_extoken(exhead, token, stat);
	*s = *s + i;
}

void get_no_quoted_extoken(t_extoken **exhead, char **s)
{
	int		i;
	char	*token;
	char	*str;
	
	i = 0;
	str = *s;
	while (str[i] && !is_quote(s[i]))
		i++;
	token = ft_substr(1 , i, str);
	add_back_extoken(exhead, token, 0);
	*s += i;
}

void get_exhead(t_extoken **exhead, t_token *token)
{
	char *str;
	
	str = token->str;
	while (*str)
	{
		if (is_quote(*str))
			get_quoted_extoken(exhead, str);
		else
			get_extoken(exhead, str);
	}
}
void	get_expand(t_extoken *exhead)
{
	// this function expand ...
	while (exhead)
	{
			
		exhead = exhead->next; 
	}	
}

//this function creat a linked list called t_extoken  , this list seperate the t_token token with quotes and remove them and expand the env_vars,
void	expand_token(t_token *token)
{
	t_extoken *exhead;

	// this function loop throgh the string and create a list of tokens
	//, remove the quotes, and flag the tokens
	get_exhead(&exhead, token);
	get_expand(exhead);
	
}

void	expand_env_vars(t_token *token)
{
	while (token)
	{
		if (is_expandable(token)) 
			expand_token(token);
		else if (is_quoted_str(token->str)) 
			remove_quote(token);
		token = token->next;
	}
}

t_cmd *parsing(char *line)
{
	t_token	*token;

	token = tokenizer(line);
	syntax_error(token);
	expand_env_vars(token);
	//herdoc
	//expand and quote removing
	return (build_cmd_list(token));
}