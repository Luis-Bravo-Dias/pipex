/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 16:58:58 by lleiria-          #+#    #+#             */
/*   Updated: 2022/07/21 11:27:37 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//end[1] -> child process (writes)
//end[0] -> parent process (reads)
#include "../pipex.h"

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