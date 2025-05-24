/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 10:43:52 by nosahimi          #+#    #+#             */
/*   Updated: 2025/05/24 12:30:38 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>


typedef struct s_node
{
	void			*content;
	struct s_node	*next;
}t_node;

typedef enum e_type
{
	CMD,
	PIPE,
	RDRIN,
	RDROUT,
	HEREDOC,
	APPND
}t_type;

typedef struct s_token
{
	char			*str;
	t_type			type;
	struct s_token *next;
}t_token;

typedef struct s_cmd
{
	char *cmd;

} t_cmd;

typedef struct s_trash
{
	void *ptr;
	struct s_trash *next;
}t_trash;

// t_cmd	*parsing(line);
int		syntax_error(char *str);
int		is_valid_quotes(char *str);
int		is_valid_arrows(char *str);
int		is_valid_pipe(char *str);

t_token *tokenizer(char *str);
#endif