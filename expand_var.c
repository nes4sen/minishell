/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:46:42 by nosahimi          #+#    #+#             */
/*   Updated: 2025/07/12 20:19:11 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int *global_quote_stat()
{
	static int quote = 0;
	return (&quote);
}
// get_expand
ft_exstrlen(char *str)
{
	int	i;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i])
	}
}
ft_exstrcpy()
{
	
}
ft_exsubstr()
{
	
}
t_token *expand_token(t_env *env, char *str)
{
	int 	i;
	int		quote;
	t_token *head;
	int		j;

	j = 0;
	quote = 0;
	i = 0;
	head = NULL;
	while (str[i])
	{
		if (!quote && (str[i] == '\'' || str[i] == '"'))
			quote = str[i++];		
		else if (quote == str[i])
			quote = 0;
		if (str[i] == '$' && quote != '\'')
		{
			token_add_back(&head, ft_substr(j, i, str), 0);
			get_expand();
		}
		j = i;
	}
}


/* 
							var="1   2  ' '   3  "
build anouther tokenizer that split tokens by quotes and give them a stat

example 	echo hello << world  > hello"$var"'$var'" "    

1_ normal tokenizer 		  [echo]  [>] [|] [hello"$var toto" '$var'$var" "]


2_ expand_tokenizer 		 [echo] [hello] ["$var toto"] ['$var'] [$var] [" "]
loop into each tokens and seperate them by quotes

3_ 						 	[hello] [1  2  3  toto] [$var] [1   2   3] [ ]
remove the quote and mark the tokens by stats: state 1 -> double quoted , 2-> single quoted, 3-> no quote
then expand the variable

	
4_ seperate by spaces if the spaces in the 3 state  
							 [echo] [echo 1  2   3 toto$var1] [2] [3 ]





[echo]  []   [hello]  []   [<<]     []    [world] [hello] ["$var"] ['$var'] [" "]
cmd    sep   cmd	  sep  herdoc   sep    dlm     cmd      cmd      cmd     cmd  
noq    noq   noq      noq  noq      noq    noq     noq     2q        1q      2q





*/


/*		echo hello  " $var" [echo] [ ] [hello] [ ] [ $var]
		[echo] -> [hello  1  2  ' ' 3];
char *args[echo , hello, 1, 2, ' ', 3];
	
										echo hello >'toto'" $var   ' yoy'"     $var"tt""$var"

		
ultimate-tokenizer						[echo] [ hello] [ >] ['toto'][" var   ' yo'"][     $var] ["tt"] ["$var"]
	
syntax_error							old syntax error + skip spaces

										mark each of the token by 3 stats , 2quted or single quoted or not quoted
										the marks for the expand
										
										
next step is removing the quotes, and expand	[echo] [ hello] [ >] [toto] [ var   ' yo'] [1  2   3 ] [tt] [1  2   3]  echo hello  "  rork  "
																																			y
												noq    noq       noq  sq     dq             noq         dq    dq     
echo										[echo] [hello]  [>] [toto] [ var]

echo hello toto"   world" $var"toto"
[echo] [hello] [toto] ["world"] [$var] [toto]
s       s         s      j        s     j
*/