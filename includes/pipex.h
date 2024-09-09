/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaes <lmaes@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:44:34 by lmaes             #+#    #+#             */
/*   Updated: 2024/09/05 11:44:34 by lmaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"
#include "libft/libft.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

typedef struct pipex
{
	int		infile;
	int		outfile;
	int		pipefd[2];
	char	**comm;
	char	**comm_paths;
	char	*path;
}			t_pipex;

/*  UTILS  */
void		error(const char *strerr);
int			open_files(t_pipex **pipex_tab, char *argv[], int argc);
char		**get_command(char *argv);
void		free_tab(t_pipex **pipex);
/*  MAIN  */
int			ft_pipex(char **argv, t_pipex **pipex_tab);
/*  PIPEX  */
void		child_process(t_pipex **pipex_tab, char *argv[]);
void		parent_process(t_pipex **pipex_tab, char *argv[]);
