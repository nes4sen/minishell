/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-laf <aait-laf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:16:13 by nosahimi          #+#    #+#             */
/*   Updated: 2025/08/15 23:36:02 by aait-laf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static size_t	int_len(int nb)
{
	size_t	len;
	long	n;

	n = (long)nb;
	len = 0;
	if (nb <= 0)
		len++;
	if (n < 0)
		n *= -1;
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int nb)
{
	size_t	len;
	char	*p;
	size_t	i;
	long	n;

	n = (long)nb;
	len = int_len(n);
	p = malloc(sizeof(char) * len + 1);
	if (!p)
		return (NULL);
	p[len] = '\0';
	i = 0;
	if (n < 0)
	{
		p[0] = '-';
		n *= -1;
		i = 1;
	}
	while (len-- > i)
	{
		p[len] = (n % 10) + 48;
		n /= 10;
	}
	return (p);
}

// in the fucntion bellow , i dont check if !var cuz i cant acces to this function only f the var is true
char *find_env_var(t_shell *shell, char *var)
{
	t_env *env;

	env = shell->env;
	if (!ft_strcmp(var, "?"))
		return (ft_itoa(shell->exit_s));
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
	if (str[i] == '?')
		return(ft_substr(1, 2, str));
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

char	*remove_quote(char *str)
{
	char	*tmp;
	int		i;
	int		quote;
	
	tmp = mm_alloc(str_no_quote_len(str) + 1);
	i = 0;
	quote = 0;
	while(*str)
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