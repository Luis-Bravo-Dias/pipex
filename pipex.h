/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 11:01:20 by lleiria-          #+#    #+#             */
/*   Updated: 2022/07/27 17:55:44 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "ft_printf/ft_printf.h"
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_struct
{
	int		infile;
	int		outfile;
	int		pipe[2];
	int		id;
	int		pipe_nbr;
	int		cmd_nbr;
	pid_t	pid;
	char	**cmd;
	char	**path;
	char	*cmd_path;
	char	**arg;
	char	*env;
	int		in;
	int		out;
	int		here_doc;
	char	*limiter;
}	t_struct;

//main.c
void	verify(int fd, int fork, int pipe);
void	child_process(t_struct *s, int i, char **env);
//parsing.c
void	heredoc(char **av, int fd);
void	redirect(t_struct *s, int ac, char **av);
void	append(t_struct *s, int ac, char **av);
void	parsing(t_struct *s, int ac, char **av);
void	find_path(t_struct *s, char **env);
//free_for_all.c
void	free_here(t_struct *s);
void	free_all(t_struct *s);
void	error(t_struct *s, char *m);
void	error_all(t_struct *s, char *m);
void	special_error(t_struct *s, char *m);
//commander.c
void	get_cmd_path(t_struct *s);
char	*get_path(char *tmp);
void	test_path(t_struct *s);
void	get_cmd(t_struct *s, int n);

#endif