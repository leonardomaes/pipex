/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaes <lmaes@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:38:29 by lmaes             #+#    #+#             */
/*   Updated: 2024/09/05 11:38:31 by lmaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	ft_pipex(char **argv, t_pipex **pipex_tab)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	else if (pid == 0)
		child_process(pipex_tab, argv);
	pid = fork();
	if (pid == -1)
		return (-1);
	else if (pid == 0)
		parent_process(pipex_tab, argv);
	close((*pipex_tab)->pipefd[1]);
	close((*pipex_tab)->pipefd[0]);
	waitpid(pid, NULL, 0);
	wait(NULL);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_pipex	*pipex;

	if (argc < 5)
	{
		ft_putstr_fd("Not enough arguments", 2);
		exit(1);
	}
	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
	{
		ft_putstr_fd("Memory allocation failed\n", 2);
		exit(1);
	}
	if (open_files(&pipex, argv, argc) == -1)
	{
		free(pipex);
		error("Error with opening file");
	}
	if (pipe(pipex->pipefd) == -1)
		error("Pipe creation failed");
	if (ft_pipex(argv, &pipex) < 0)
		error("Error with the pipe process");
	close(pipex->infile);
	close(pipex->outfile);
	free(pipex);
	return (0);
}
