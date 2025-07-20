/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 10:53:41 by nosahimi          #+#    #+#             */
/*   Updated: 2025/07/20 17:22:11 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//this function creat the extoken list
void get_exhead(t_extoken **exhead, t_token *token)
{
	char *str;
	
	str = token->str;
	while (*str)
	{
		if (is_quote(*str))
			get_quoted_extoken(exhead, str);
		else
			get_extoken(exhead, str);
	}

}
//this function creat a linked list called t_extoken  , this list seperate the t_token token with quotes and remove them and expand the env_vars,
void expand_token(t_token *token)
{
	t_extoken *exhead;
	
	get_exhead(&exhead, token);
	//1_ 
	
	
}
void	expand_env_vars(t_token *token)
{
	while (token)
	{
		if (is_expandable(token)) 
			expand_token(token);
		else if (is_quoted_str(token->str)) 
			remove_quote(token);
		token = token->next;
	}
}


t_cmd *parsing(char *line)
{
	t_token	*token;

	token = tokenizer(line);
	syntax_error(token);
	expand_env_vars(token);
	//herdoc
	//expand and quote removing
	return (build_cmd_list(token));
}