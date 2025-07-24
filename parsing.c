/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 10:53:41 by nosahimi          #+#    #+#             */
/*   Updated: 2025/07/24 13:27:31 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//this function creat the extoken list

void get_quoted_extoken(t_extoken **exhead, char **s)
{
	//this function remove target the quoted sring , remove it quotes and flag the token

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
	/*
		this function check if the captured var is in the env
	*/
	while (!var && env)
	{
		if (!ft_strcmp(var, env->name))
			return (env->value);
		env = env->next;
	}
	return (ft_substr(0 , 1, ""));
}

char is_valid_env_var_name(char c)
{
	if (!(c >= 'a' && c <= 'z')
		&& !(c >= 'A' && c <= 'Z')
		&& c != '_' && !c)
		return (0);
	return (1);
}

char *extract_var_name(char *str, int *index)
{
	int		i;
/*
this function capture the name of the var

*/	
	i = 1;
	while (str[i])
	{
		if (!is_valid_env_var_name(str[i]))
			break;
		i++;
	}
	if (i == 1) // means if the first char is invalid , that means no expand of $ should happen
		return (NULL);
	*index += i;	
	return (ft_substr(1 , i, str + 1));
}

/*
this function scan the extoken , searching for a valid $ for expand, 
calling the function find_env_var() that return the value of the env var found
-- the function extract_var_name() return the name of the var after the $
-- if invalid (ex. $1 $+ ..) it return NULL


*/
// void	scan_for_expand(t_extoken *exhead, t_env *env)
// {
// 	// this function expand ...
// 	char	*str;
// 	int		final_len;
// 	char 	*var;

// 	final_len = 0;
// 	str = exhead->str;
// 	while (*str)
// 	{
// 		if (*str = '$' && exhead->stat != SINGLE_QUOTE)
// 		{
// 			var = extract_var_name(&str);
// 			if (var)
// 			{
// 				var = find_env_var(env, extract_var_name(&str));
// 				final_len += ft_strlen(var);
// 				str =  (str + final_len);	
// 			}
			
// 		}
// 		final_len++;
// 	}
// 	fill_expanded_token(final_len, exhead, env);
// }

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str1;
	char	*str2;
	char	*p;
	size_t	first_len;
	size_t	sec_len;

	if (!s1 || !s2)
		return (NULL);
	str1 = (char *)s1;
	str2 = (char *)s2;
	first_len = ft_strlen(s1);
	sec_len = ft_strlen(s2);
	p = malloc(first_len + sec_len + 1);
	if (!p)
		return (NULL);
	ft_strcpy(p, str1);
	ft_strcpy(p + first_len, str2);
	p[first_len + sec_len] = '\0';
	return (p);
}

void	get_expand(t_extoken *exhead, t_env *env)
{
	int		i;
	char	*str;
	char 	*join_str;
	
	str = exhead->str;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			
		i++;
	}
}

/*
	echo"hello$vary$var"
	[echo] ["hello$vary$var"]
*/


//this function create a linked list called t_extoken  , this list seperate the t_token token with quotes and remove them and expand the env_vars,
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

/*
1_	loop into the tokenizer and check if the token have a valid $ for expand, if not check if the token is quoted

	1.a_	is_expandable() -> expand_token()
			
			the function expand_token()  create a linked list called exlist with the function build_exlist(), its create tokens from the main token,
			the extoken separated by quotes, and they get a flaged and quote removed.
			
			next, i loop through the exlist and expand the vars.
		
		summary:
		1. create exlist
		2. exlist tokens separeted with quotes
		3. remove quotes and flag the extoken
		4. expand the vars


*/