/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 10:22:45 by nosahimi          #+#    #+#             */
/*   Updated: 2025/08/21 12:38:48 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	get_rdr(t_rdr **head, t_shell *s, t_token *token, unsigned int type)
{
	char	*file_name;

	file_name = NULL;
	if (token->next && token->next->type == DLMTR)
	{
		file_name = prepare_to_heredoc(token->next->str, s);
		if (!file_name)
			return (130);
	}
	else if (token->next && token->next->type == file)
	{
		if (token->next->subtoken)
			file_name = token->next->subtoken->str;
		else
			file_name = token->next->str;
	}
	if (type >= 2 && type <= 5 && file_name)
		add_back_rdr(head, file_name, type);
	return (0);
}

int	build_cmd(t_shell *shell)
{
	t_rdr	*rdr;
	t_token	*token;
	char	**args;
	int		arg_i;

	token = shell->tokens;
	while (token)
	{
		rdr = NULL;
		args = space_for_args(token);
		arg_i = 0;
		while (token && token->type != 1)
		{
			if (get_rdr(&rdr, shell, token, token->type))
				return (130);
			get_args(args, token, &arg_i);
			token = token->next;
		}
		add_back_cmd(&(shell->cmd), args, rdr);
		if (token)
			token = token->next;
	}
	return (0);
}
