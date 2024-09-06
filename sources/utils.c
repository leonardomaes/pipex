/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaes <lmaes@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:22:59 by lmaes             #+#    #+#             */
/*   Updated: 2024/09/05 12:23:00 by lmaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	error(const char *strerr)
{
	perror(strerr);
	exit(1);
}

void	open_files(t_pipex **pipex_tab, char *argv[], int argc)
{
	(*pipex_tab)->infile = open(argv[1], O_RDONLY, 0777);
		if ((*pipex_tab)->infile < 1)
			error("Error opening file");
	(*pipex_tab)->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if ((*pipex_tab)->outfile < 1)
			error("Error opening file");
}

char	**get_command(char	*argv)
{
	char **comm;

	comm = ft_split(argv, ' ');
	if (!comm)
		return (NULL);
	comm[0] = ft_strjoin("/bin/", comm[0]);
	return (comm);
}
