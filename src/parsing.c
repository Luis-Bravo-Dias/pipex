/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 16:35:51 by lleiria-          #+#    #+#             */
/*   Updated: 2022/07/28 11:55:51 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

/*Recria o here_doc no shell para
escrever o "pipe heredoc> ", depois
disso, lê o que o usuário digita
num loop infinito. Esse loop só vai
parar quando a função read receber
um input exatamente igual ao limitador,
enquanto não o encontrar, vai
resetar o input com ft_bzero*/
void	heredoc(char **av, int fd)
{
	char	*buffer;
	char	*tmp;
	char	*tmp2;

	tmp = ft_strdup(av[2]);
	tmp2 = ft_strjoin(tmp, "\n");
	while (1)
	{
		ft_printf("pipe heredoc> ");
		buffer = get_next_line(0);
		if (buffer)
		{
			if (ft_strlen(tmp2) == ft_strlen(buffer))
				if (!ft_strncmp(tmp2, buffer, ft_strlen(tmp2)))
					break ;
			write(fd, buffer, ft_strlen(buffer));
			free(buffer);
		}
	}
	free(tmp);
	free(tmp2);
}

/*Se for redirecionado, o outfile deve
apagar o que estiver lá e escrever o
novo input, é por isso que a flag O_TRUNC
é usada, se o outfile não existir, então
será criado com o O_CREAT e a flag do
here_doc será 0*/
void	redirect(t_struct *s, int ac, char **av)
{
	s->here_doc = 0;
	s->infile = open(av[1], O_RDONLY);
	s->outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (s->outfile < 0)
	{
		perror("");
		exit(EXIT_FAILURE);
	}
	if (s->infile < 0)
		perror("");
}

//0644 -> User: read & write Group: read Other: read
//O_TRUNC faz com que o ficheiro esteja vazio
//O_APPEND serve para concatenar o novo output com o antigo
void	append(t_struct *s, int ac, char **av)
{
	int	fd;

	if (ac < 6)
	{
		ft_printf("Insufficient arguments\n");
		exit(EXIT_FAILURE);
	}
	s->here_doc = 1;
	fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	s->outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0 || s->outfile < 0)
	{
		perror("");
		exit(EXIT_FAILURE);
	}
	heredoc(av, fd);
}

void	parsing(t_struct *s, int ac, char **av)
{
	int	i;
	int	n;

	if (!ft_strncmp(av[1], "here_doc", 9))
		append(s, ac, av);
	else
		redirect(s, ac, av);
	s->arg = malloc(sizeof(char *) * ac);
	if (!s->arg)
		error(s, "");
	i = 1;
	n = -1;
	while (++i < ac)
		s->arg[++n] = ft_strdup(av[i]);
	s->arg[++n] = 0;
}

void	find_path(t_struct *s, char **env)
{
	char	*path;
	int		i;

	i = -1;
	while (env[++i])
		if (!ft_strncmp(env[i], "PATH", 4))
			path = ft_strdup(env[i] + 5);
	if (!path)
		error(s, "");
	s->path = ft_split(path, ':');
	free(path);
}
