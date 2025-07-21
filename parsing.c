/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 10:53:41 by nosahimi          #+#    #+#             */
/*   Updated: 2025/07/21 17:22:40 by nosahimi         ###   ########.fr       */
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

void build_exlist(t_extoken **exhead, t_token *token)
{
	char *str;
	
	str = token->str;
	while (*str)
	{
		if (is_quote(*str))
			get_quoted_extoken(exhead, str);
		else
			get_no_quoted_extoken(exhead, str);
	}
}
char *find_env_var(t_env *env, char *var)
{
	
	while (!var && env)
	{
		if (!ft_strcmp(var, env->name))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char is_valid_env_var_name(char c)
{
	if (!(c >= 'a' && c <= 'z')
		&& !(c >= 'A' && c <= 'Z')
		&& c != '_')
		return (0);
	return (1);
}

char *extract_var_name(char **s)
{
	int		i;
	char	*str;
	
	str = *s;
	i = 1;
	while (str[i])
	{
		if (!is_valid_env_var_name(str[i]))
			break;
		i++;
	}
	if (i == 1) // means if the first char is invalid , that means no expand of $ should happen
		return (NULL);
	*s = (*s + i);
	return (ft_substr(1 , i, str + 1));
}

void	expand_extoken(t_extoken *exhead, t_env *env)
{
	// this function expand ...
	char	*str;
	int		final_len;
	char 	*var;
	
	final_len = 0;
	str = exhead->str;
	while (*str)
	{
		if (*str = '$' && exhead->stat != SINGLE_QUOTE)
		{
			var = find_env_var(env, extract_var_name(&str));
			final_len += ft_strlen(var);
		}
		final_len++;
	}
}

//this function creat a linked list called t_extoken  , this list seperate the t_token token with quotes and remove them and expand the env_vars,
void	expand_token(t_token *token, t_env *env)
{
	t_extoken *exhead;

	// this function loop throgh the string and create a list of tokens
	//, remove the quotes, and flag the tokens
	build_exlist(&exhead, token);
	expand_extoken(exhead, env);
	
}

void	expand_env_vars(t_token *token, t_env *env)
{
	while (token)
	{
		if (is_expandable(token)) 
			expand_token(token, env);
		else if (is_quoted_str(token->str)) 
			remove_quote(token);
		token = token->next;
	}
}

t_cmd *parsing(char *line, t_env *env)
{
	t_token	*token;

	token = tokenizer(line);
	syntax_error(token);
	expand_env_vars(token, env);
	//herdoc
	//expand and quote removing
	return (build_cmd_list(token));
}