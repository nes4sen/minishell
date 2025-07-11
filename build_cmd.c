/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 10:22:45 by nosahimi          #+#    #+#             */
/*   Updated: 2025/07/11 11:07:01 by nosahimi         ###   ########.fr       */
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
		printf("rdr_str -> [%s]\nrdr_type-> [%d]\n fd->%d",rdr->file , rdr->type, rdr->fd);
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

void get_rdr(t_rdr **head, char *file_name, unsigned int type)
{
	if (type == 2)
		// get_heredoc();
	if (type >= 3 && type <= 5)
		add_back_rdr(head, file_name, type, -1);
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

char **alloc_arg(t_token *tokens)
{
	int		b_len;
	char 	**b_alloc;
	
	b_len = count_words(tokens);
	b_alloc = malloc(sizeof(char *) * (b_len + 1));
	if (b_alloc)
	{
		//free
	}
	b_alloc[b_len] = NULL;
	return (b_alloc);
}
char *alloc_word(char *str)
{
	char *arg;

	arg = malloc(sizeof(str) + 1);
	if (!arg)
	{
	//free
	}
	ft_strcpy(arg, str);
	return (arg);
}
t_cmd *build_cmd_list(t_token *tokens)
{
	t_cmd	*cmd;
	char	**arg;
	t_rdr	*rdr;
	int 	i;

	cmd = NULL;
	rdr = NULL;
	while(tokens)
	{
		arg = alloc_arg(tokens);
		i = 0;
		while (tokens && tokens->type != 1)
		{
			get_rdr(&rdr, tokens->str, tokens->type);
			if (!tokens->type)
				arg[i++] = alloc_word(tokens->str);
			tokens = tokens->next;
		}
		add_back_cmd(&cmd, arg,rdr);
		print_arg(arg);
		print_rdr(rdr);
	 	if (tokens)
			tokens = tokens->next;	
	}
	return cmd;
}



