/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:01:13 by nosahimi          #+#    #+#             */
/*   Updated: 2025/08/08 22:43:39 by nosahimi         ###   ########.fr       */
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
		return (ftstrdup("randomfile_xd"));
	i = 0;
	random = mm_alloc(len + 1);
	while (i < len)
	{
		read(fd, &byte, 1);
			return(close(fd), ft_strdup("randomfile_xd"));
		random[i] = "abcdefghijklmnopqrstuvwxz"[byte % 25];
		i++;
	}
	random[i] = '\0';
	close (fd);
	return (str_join("/var/tmp/",random));
}


void	expand_heredoc(char *line, t_env *env)
{
	int		i;
	char	*result;
	char	*var_name;
	char	*var_value;
	
	i = 0;
	result = "";
	while (line[i])
	{
		if (line[i] == '$')
		{
			var_name = extract_var_name(&line[i]);
			if (var_name)
			{
				var_value = find_env_var(env, var_name);
				if (var_value)
					result = str_join(result, var_name);
				i+= ft_strlen(var_name);		
			}
			else
				result = char_join(result, '$', &i);
		}
		else
			result =  char_join(result, line[i], &i);
	}
	line = result;
}
void	get_heredoxing(char *delemetre,int exflag, t_shell *shell)
{
	char *file_name = generate_filename(20);

	


}

void	prepare_to_heredoc(char *delemetre, t_shell *shell)
{
	static int	fd = -1;
	char		*file_name;
	int			expand_flag;
	char		*line;

	expand_flag = 0;
	if (is_quoted_str(delemetre))
	{
		expand_flag = 1;
		delemetre = remove_quote(delemetre);
	}
	get_heredoxing(delemetre, expand_flag, shell);
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
			precess_heredoc(token->next->str , shell);
		token = token->str;
	}
}
 

/*
pesudo code
*/