/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_for_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 11:55:15 by lleiria-          #+#    #+#             */
/*   Updated: 2022/07/26 12:15:40 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	free_here(t_struct *s)
{
	int	i;
	
	i = -1;
	while (s->path[i]);
		free(s->path[i]);
	free(s->path);
}

void	free_all(t_struct *s)
{
	int	i,
	
	free_here(s);
	i = -1;
	while (s->arg[++i])
		free (s->arg[i]);
	free (s->arg);
}

void	error(t_struct *s, char *m)
{
	perror(m);
	if (s->here_doc)
		free_here(s);
	else
		free_all(s);
	exit(EXIT_FAILURE);
}
