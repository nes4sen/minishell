/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:01:13 by nosahimi          #+#    #+#             */
/*   Updated: 2025/08/22 22:12:51 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*generate_filename(int len)
{
	unsigned char	byte;
	char			*random;
	int				fd;
	int				i;

	fd = open("/dev/random", O_RDONLY);
	if (fd < 0)
		return (ft_strdup("randomfile_xd"));
	i = 0;
	random = mm_alloc(len + 1);
	while (i < len)
	{
		if (read(fd, &byte, 1) < 0)
		{
			close(fd);
			return (ft_strdup("randomfile_xd"));
		}
		random[i] = "abcdefghijklmnopqrstuvwxz"[byte % 25];
		i++;
	}
	random[i] = '\0';
	close(fd);
	return (str_join("/tmp/", random));
}

void	expand_heredoc(char **line, t_shell *shell)
{
	int		i;
	char	*result;
	char	*var_name;

	i = 0;
	result = "";
	while ((*line)[i])
	{
		if ((*line)[i] == '$')
		{
			var_name = extract_var_name(*line + i);
			if (var_name)
			{
				result = str_join(result, find_env_var(shell, var_name));
				i += ft_strlen(var_name) + 1;
			}
			else
				result = char_join(result, '$', &i);
		}
		else
			result = char_join(result, (*line)[i], &i);
	}
	free(*line);
	*line = NULL;
	*line = result;
}

void	herechild(char *dlmtr, t_shell *shell, int exflag, int fd)
{
	char	*line;

	signal(SIGINT, handle_segnal_herd);
	while (1)
	{
		line = readline(">");
		if (!line)
		{
			close(fd);
			write(2, "warning: here-document delimited by end-of-file\n", 48);
			break ;
		}
		if (!ft_strcmp(line, dlmtr))
		{
			mm_free(FREE_ALL);
			(close(fd)), (exit(0));
		}
		if (exflag)
			expand_heredoc(&line, shell);
		(write(fd, line, ft_strlen(line))), (write(fd, "\n", 1));
		if (!exflag)
			free(line);
	}
	(mm_free(FREE_ALL)), (exit(shell->exit_s));
}

int	heredoxing(char **fname, char *dlmtr, int exflag, t_shell *shell)
{
	int	fd;
	int	pid;
	int	status;

	*fname = generate_filename(20);
	fd = open(*fname, O_CREAT | O_WRONLY, 0644);
	if (fd < 0)
		exit(1);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		herechild(dlmtr, shell, exflag, fd);
	close(fd);
	waitpid(pid, &status, 0);
	setup_signals();
	if (WIFSIGNALED(status))
		return (mm_free(FREE_ALL_EXCEPT_ENV), shell->exit_s = 130, 130);
	if (WEXITSTATUS(status) == 130)
		return (mm_free(FREE_ALL_EXCEPT_ENV), shell->exit_s = 130, 130);
	else if (WIFEXITED(status))
		shell->exit_s = WEXITSTATUS(status);
	return (0);
}

char	*prepare_to_heredoc(char *delemetre, t_shell *shell)
{
	char	*fname;
	int		expand_flag;

	expand_flag = 1;
	if (is_quoted_str(delemetre))
	{
		expand_flag = 0;
		delemetre = remove_quote(delemetre);
	}
	if (heredoxing(&fname, delemetre, expand_flag, shell) == 130)
		return (NULL);
	return (fname);
}
