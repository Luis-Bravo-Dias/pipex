/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 15:11:45 by lleiria-          #+#    #+#             */
/*   Updated: 2022/07/04 14:53:48 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

/*void	verify(int fd, int fork)
{
	if (fd == -1)
		perror("");
	if (fork == -1)
		perror("");
}*/

int	main(int ac, char **av)
{
	//int	fd;

	if (ac < 4)
		ft_printf("Insufficient arguments\n");
	(void)av;
	/*else
	{
		fd = open(av[1], O_RDONLY);
		//verify (fd);
	}*/
	return (0);
}
