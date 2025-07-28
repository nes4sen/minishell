/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:16:13 by nosahimi          #+#    #+#             */
/*   Updated: 2025/07/28 18:05:31 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// in the fucntion bellow , i dont check if !var cuz i cant acces to this function only f the var is true
char *find_env_var(t_env *env, char *var)
{
	while (env)
	{
		if (!ft_strcmp(var, env->name))
			return (env->value);
		env = env->next;
	}
	return (ft_substr(0 , 1, ""));
}

char is_valid_env_var_name(char c)
{
	if (!(c >= 'a' && c <= 'z') && !(c >= 'A' && c <= 'Z')
		&& c != '_')
		return (0);
	return (1);
}

char *extract_var_name(char *str)
{
	int	i;

	i = 1;
	if (!is_valid_env_var_name(str[i])
		|| (str[i] >= '0' && str[i] <= '9'))
		return (NULL);
	while (str[i])
	{
		if (!is_valid_env_var_name(str[i]))
			break;
		i++;
	}
	return (ft_substr(1 , i, str));
}

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
int  str_no_quote_len(char *str)
{
	int		len;
	char	quote;

	len = 0;
	quote = 0;
	while (*str)
	{
		if (!quote && is_quote(*str))
			quote = *str;
		else if (*str == quote)
			quote = 0;
		else
			len++;
		str++;
	}
	return len;
}

void	remove_quote(t_token *token)
{
	char	*s;
	char	*tmp;
	int		i;
	int		quote;
	
	s = token->str;
	tmp = malloc(str_no_quote_len(s) + 1);
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