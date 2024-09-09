/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaes <lmaes@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:34:14 by lmaes             #+#    #+#             */
/*   Updated: 2024/09/06 12:34:16 by lmaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	parent_process_bonus(t_pipex **pipex_tab, char *argv[])
{
	dup2((*pipex_tab)->pipefd[0], STDIN_FILENO);
	dup2((*pipex_tab)->outfile, STDOUT_FILENO);
	close((*pipex_tab)->pipefd[1]);
	(*pipex_tab)->comm = get_command_bonus(argv[3]);
	execve((*pipex_tab)->comm[0], (*pipex_tab)->comm, NULL);
	error_bonus("Parent process failed");
}

void	child_process_bonus(t_pipex **pipex_tab, char *argv)
{
	dup2((*pipex_tab)->infile, STDIN_FILENO);
	dup2((*pipex_tab)->pipefd[1], STDOUT_FILENO);
	close((*pipex_tab)->pipefd[0]);
	(*pipex_tab)->comm = get_command_bonus(argv);
	execve((*pipex_tab)->comm[0], (*pipex_tab)->comm, NULL);
	error_bonus("Child process failed");
}
