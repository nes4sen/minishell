/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:01:13 by nosahimi          #+#    #+#             */
/*   Updated: 2025/08/07 11:15:12 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

char *str_join(char *old, char *new)
{
    char *result;
    int old_len;
    int new_len;
    
    if (!old && !new)
        return (NULL);
    old_len = strlen(old);
    new_len = strlen(new);
    result = malloc(old_len + new_len + 1);
    // if (!result)
    //     ;
    strcpy(result, old);
    strcpy(result + old_len, new);
    return (result);
}

char	*generate_filename(int len)
{
	int		fd;
	char	*random;
	int		i;
	unsigned char byte ;
	
	fd = open("/dev/random",O_RDONLY);
	// if (fd < 0)
	// 	return (ftstrdup("randomfile_xd"));
	i = 0;
	random = malloc(len + 1);
	while (i < len)
	{
		read(fd, &byte, 1);
			// return(close(fd), ft_strdup("randomfile_xd"));
		random[i] = "abcdefghijklmnopqrstuvwxz"[byte % 25];
		i++;
	}
	random[i] = '\0';
	close (fd);
	return (str_join("/var/tmp/",random));
}
int	handle_herdoc(char *str)
{
	static int fd = -1;
	char	*dlmtr = str;
	char	*file_name;
	int		r_fd;
	int		w_fd;
	char	*rline;
	
	
 	file_name = generate_filename(20);
	printf("%s\n", file_name);
	w_fd = open(file_name, O_WRONLY | O_CREAT , 0644);
	r_fd = open(file_name, O_RDONLY);
	// printf("r_fd = %d  | w_fd = %d \n", w_fd, r_fd);
	while (1)
	{
		rline = readline("> ");
		if (!strcmp(rline, dlmtr))
			break;
		write(w_fd, rline, strlen(rline));
		write(w_fd, "\n", 1);
	}
	return(r_fd); 
}
int main()
{
	char byte;
	int fd = handle_herdoc("hello");
	while(read(fd, &byte, 1) > 0 )
	{
		
		printf("%c", byte);
	}
}
void	process_herdoc(char *delemetre, t_cmd **cmd)
{
	static int	fd = -1;
	char		*file_name;
	int			expand;
	char		*line;

	expand = 0;
	file_name = generate_filename(20);
	if (is_quoted_str(delemetre))
	{
		expand = 1;
		delemetre = remove_quote(delemetre);
	}
	while (1)
	{
		line = readline
	}
}
void	handle_heredoc(t_shell *shell)
{
	t_token *token;
	t_cmd	*cmd;

	token = shell->tokens;
	cmd = shell->cmd;
	while (token)
	{
		if (token->type == HEREDOC || token->type == PIPE)
			precess_heredoc(token->next->str , &cmd);
		token = token->str;
	}
}

// int	handle_herdoc(t_token *token)
// {
// 	static int	fd = -1;
// 	char		*dlmtr;
	
// 	if (token->type = DLMTR)
// 	{
		
// 	}
// 	return (fd);
// }

/*
pseudo code :

while (t_shell *shell)
{
	t_token *token;
	t_cmd   *cmd;
	
	if (token->str == HEREDOC)
		heredoc_process()
	token = token->str;
}


*/