/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 10:53:41 by nosahimi          #+#    #+#             */
/*   Updated: 2025/08/19 12:01:08 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_type_name(t_type type)
{
	if (type == CMD)
		return ("CMD");
	else if (type == PIPE)
		return ("PIPE");
	else if (type == HEREDOC)
		return ("HEREDOC");
	else if (type == RDRIN)
		return ("RDRIN");
	else if (type == RDROUT)
		return ("RDROUT");
	else if (type == APPND)
		return ("APPND");
	else if (type == file)
		return ("FILE");
	else if (type == DLMTR)
		return ("DLMTR");
	return ("UNKNOWN");
}

void	print_tokenizer(t_shell *shell)
{
	t_token	*current;
	int		i;

	if (!shell || !shell->tokens)
	{
		printf("No tokens to display\n");
		return ;
	}
	current = shell->tokens;
	i = 0;
	printf("\n=== TOKENIZER DEBUG ===\n");
	while (current)
	{
		printf("Token [%d]: ", i);
		if (current->str)
			printf("'%s' ", current->str);
		else
			printf("(NULL) ");
		printf("Type: %s\n", get_type_name(current->type));
		current = current->next;
		i++;
	}
	printf("=== END TOKENIZER ===\n\n");
}


int	parser(t_shell *shell)
{
	int		syntax_exit;

	tokenizer(shell);
	// print_tokenizer(shell);
	syntax_exit = syntax_error(shell);
	if (!syntax_exit)
	{
		expand_env_vars(shell);
		if (build_cmd(shell))
			return (130);
	}
	else
	{
		shell->exit_s = 2;
		return (shell->exit_s);
	}
	return (0);
}
