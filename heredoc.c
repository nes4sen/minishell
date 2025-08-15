/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:01:13 by nosahimi          #+#    #+#             */
/*   Updated: 2025/08/14 10:37:03 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	*generate_filename(int len)
{
	unsigned char	byte ;
	char			*random;
	int				fd;
	int				i;
	
	fd = open("/dev/random",O_RDONLY);
	if (fd < 0)
		return (ft_strdup("randomfile_xd"));
	i = 0;
	random = mm_alloc(len + 1);
	while (i < len)
	{
		if (read(fd, &byte, 1) < 0)
		{
			close(fd);
			return(ft_strdup("randomfile_xd"));
		}
		random[i] = "abcdefghijklmnopqrstuvwxz"[byte % 25];
		i++;
	}
	random[i] = '\0';
	close (fd);
	return (str_join("/tmp/",random));
}

void	expand_heredoc(char **line, t_shell *shell)
{
	int		i;
	char	*result;
	char	*var_name;
	char	*var_value;
	
	i = 0;
	result = "";
	while ((*line)[i])
	{
		if ((*line)[i] == '$')
		{
			var_name = extract_var_name(line[i]);
			if (var_name)
			{
				var_value = find_env_var(shell, var_value);
				if (var_value)
					result = str_join(result, var_value);
				i+= ft_strlen(var_name);
			}
			else
				result = char_join(result, '$', &i);
		}
		else
			result =  char_join(result, (*line)[i], &i);
	}
	*line = result;
}

void	heredoxing(char **fname, char *dlmtr,int exflag, t_shell *shell)
{
	char	*line;
	int		fd;
	int		pid;

	*fname = generate_filename(20);
	fd = open(*fname, O_CREAT | O_WRONLY, 0644);
	if (fd < 0)
		exit(1);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		while (1)
		{
			line = readline("> ");
			if (!line)
				break;
			if (!ft_strcmp(line, dlmtr))
			{
				mm_free(FREE_ALL);
				close(fd);
				exit(0);
			}
			if (exflag)
				expand_heredoc(&line, shell);
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
		}
	}
	else if (pid)
		wait(NULL);
}

char	*prepare_to_heredoc(char *delemetre, t_shell *shell)
{
	char		*fname;
	int			expand_flag;

	expand_flag = 0;
	if (is_quoted_str(delemetre))
	{
		expand_flag = 1;
		delemetre = remove_quote(delemetre);
	}
	heredoxing(&fname ,delemetre, expand_flag, shell);
	return (fname);
}

void	scan_for_heredoc(t_shell *shell)
{

	/*
	loop through the tokens until the end
		loop through the token until thw pipe is found
			if the token is a delemetere the function prepare_for_heredoc() is called
				prepare_for_heredoc() --> 1_ flag the delemetre with expand_flag
										  2_ remove the quotes from delemetre
										  3_ heredoxing(&fname , delemetre, expand_flag, shell) --> 1_ generate a randome file name and open it
										  															2_ create a child , why ? 	
		
	*/
	t_token *token;
	t_cmd	*cmd;
	char	*file_name;

	token = shell->tokens;
	cmd = shell->cmd;
	file_name = NULL;
	while (token)
	{
		while (token && token->type != PIPE)
		{
			if (token->type == DLMTR)
				file_name = prepare_to_heredoc(token->str, shell);
			token = token->next;
		}
		if (cmd)
			cmd->heredox = file_name;
		if (token)
			token = token->next;
		cmd = cmd->next;
	}
}
 
