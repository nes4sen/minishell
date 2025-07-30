/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 10:22:45 by nosahimi          #+#    #+#             */
/*   Updated: 2025/07/30 21:30:00 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_arg(char **arg)
{
	int i;

	i = 0;
	while (arg[i])
	{
		printf("Arg[%d]: %s\n", i, arg[i]);
		i++;
	}
}

void print_rdr(t_rdr *rdr)
{
	t_rdr *tmp;

	tmp = rdr;
	while (tmp)
	{
		printf("Rdr file: %s, type: %d\n", tmp->file, tmp->type);
		tmp = tmp->next;
	}
}
void print_all_cmd(t_cmd *cmd)
{
	t_cmd *tmp;
	

	tmp = cmd;
	while (tmp)
	{
		printf("Command:\n");
		print_arg(tmp->arg);
		print_rdr(tmp->rdr);
		tmp = tmp->next;
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
	{
		// get_heredoc();
		
	}
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
		while (tokens->subtoken)
		{
			
		}
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

// t_cmd *build_cmd_list(t_token *tokens)
// {
// 	t_cmd	*cmd;
// 	char	**arg;
// 	t_rdr	*rdr;
// 	int 	i;

// 	cmd = NULL;
// 	rdr = NULL;
// 	while(tokens)
// 	{
// 		arg = alloc_arg(tokens);
// 		i = 0;
// 		while (tokens && tokens->type != 1)
// 		{
// 			get_rdr(&rdr, tokens->str, tokens->type);
// 			if (!tokens->type)
// 				arg[i++] = alloc_word(tokens->str);
// 			tokens = tokens->next;
// 		}
// 		add_back_cmd(&cmd, arg,rdr);
// 		print_arg(arg);
// 		print_rdr(rdr);
// 	 	if (tokens)
// 			tokens = tokens->next;	
// 	}
// 	return cmd;
// }

int args_len(t_token *token)
{
	int len;
	t_token *tmp;

	len = 0;
	while (token)
	{
		if (token->subtoken)
		{
			tmp = token->subtoken;
			while (tmp)
			{
				len++;
				tmp = tmp->next;	
			}
		}else if (token->type == CMD)
			len++;
		token = token->next;
	}
	return (len);
}
char **space_for_args(t_token *token)
{
	int len;
	char **args;
	int i;

	len = args_len(token);
	if (len == 0)
		return (NULL);
	i = 0;
	args = malloc(sizeof(char *) * (len + 1));
	if (!args)
	{
		//free
	}
	while (i < len)
	{
		args[i] = NULL;
		i++;
	}
	return (args);
}

void get_args(char ***args, t_token *token)
{
	int i;
	
	i = 0;
	if (token->subtoken)
	{
		while (token->subtoken)
		{
			(*args)[i] = alloc_word(token->subtoken->str);
				i++;
			token->subtoken = token->subtoken->next;
		}
	}
	else if (token->type == CMD)
	{
		(*args)[i] = alloc_word(token->str);
		i++;
	}
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
		// if (token->subtoken)
		while (token && token->type != 1)
		{
			get_rdr(&rdr, token->str, token->type);
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
