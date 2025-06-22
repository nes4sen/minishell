/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 10:43:52 by nosahimi          #+#    #+#             */
/*   Updated: 2025/06/22 18:40:29 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <readline/readline.h>
#include <readline/history.h>

#define VOID_MODE 0
#define SINGLE_MODE 1
#define DOUBLE_MODE 2

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
	int				join;
	struct	s_token	*next;
}t_token;

typedef struct s_cmd
{
	char *cmd;

} t_cmd;

typedef struct s_env
{
	char			*str;
	struct s_env	*next;
}t_env;

typedef struct s_trash
{
	void *ptr;
	struct s_trash *next;
}t_trash;

int	ft_strlen(char *str);

// t_cmd	*parsing(line);
int		syntax_error(char *str);
int		is_valid_quotes(char *str);
int		is_valid_arrows(char *str);
int		is_valid_pipe(char *str);
int		is_symbole(char c);


t_token *tokenizer(char *str);

void	add_back_env(t_env **head, char *str);
t_env	*creat_node_env(char *str);
t_env	*get_env(char **envp);

#endif  