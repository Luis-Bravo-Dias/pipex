/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 15:11:45 by lleiria-          #+#    #+#             */
/*   Updated: 2022/07/27 18:07:23 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	child_process(t_struct *s, int i, char **env)
{
	if (pipe(s->pipe) == -1)
		error(s, "");
	s->pid = fork();
	if (s->pid < 0)
		error(s, "");
	if (!s->pid)
	{
		close(s->pipe[0]);
		if (s->id == 0)
		{
			if (s->infile < 0)
				exit(127);
			dup2(s->infile, STDIN_FILENO);
			dup2(s->pipe[1], STDOUT_FILENO);
		}
		else if (s->id == s->cmd_nbr - 1)
			dup2(s->outfile, STDOUT_FILENO);
		else
			dup2(s->pipe[1], STDOUT_FILENO);
		get_cmd(s, i);
		execve(s->cmd_path, s->cmd, env);
	}
	close (s->pipe[1]);
	wait(NULL);
	dup2(s->pipe[0], STDIN_FILENO);
}

int	main(int ac, char **av, char **env)
{
	t_struct	s;

	if (ac < 5)
	{
		ft_printf("Insufficient arguments\n");
		exit(EXIT_FAILURE);
	}
	parsing(&s, ac, av);
	s.cmd_nbr = ac - 3 - s.here_doc;
	find_path(&s, env);
	s.id = -1;
	while (++s.id < s.cmd_nbr)
		child_process(&s, s.id + s.here_doc, env);
	if (s.here_doc)
		unlink(".heredoc_tmp");
	free_all(&s);
	return (0);
}

	/*(void)av;
	else
	{
		fd = open(av[1], O_RDONLY);
		//verify (fd);
	}
	return (0);
	int		i;
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
	}*/