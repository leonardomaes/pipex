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

#include "includes/libft/libft.h"
#include "includes/ft_printf/ft_printf.h"

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

typedef struct pipex
{
	int	infile;
	int	outfile;
	int	pipefd[2];
	char	**comm;
	char	**comm_paths;
	char	*path;
} t_pipex;

void	error(const char *strerr);
void	open_files(t_pipex **pipex_tab, char *argv[], int argc);
char	**get_command(char	*argv);

void	child_process(t_pipex **pipex_tab, char *argv[]);
void	parent_process(t_pipex **pipex_tab, char *argv[]);

char	*find_path(char **envp);
char	*get_cmd(char **paths, char *cmd);
