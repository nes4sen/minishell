/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:46:42 by nosahimi          #+#    #+#             */
/*   Updated: 2025/07/25 11:58:13 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_expandable(char *str)
{
	int quote;

	quote = 0;
	while (*str)
	{
		if (!quote && is_quote(*str))
			quote = *str;
		else if (quote == *str)
			quote = 0;
		if (quote != '\'' && *str == '$')
			return (1);
		str++;
	}
	return (0);
}

void	remove_quote(t_token *token)
{
	char	*s;
	char	*tmp;
	int		i;
	int		quote;
	
	s = token->str;
	tmp = malloc(str_no_quote_len(s) + 1);
	if (tmp)
	{
		//free
	}
	i = 0;
	quote = 0;
	while(*s)
	{
		if (!quote && is_quote(*s))
			quote = *s;
		else if (quote == *s)
			quote = 0;	
		else
			tmp[i++] = *s;
		s++;
	}
	tmp[i] = '\0';
	free(token->str);
	token->str = tmp;
 } 


 void	get_expand(t_extoken *exhead, t_env *env)
{
	int		i;
	char	*str;
	char	*var_name;
	char	*var_value;
	char	*left_str;
	int		start;
	
	str = exhead->str;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			var_name = extract_var_name(&str[i], &i);
			if (var_name)
			{
				start = i;
				left_str = ft_substr(start, i - 1, str);
				i+= ft_strlen(var_name);
				var_value = find_env_var(env, var_name);
				left_str = ft_join(left_str, var_value);
			}
		}
		else
			i++;
	}
	exhead->str = left_str;
}

void	prepare_for_expand(t_token *token, t_env *env)
{
	t_extoken *exhead;

	build_exlist(&exhead, token);
	while (exhead)
	{
		get_expand(exhead, env);
		exhead = exhead->next;
	}
}

void	expand_env_vars(t_token *token, t_env *env)
{
	while (token)
	{
		if (is_expandable(token)) 
			prepare_for_expand(token, env);
		else if (is_quoted_str(token->str)) 
			remove_quote(token);
		token = token->next;
	}
}

