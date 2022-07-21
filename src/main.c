/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 15:11:45 by lleiria-          #+#    #+#             */
/*   Updated: 2022/07/21 15:46:54 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	verify(int fd, int fork, int pipe)
{
	if (fd == -1)
		perror("");
	if (fork == -1)
		perror("");
	if (pipe == -1)
		perror("");
}

int	main(int ac, char **av, char **env)
{
	//int	fd;

	/*if (ac < 4)
		ft_printf("Insufficient arguments\n");*/
	(void)av;
	(void)ac;
	/*else
	{
		fd = open(av[1], O_RDONLY);
		//verify (fd);
	}
	return (0);*/
	int 	i;
	char	**path;

	i = 0;
	while (env[i])
	{
		if (env[i][0] == 'P' && env[i][1] == 'A')
			path = ft_split(env[i] + 5, ':');
		i++;
	}
	
	i = 0;
	while (path[i])
	{
		ft_printf("%s\n", path[i]);
		i++;
	}
}
