/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ztest.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:25:28 by nosahimi          #+#    #+#             */
/*   Updated: 2025/07/27 17:23:54 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int  str_no_quote_len(char *str)
{
	int		len;
	char	quote;

	while (*str)
	{
		if (!quote && (*str == '"' || *str == '\''))
			quote = *str;
		else if (*str == quote)
			quote = 0;
		else
			len++;
		str++;
	}
	return len;
}

int main()
{
	// hl"'o'"w
	char *str = "hl\"\'o\'\"w";
	int res = str_no_quote_len(str);
	printf("[%d]\n", res);
	
	
}