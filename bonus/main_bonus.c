/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaes <lmaes@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:38:29 by lmaes             #+#    #+#             */
/*   Updated: 2024/09/05 11:38:31 by lmaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	ft_pipex_bonus(char **argv, t_pipex **pipex_tab, int argc)
{
	pid_t	pid;
	int		i;

	i = 2;
	while (i < argc - 2)
	{
		pid = fork();
		if (pid == -1)
			return (-1);
		else if (pid == 0)
			child_process_bonus(pipex_tab, argv[i]);
		i++;
	}
	pid = fork();
	if (pid == -1)
		return (-1);
	else if (pid == 0)
		parent_process_bonus(pipex_tab, argv);
	close((*pipex_tab)->pipefd[1]);
	close((*pipex_tab)->pipefd[0]);
	while (wait(NULL) > 0)
		;
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
	if (open_files_bonus(&pipex, argv, argc) == -1)
	{
		free(pipex);
		error_bonus("Error with opening file");
	}
	if (pipe(pipex->pipefd) == -1)
		error_bonus("Pipe creation failed");
	if (ft_pipex_bonus(argv, &pipex, argc) < 0)
		error_bonus("Error with the pipe process");
	close(pipex->infile);
	close(pipex->outfile);
	free(pipex);
	return (0);
}
