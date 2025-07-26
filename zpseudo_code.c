/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zpseudo_code.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 12:03:48 by nosahimi          #+#    #+#             */
/*   Updated: 2025/07/26 12:31:51 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
world$HOMe$var$$

if (str[i] == '$')
{
	left_str = ft_substr(start , i - 1, str) = "world";
	var_name = $HOMe
	var_value = "";
	left_str = join(left_str, var_value);
}

char *join_next_str(char *old, char *next)
{

	if (!old)
		return (malloc(next));
	else 
		char p = sizeof(old) + sizeof(new);
	old = old + new;
	return (old)	

}

char *left_str(char *str, int i)
{
	old = NULL;
	start  = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			left_str = ft_substr(start, i - 1);
			var_name = exract_env_var(str);
			if (var_name)  //means if it valid
			{
				var_value = find_env_value();
			}
			
		}
		old = join(old, left);
	}
}




*/