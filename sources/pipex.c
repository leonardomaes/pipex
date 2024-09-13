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

#include "../includes/pipex.h"

void	parent_process(t_pipex **pipex_tab, char *argv[])
{
	dup2((*pipex_tab)->pipefd[0], STDIN_FILENO);
	dup2((*pipex_tab)->outfile, STDOUT_FILENO);
	close((*pipex_tab)->pipefd[1]);
	(*pipex_tab)->args = ft_split(argv[3], ' ');
	(*pipex_tab)->comm = get_command((*pipex_tab)->args[0],
			(*pipex_tab)->cmd_paths);
	if (!(*pipex_tab)->comm)
	{
		error("Command not found\n", *pipex_tab);
	}
	execve((*pipex_tab)->comm, (*pipex_tab)->args, environ);
	error("Parent process failed", *pipex_tab);
}

void	child_process(t_pipex **pipex_tab, char *argv[])
{
	dup2((*pipex_tab)->infile, STDIN_FILENO);
	dup2((*pipex_tab)->pipefd[1], STDOUT_FILENO);
	close((*pipex_tab)->pipefd[0]);
	(*pipex_tab)->args = ft_split(argv[2], ' ');
	(*pipex_tab)->comm = get_command((*pipex_tab)->args[0],
			(*pipex_tab)->cmd_paths);
	if (!(*pipex_tab)->comm)
	{
		error("Command not found\n", *pipex_tab);
	}
	execve((*pipex_tab)->comm, (*pipex_tab)->args, environ);
	error("Child process failed", *pipex_tab);
}
