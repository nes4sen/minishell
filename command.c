/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 10:22:45 by nosahimi          #+#    #+#             */
/*   Updated: 2025/07/02 12:49:17 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void print_arg(char **arg)
{
	int i;
	i = 0;
	while (arg[i])
	{
		printf("arg	-> %s	\n",arg[i]);
		i++;
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
			add_back_rdr(&head, tokens->str, tokens->type);
// printf("[tokens->str = %s]\n",tokens->str);
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
	// printf("b_len %d\n", i);
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
	while(*start && (*start)->type == 1)
		*start = (*start)->next;	
}
t_cmd *build_cmd_list(t_token *tokens)
{
	t_cmd	*cmd;
	char	**arg;
	t_token *ptr;
	t_rdr	*rdr;
	
	cmd = NULL;
	ptr = tokens;
	while(ptr)
	{
		rdr = get_rdr(tokens);
		arg = get_cmd_arg(tokens);
		add_back_cmd(&cmd, arg,rdr);
		into_next_cmd(&tokens);
		ptr = ptr->next;
	}
	
	return cmd;
}

void print_rdr(t_rdr *rdr)
{
	
	while (rdr)
	{
		printf("rdr_str -> %s		| rdr_type-> %d\n",rdr->file , rdr->type);
		rdr = rdr->next;
	}	

}

int main()
{
	char str[] = " one  >\"$var\">>   |  <<  \" > three \"\' for \'";
	t_token *token = tokenizer(str);
	// t_token *tmp;
	t_cmd *cmd = build_cmd_list(token);
	while (cmd)
	{
		print_arg(cmd->arg);
		print_rdr(cmd->rdr);
		cmd = cmd->next;
	}
}


/*

t_cmd *build_cmd_list(t_token *tokens)
{
	t_cmd *cmd = NULL;
	t_token *ptr = tokens;

	while (ptr)
	{
		t_rdr *rdr = get_rdr(&ptr);      // update ptr internally
		char **arg = get_cmd_arg(&ptr);  // also update ptr inside
		add_back_cmd(&cmd, arg, rdr);
	}
	return cmd;
}

*/
