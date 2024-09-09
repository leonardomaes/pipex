/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaes <lmaes@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:22:59 by lmaes             #+#    #+#             */
/*   Updated: 2024/09/05 12:23:00 by lmaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	error_bonus(const char *strerr)
{
	perror(strerr);
	exit(1);
}

int	open_files_bonus(t_pipex **pipex_tab, char *argv[], int argc)
{
	(*pipex_tab)->infile = open(argv[1], O_RDONLY, 0777);
	if ((*pipex_tab)->infile < 1)
		return (-1);
	(*pipex_tab)->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC,
			0777);
	if ((*pipex_tab)->outfile < 1)
		return (-1);
	return (0);
}

char	**get_command_bonus(char *argv)
{
	char	**comm;

	comm = ft_split(argv, ' ');
	if (!comm)
		return (NULL);
	comm[0] = ft_strjoin("/bin/", comm[0]);
	return (comm);
}
