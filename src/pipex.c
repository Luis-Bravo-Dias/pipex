/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 16:58:58 by lleiria-          #+#    #+#             */
/*   Updated: 2022/07/21 16:03:56 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//end[1] -> child process (writes)
//end[0] -> parent process (reads)
#include "../pipex.h"

#define PID 1


void	errors(int nbr, int id)
{
	if (id == 1)
	{
		pid 
	}
	
}

void *test(void *test)
{
	if (!test)
	{
		free(cenas);
		exit(1);
	}	
	else 
		return (test);
}

test(strdup())



void	child_process(int f1, char *cmd1)
{
	
}

void	pipex(int f1, int f2)
{
	int		end[2];
	pid_t	parent;

	pipe(end);
	parent = fork();
	if (parent < 0)
		return (perror(""));
	if (parent == 0)
		child_process(f1, cmd1);
	else
		parent_process(f2, cmd2);
}