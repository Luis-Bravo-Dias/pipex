/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commander.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 10:31:14 by lleiria-          #+#    #+#             */
/*   Updated: 2022/07/27 17:52:33 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

/*A função concatena o CMD com o path
e testa para ver se é válido ou não
exemplo:
CMD_PATH = /ls
PATH = /bin
TMP2 = PATH + CMD_PATH
CMD_PATH = TMP2
e o CMD_PATH fica com /bin/ls*/
void	get_cmd_path(t_struct *s)
{
	char	*tmp;
	char	*tmp2;
	int		i;
	int		n;

	n = -1;
	while (s->path[++n])
	{
		tmp = ft_strjoin(s->path[n], s->cmd_path);
		tmp2 = ft_strdup(tmp);
		free(tmp);
		i = access(tmp2, F_OK);
		if (i < 0)
		{
			free(tmp2);
			continue ;
		}
		else
		{
			s->cmd_path = ft_strdup(tmp2);
			free(tmp2);
			return ;
		}
	}
	special_error(s, "");
}

/*verifica o argumento com o
comando no seu interior e
separa o comando para verificar
o path, Exemplo:
"ls -l" o CMD_PATH é /ls, e
o CMD é ls -l*/
char	*get_path(char *tmp)
{
	int		i;
	char	*path;

	i = -1;
	while (tmp[++i])
		if (tmp[i] == ' ')
			break ;
	path = ft_substr(tmp, 0, i);
	return (path);
}

/*testa se o absolute arg tem
o path correto e se se é um
comando/path válido*/
void	test_path(t_struct *s)
{
	int	i;

	i = access(s->cmd_path, F_OK);
	if (i < 0)
		error_all(s, "");
}

/*Recebe a struct com os argumentos
e paths e vai verificar se o
argumento tem '/', vai assumir
automaticamente que passou o
absolute path, então vai buscar o
comando e testá-lo.
Se o argumento não tiver '/', vai
pegar o argumento e usar split para
obter o comando e colocá-lo com '/'
no CMD_PATH, passando-o para a
função get_cmd_path para conseguir
ver o path correto para o comando*/
void	get_cmd(t_struct *s, int n)
{
	char	*tmp;
	int		i;

	i = -1;
	if (s->arg[n][0] == '/')
	{
		s->cmd = ft_split(ft_strrchr(s->arg[n], '/') + 1, ' ');
		while (s->arg[n][++i])
			if (s->arg[n][i] == ' ')
				break ;
		s->cmd_path = ft_substr(s->arg[n], 0, i);
		test_path(s);
	}
	else
	{
		s->cmd = ft_split(s->arg[n], ' ');
		s->cmd_path = get_path(s->arg[n]);
		tmp = ft_strjoin("/", s->cmd_path);
		free(s->cmd_path);
		s->cmd_path = strdup(tmp);
		free(tmp);
		tmp = NULL;
		get_cmd_path(s);
	}
}
