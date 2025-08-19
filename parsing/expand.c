/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:46:42 by nosahimi          #+#    #+#             */
/*   Updated: 2025/08/19 13:36:12 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void get_expand(t_shell *shell, t_extoken *exhead)
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
				var_value = find_env_var(shell , var_name);
				result = str_join(result, var_value);
				i += ft_strlen(var_name) + 1;
			}
			else
				result = char_join(result, '$', &i);
		}
		else
			result =  char_join(result, str[i], &i);
	}
	exhead->str = result;
}

void	get_substr(char **substr, t_token **subhead, int type)
{
	token_add_back(subhead, *substr, type);
	*substr = "";
}

void	fill_subtoken(t_token *token, t_extoken *extoken)
{
	t_token *subhead;
	char	*substr;
	char	*str;

	substr = "";
	subhead = NULL;
	while (extoken)
	{
		str = extoken->str;
		if (str && !*str)
				get_substr(&substr, &subhead, token->type);
		while (*str)
		{
			while (*str && white_space(*str) && extoken->stat == NO_QUOTE)
				str++;
			while (*str && (!white_space(*str) || extoken->stat != NO_QUOTE))
				substr = char_join(substr, *str++, 0);
			if (*substr)
				get_substr(&substr, &subhead, token->type);
		}
		extoken = extoken->next;
	}
	token->subtoken = subhead;
}

void	prepare_for_expand(t_shell *shell)
{
	t_extoken *exhead;
	t_extoken *tmp;

	exhead = NULL;
	build_exlist(&exhead, shell->tokens);
	tmp = exhead;
	while (tmp)
	{
		if (tmp->stat != SINGLE_QUOTE)
			get_expand(shell, tmp);
		tmp = tmp->next;
	}
	tmp = exhead;
	fill_subtoken(shell->tokens, tmp);
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

void	expand_env_vars(t_shell *shell)
{
	t_token *save_point;

	save_point = shell->tokens;
	while (shell->tokens)
	{
		if (shell->tokens->type != DLMTR)
		{
			if (is_expandable(shell->tokens->str)) 
				prepare_for_expand(shell);
			else if (is_quoted_str(shell->tokens->str)) 
				shell->tokens->str = remove_quote(shell->tokens->str);
		}
		shell->tokens = shell->tokens->next;
	}
	shell->tokens = save_point;
}
