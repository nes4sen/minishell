/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_red.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-laf <aait-laf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:32:41 by aait-laf          #+#    #+#             */
/*   Updated: 2025/08/21 15:00:54 by aait-laf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	rdrin(t_rdr *red, t_fd_fils *fil)
{
	struct stat	info;
	char		*tmp;

	if (stat(red->file, &info) != 0)
	{
		tmp = ft_strjoin(red->file, ": No such file or directory\n");
		write(2, tmp, ft_strlen(tmp));
		return (1);
	}
	fil->outfil = open(red->file, O_RDONLY);
	if (fil->outfil == -1)
		return (perror("open"), -1);
	dup2(fil->outfil, 0);
	close(fil->outfil);
	return (0);
}

int	rdrrout(t_rdr *red, t_fd_fils *fil)
{
	fil->infil = open(red->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fil->infil == -1)
		return (perror("open"), -1);
	dup2(fil->infil, 1);
	close(fil->infil);
	return (0);
}

int	appnd(t_rdr *red, t_fd_fils *fil)
{
	fil->infil = open(red->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fil->infil == -1)
		return (perror("open"), -1);
	dup2(fil->infil, 1);
	close(fil->infil);
	return (0);
}

int	heredoc(t_rdr *red)
{
	int	fd;

	fd = open(red->file, O_RDONLY);
	if (fd == -1)
		return (perror("open"), -1);
	dup2(fd, 0);
	close(fd);
	return (0);
}

int	count_len(t_env *temp)
{
	int	count;

	count = 0;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}
