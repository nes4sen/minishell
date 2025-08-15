/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 12:10:00 by nosahimi          #+#    #+#             */
/*   Updated: 2025/08/14 12:14:37 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void	print_subtokens(t_token *subtokens)
{
	t_token *subtoken = subtokens;
	int i = 0;
	if (!subtoken)
		return;
	while (subtoken)
	{
		printf("    Subtoken %d: [%s], Type: %d\n", i++, subtoken->str, subtoken->type);
		subtoken = subtoken->next;
	}
}

void	print_tokens(t_token *token)
{
	t_token *tokens = token; 

	int i = 0;
	if (!tokens)
		return;
	printf("--- Tokens ---\n");
	while (tokens)
	{
		printf("Token %d: [%s], Type: %d\n", i++, tokens->str, tokens->type);
		if (tokens->subtoken)
		{
			print_subtokens(tokens->subtoken);
		}
		tokens = tokens->next;
	}
	printf("--------------\n");
}

void	print_extokens(t_extoken *extoken)
{
	t_extoken *extokens = extoken;
	int i = 0;
	if (!extokens)
		return;
	printf("--- Extokens ---\n");
	while (extokens)
	{
		printf("Extoken %d: [%s], Stat: %d\n", i++, extokens->str, extokens->stat);
		extokens = extokens->next;
	}
	printf("----------------\n");
}

void	print_cmd_struct(t_cmd *cmds)
{
	t_cmd *cmd = cmds;
	int		i;
	int		j;
	t_rdr	*rdr_tmp;

	i = 0;
	if (!cmd)
		return;
	while (cmd)
	{
		printf("---- Command %d ----\n", i + 1);
		printf("Args: ");
		j = 0;
		if (cmd->arg)
		{
			while (cmd->arg[j])
			{
				printf("[%s] ", cmd->arg[j]);
				j++;
			}
		}
		printf("\n");
		printf("Heredoc: %s\n", cmd->heredox ? cmd->heredox : "(null)");
		rdr_tmp = cmd->rdr;
		j = 0;
		while (rdr_tmp)
		{
			printf("  Redirection %d:\n", j + 1);
			printf("    File: %s\n", rdr_tmp->file);
			printf("    Type: %d\n", rdr_tmp->type);
			rdr_tmp = rdr_tmp->next;
			j++;
		}
		cmd = cmd->next;
		i++;
	}
}
