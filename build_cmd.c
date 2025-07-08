/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 10:22:45 by nosahimi          #+#    #+#             */
/*   Updated: 2025/07/08 19:41:19 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void print_arg(char **arg)
{
	int i;
	i = 0;
	while (arg[i])
	{
		printf("arg		: [%s]\n",arg[i]);
		i++;
	}
}
void print_rdr(t_rdr *rdr)
{
	
	while (rdr)
	{
		printf("rdr_str -> [%s]\nrdr_type-> [%d]\n",rdr->file , rdr->type);
		rdr = rdr->next;
	}	

}











t_cmd *create_node_cmd(char **cmd, t_rdr *rdr)
{
	t_cmd *ptr;
	
	ptr = malloc(sizeof(t_cmd));
	if (!ptr)
	{
		//free
	}
	ptr->arg = cmd;
	ptr->rdr = rdr;
	ptr->next = NULL;
	return (ptr);
}

void	add_back_cmd(t_cmd **head, char **cmd, t_rdr *rdr)
{
	t_cmd *tmp;
	
	if (!*head)
	{
		*head = create_node_cmd(cmd, rdr);
	}
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = create_node_cmd(cmd, rdr);
	}
}

t_rdr *get_rdr(t_token *tokens)
{
	t_rdr *head;
	
	head = NULL;
	while (tokens && tokens->type != 1)
	{
		if (tokens->type > 2 )
		{
			add_back_rdr(&head, tokens->str, tokens->type);
			// tokens->next->type = tokens->type;
			// if (tokens->next)
            // 	tokens->next->type = tokens->type;
		}
		tokens = tokens->next;
	}
	return (head);
}
int	count_words(t_token *tokens)
{
	int i;

	i = 0;
	if (!tokens)
		return (0);
	while (tokens && tokens->type != 1)
	{
		if (!tokens->type)
			i++;
		tokens = tokens->next;
	}
	return (i);
}
char **get_cmd_arg(t_token *tokens)
{
	int		b_len;
	char 	**b_alloc;
	int		i;

	b_len =  count_words(tokens);
	b_alloc = malloc(sizeof(char *) * b_len + 1);
	i = 0;
	if (!b_alloc)
	{
		//free
	}
	while(i < b_len)
	{
		while (tokens)
		{
			if(!tokens->type)
			{
				b_alloc[i] = malloc(ft_strlen(tokens->str) + 1);
				if (!b_alloc)
				{
					//free
				}
				ft_strcpy(b_alloc[i], tokens->str);
				i++;
			}
			tokens = tokens->next;
		}
	}
	b_alloc[i] = NULL;
	return (b_alloc);
}


void	into_next_cmd(t_token **start)
{
	while(*start && (*start)->type != 1)
		*start = (*start)->next;
	if (*start && (*start)->type == 1)
		*start = (*start)->next;
}


t_cmd *build_cmd_list(t_token *tokens)
{
	t_cmd	*cmd;
	char	**arg;
	t_rdr	*rdr;

	cmd = NULL;
	while(tokens)
	{
		rdr = get_rdr(tokens);
		arg = get_cmd_arg(tokens);
		add_back_cmd(&cmd, arg,rdr);
		into_next_cmd(&tokens);
	}
	printf("\n\033[1m----COMMAND----\033[0m\n");
	t_cmd 	*tmp = cmd;
	while (tmp)
	{
		print_arg(tmp->arg);
		printf("\n		-----------------		\n");
		print_rdr(tmp->rdr);
		printf("\n		NEXT_COMMAND		\n");
		tmp = tmp->next;
	}
	return cmd;
}



