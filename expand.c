/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:46:42 by nosahimi          #+#    #+#             */
/*   Updated: 2025/07/27 17:35:49 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void get_expand(t_extoken *exhead, t_env *env)
{
	char *str;
	char *result;
	int i = 0;
	
	str = exhead->str;
	result = "";
	while (str[i])
	{
		if (str[i] == '$')
		{
			char *var_name = extract_var_name(&str[i]);
			if (var_name)
			{
				char *var_value = find_env_var(env, var_name);
				if (var_value)
					result = str_join(result, var_value);
				i += ft_strlen(var_name) + 1;  // Skip $VAR
			}
			else
				result = char_join(result, '$', &i);
		}
		else
			result =  char_join(result, str[i], &i);
	}
	exhead->str = result;
}
void fill_subtoken(t_token *token,t_extoken *exhead)
{
	char	*str;
	int		i;
	char	*subtoken;;
	t_token *subhead;
	
	subhead = NULL;
	subtoken = "";
	while (exhead)
	{
		i = 0;
		str = exhead->str;
		while (str[i])
		{
			subtoken = char_join(subtoken, str[i], 0);
			if (white_space(str[i]) && exhead->stat == NO_QUOTE)
			{
				token_add_back(&subhead, subtoken, 0);	
				subtoken = "";
			}
			i++;
		}
		exhead = exhead->next;
	}
	token->subtoken = subhead;
}

void	prepare_for_expand(t_token *token,t_extoken **exhead, t_env *env)
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
}


int is_quoted_str(char *str)
{
	while (*str)
	{
		if (is_quote(*str))
			return (1);
		str++;
	}
	return (0);
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

