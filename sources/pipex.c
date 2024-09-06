/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaes <lmaes@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:34:14 by lmaes             #+#    #+#             */
/*   Updated: 2024/09/06 12:34:16 by lmaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	parent_process(t_pipex **pipex_tab, char *argv[])
{
	dup2((*pipex_tab)->pipefd[0], STDIN_FILENO);
	dup2((*pipex_tab)->outfile, STDOUT_FILENO);
	close((*pipex_tab)->pipefd[1]);
	(*pipex_tab)->comm = get_command(argv[3]);
	execve((*pipex_tab)->comm[0], (*pipex_tab)->comm, NULL);
	error("Parent process failed");
}

void	child_process(t_pipex **pipex_tab, char *argv[])
{
	dup2((*pipex_tab)->infile, STDIN_FILENO);
	dup2((*pipex_tab)->pipefd[1], STDOUT_FILENO);
	close((*pipex_tab)->pipefd[0]);
	(*pipex_tab)->comm = get_command(argv[2]);
	execve((*pipex_tab)->comm[0], (*pipex_tab)->comm, NULL);
	error("Child process failed");
}
