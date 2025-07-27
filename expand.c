/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:46:42 by nosahimi          #+#    #+#             */
/*   Updated: 2025/07/27 11:59:15 by nosahimi         ###   ########.fr       */
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


void get_expand(t_extoken *exhead, t_env *env)
{
	char *str;
	char *result;
	int i = 0;
	
	str = exhead->str;
	result = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$')
		{
			char *var_name = extract_var_name(&str[i]);
			if (var_name)
			{
				char *var_value = find_env_var(env, var_name);
				if (var_value)
					result = ft_join(result, var_value);
				i += ft_strlen(var_name) + 1;  // Skip $VAR
			}
			else
				result = ft_join_char(result, '$', &i);
		}
		else
			result = ft_join_char(result, str[i], &i);
	}
	exhead->str = result;
}
void fill_subtoken(t_token token,t_extoken *exhead)
{
		
}
void	*prepare_for_expand(t_token *token,t_extoken **exhead, t_env *env)
{
	
	t_extoken *tmp;
	
	build_exlist(exhead, token);
	tmp = *exhead;
	while (tmp)
	{
		if (tmp->stat != SINGLE_QUOTE)
			get_expand(tmp, env);
		tmp = tmp->next;
	}
	
	//
}



void	expand_env_vars(t_token *token, t_env *env)
{
	t_extoken *exhead;

	exhead = NULL;
	while (token)
	{
		if (is_expandable(token->str)) 
			prepare_for_expand(token, &exhead, env);
		else if (is_quoted_str(token->str)) 
			remove_quote(token);
		token = token->next;
	}
}

