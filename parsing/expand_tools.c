/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:16:13 by nosahimi          #+#    #+#             */
/*   Updated: 2025/08/21 17:11:25 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// in the fucntion bellow ,
// i dont check if !var cuz i cant 
//acces to this function only f the var is true char
// check this cuz ichange it
char	*find_env_var(t_shell *shell, char *var)
{
	t_env	*env;

	if (g_sigint)
	{
		shell->exit_s = 130;
		g_sigint = 0;
	}
	env = shell->env;
	if (!ft_strcmp(var, "?"))
		return (ft_itoa(shell->exit_s));
	while (env)
	{
		if (!ft_strcmp(var, env->name))
		{
			if (env->value)
				return (env->value);
			else
				break ;
		}
		env = env->next;
	}
	return (ft_substr(0, 1, ""));
}

char	*extract_var_name(char *str)
{
	int	i;

	i = 1;
	if (str[i] == '?')
		return (ft_substr(1, 2, str));
	if (!is_valid_env_var_name(str[i])
		|| (str[i] >= '0' && str[i] <= '9'))
		return (NULL);
	while (str[i])
	{
		if (!is_valid_env_var_name(str[i]))
			break ;
		i++;
	}
	return (ft_substr(1, i, str));
}

int	is_expandable(char *str)
{
	int	quote;

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

int	str_no_quote_len(char *str)
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
	return (len);
}

char	*remove_quote(char *str)
{
	char	*tmp;
	int		i;
	int		quote;

	tmp = mm_alloc(str_no_quote_len(str) + 1);
	i = 0;
	quote = 0;
	while (*str)
	{
		if (!quote && is_quote(*str))
			quote = *str;
		else if (quote == *str)
			quote = 0;
		else
			tmp[i++] = *str;
		str++;
	}
	tmp[i] = '\0';
	return (tmp);
}
