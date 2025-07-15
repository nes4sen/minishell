/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:46:42 by nosahimi          #+#    #+#             */
/*   Updated: 2025/07/15 20:34:58 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_expandable(char *str)
{
	int quote;

	quote = 0;
	while (*str)
	{
		if (!quote && is_quote(*str))
			quote = *str;
		else if (quote == *str)
			quote = 0;
		if (quote != '\'' && *str == '$')
			return (1);
		str++;
	}
	return (0);
}

t_token *expand_token(t_token *head)
{
	t_token *current;
	t_token *next;
	char 	*str;

	str = head->str;
	current = head;
	while (*str)
	{
		if (is_quote(*str))
			get_quoted_token();
		else
		{
			while ()
		}
		str++;
	}
	next = head->next;
}

int	is_quoted_str(char *str)
{
	while (*str)
	{
		if (is_quote(*str))
			return (1);
		str++;
	}
	return (0);
}
int str_no_quote_len(char *str)
{
	int		len;
	int 	quote;
	int		i;
	
	len = 0;
	quote = 0;
	i = 0;
	while (str[i])
	{
		if (!quote && is_quote(str[i]))
			quote = str[i];
		else if (quote == str[i])
			quote = 0;
		else
			len++;
		i++;
	}
	return (len);
}
void	remove_quote(t_token *token)
{
	char	*s;
	char	*tmp;
	int		i;
	int		quote;
	
	s = token->str;
	tmp = malloc(str_no_quote_len(s) + 1);
	if (tmp)
	{
		//free
	}
	i = 0;
	quote = 0;
	while(*s)
	{
		if (!quote && is_quote(*s))
			quote = *s;
		else if (quote == *s)
			quote = 0;	
		else
			tmp[i++] = *s;
		s++;
	}
	tmp[i] = '\0';
	free(token->str);
	token->str = tmp;
 } 

 
t_token *prepare_for_expand(t_env *env, t_token  *head)
{
	while (head)
	{
		if (is_expandable(head->str))
			expand_token(head);
		else if (is_quoted_str(head->str))
			remove_quote(head);
		head = head->next;
	}
}
/*
	var='1 "2"  3 '

		"e '' ""c""h""o"  hello$var"$var"
		 


*/

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





[echo]  []   [hello]  []   [<<]     []    [world] [hello] [toto $var] [yy$var] [ ]
cmd    sep   cmd	  sep  herdoc   sep    dlm     cmd      cmd      cmd     cmd  
noq    noq   noq      noq  noq      noq    noq     noq     2q        noq      2q
                                                           toto  1   2   3 yy1 2 3 

[echo]  []   ["hello"] [] [<<] [world] ['$var']
[echo]  []   [hello] [] [<<] [world] [$var]
echo hello << world1 2 3
[echo] [hello] [<<] [world1] [2] [3]

[echo]  []   [hello] [] [<<] [world] [$var]

var="1   2  ' '   3  "  

echo << hello"$var "$var"toto  yy"

[echo]    [<<]     [hello"$var "$var"toto  yy"]
[echo]    [<<]    [hello"1 2 ' '  3 "toto] [yy]


if (s[i] == '$' && quote != '\'')

hello  hello
echo hello1 2  3 1
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