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
void		error_bonus(const char *strerr);
int			open_files_bonus(t_pipex **pipex_tab, char *argv[], int argc);
char		**get_command_bonus(char *argv);
/*  MAIN  */
int			ft_pipex_bonus(char **argv, t_pipex **pipex_tab, int argc);
/*  PIPEX  */
void		child_process_bonus(t_pipex **pipex_tab, char *argv);
void		parent_process_bonus(t_pipex **pipex_tab, char *argv[]);
