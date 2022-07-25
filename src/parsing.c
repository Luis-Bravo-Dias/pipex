/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 16:35:51 by lleiria-          #+#    #+#             */
/*   Updated: 2022/07/25 17:18:42 by lleiria-         ###   ########.fr       */
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
			if (ft_strlen(buffer) == ft_strlen(tmp2))
				if (!ft_strncmp(tmp2, buffer, ft_strlen(av[2])))
					break;
			write(fd, buffer, ft_strlen(buffer));
			free(buffer);
		}
		free(tmp);
		free(tmp2);
		free(buffer);
	}
}

void	redirect(t_struct *s, int ac, char **ac)
{
	s->here_doc = 0;
	s->infile = open(av[1], O_RDONLY);
	s->outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (s->infile < 0 || s->outfile < 0)
	{
		perror("");
		exit(EXIT_FAILURE);
	}
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
	heredoc(av, file);
}

void	parsing(t_struct *s, int ac, char **av)
{
	int	i;
	int	n;

	if (!ft_strncmp(av[1], "here_doc", 9))
		append(s, ac, av);
	else
		redirect(p, ac, av);
}