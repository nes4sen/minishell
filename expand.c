/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:46:42 by nosahimi          #+#    #+#             */
/*   Updated: 2025/07/29 19:43:35 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void get_expand(t_extoken *exhead, t_env *env)
{
	char *str;
	char *result;
	int i;
	char *var_name;
	char *var_value;
	
	str = exhead->str;
	result = "";
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			var_name = extract_var_name(&str[i]);
			if (var_name)
			{
				var_value = find_env_var(env, var_name);
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
			if (white_space(str[i]) && exhead->stat == NO_QUOTE)
			{
				token_add_back(&subhead, subtoken, 0);	
				subtoken = "";
				while (white_space(str[i]) && exhead->stat == NO_QUOTE)
					i++;
			}
			else
				subtoken = char_join(subtoken, str[i++], 0);
		}
		exhead = exhead->next;
	}
	token->subtoken = subhead;
}
void print_exlist(t_extoken *token)
{
	while (token)
	{
		printf("x[%s] [%d]x\n", token->str, token->stat);
		token = token->next;
	}
	
}
void print_subtoken(t_token *token)
{
	t_token *sub;
	while (token)
	{
		if (!token->subtoken)
		{
			printf("{%s}\n",token->str);	
		}
		else
		{
			sub = token->subtoken;	
			while(sub)
			{
				printf("sub{%s  %d}\n", sub->str, sub->type);
				sub = sub->next;
			}
		}
		token = token->next;
	}
}

void	prepare_for_expand(t_token *token,t_extoken **exhead, t_env *env)
{
	t_extoken *tmp;
	// t_extoken *print;

	build_exlist(exhead, token);
	// print = *exhead; 
	tmp = *exhead;
	while (tmp)
	{
		if (tmp->stat != SINGLE_QUOTE)
			get_expand(tmp, env);
		tmp = tmp->next;
	}
	tmp = *exhead;
	fill_subtoken(token, tmp);
// print_subtoken(token);
// print_exlist(print);	
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

// toto$HOME
