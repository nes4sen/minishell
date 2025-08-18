/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 10:22:45 by nosahimi          #+#    #+#             */
/*   Updated: 2025/08/18 13:18:21 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_arg(char **arg)
{
	int i;

	i = 0;
	while (arg && arg[i])
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
	int len = 0;
	tmp = cmd;
	while (tmp)
	{
		printf("\nCommand:\n");
		print_arg(tmp->arg);
		printf("\nrediractions:\n");
		print_rdr(tmp->rdr);
		tmp = tmp->next;
		len++;
	}
	printf("->>>%d\n",len);
}

void get_rdr(t_rdr **head,t_shell *s, t_token *token, unsigned int type)
{
	char *file_name;
	
	file_name = NULL;
	if (token->next && token->next->type == DLMTR)
		file_name = prepare_to_heredoc(token->next->str, s);
	else if (token->next &&  token->next->type == file)
	{
		if (token->next->subtoken)
			file_name = token->next->subtoken->str;
		else
			file_name = token->next->str;
	}
	if (type >= 2 && type <= 5 && file_name)
		add_back_rdr(head, file_name, type);
}

void build_cmd(t_shell *shell)
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
			get_rdr(&rdr,shell, token, token->type);
			get_args(args, token, &arg_i);
			token = token->next;
		}
		add_back_cmd(&(shell->cmd), args, rdr); // check if i should pass * or **
		if (token)
			token = token->next;
	}
	// print_all_cmd(shell->cmd);
}
// cpu cash l3 
// [<] [<] [ <<] [> ] [|]  [<<] [<] [ <<] [> ]
// [cmd]  | [cmd]