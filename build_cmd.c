/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 10:22:45 by nosahimi          #+#    #+#             */
/*   Updated: 2025/07/31 11:38:46 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_arg(char **arg)
{
	int i;

	i = 0;
	while (arg[i])
	{
		printf("	Arg[%d]: %s\n", i, arg[i]);
		i++;
	}
}

void print_rdr(t_rdr *rdr)
{
	t_rdr *tmp;

	tmp = rdr;
	while (tmp)
	{
		printf("	Rdr file: %s\n	type: %d\n", tmp->file, tmp->type);
		tmp = tmp->next;
	}
}
void print_all_cmd(t_cmd *cmd)
{
	t_cmd *tmp;
	

	tmp = cmd;
	while (tmp)
	{
		printf("\nCommand:\n");
		print_arg(tmp->arg);
		printf("\nrediractions:\n");
		print_rdr(tmp->rdr);
		tmp = tmp->next;
	}
}

void get_rdr(t_rdr **head, t_token *token, unsigned int type)
{
	char *file_name;

	if (type == 2)
	{
		// get_heredoc();
		
	}
	if (token->next &&  token->next->type == file)
		file_name = token->next->str;
	if (type >= 3 && type <= 5)
		add_back_rdr(head, file_name, type, -1);
}

t_cmd	*build_cmd_list(t_token *token)
{
	t_rdr	*rdr;
	t_cmd	*cmd;
	char **args;

	cmd = NULL;
	rdr = NULL;	
	args = space_for_args(token);
	while (token)
	{
		while (token && token->type != 1)
		{
			get_rdr(&rdr, token, token->type);
			get_args(&args, token);
			token = token->next;
		}
		add_back_cmd(&cmd, args, rdr);
		if (token)
			token = token->next;
	}
	print_all_cmd(cmd);
	return (cmd);
}
