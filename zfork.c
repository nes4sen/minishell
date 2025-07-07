/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nosahimi <nosahimi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 16:19:57 by nosahimi          #+#    #+#             */
/*   Updated: 2025/07/06 16:42:14 by nosahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
	int corrent_pid = getpid();
	printf("corrent pid = %d\n", corrent_pid);
	
	
	
	
	int pid = fork();
	printf("fork %d\n",pid);
	int new_pid = getpid();
	printf("new pid = %d\n", new_pid);
	printf("fork %d\n",pid);
	printf("fork final %d\n",pid);
}