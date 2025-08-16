#ifndef DEBUG_H
# define DEBUG_H

# include "parsing/minishell.h"

void	print_cmd_struct(t_cmd *cmd);
void	print_tokens(t_token *tokens);
void	print_extokens(t_extoken *extokens);
void	print_subtokens(t_token *subtoken);

#endif
