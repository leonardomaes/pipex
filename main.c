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

#include "pipex.h"

char	**get_command(char	*argv)
{
	char **comm;

	comm = ft_split(argv, ' ');
	comm[0] = ft_strjoin("/bin/", comm[0]);
	comm[2] = NULL;
	return (comm);
}

int	ft_execve(t_pipex *pipex_tab)
{
	pid_t	pid;
	int		val;

	if (pipe(pipex_tab->pipefd) == -1)
	{
		printf("Error on pipe\n");
		return (-1);
	}
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		val = execve(pipex_tab->comm[0], pipex_tab->comm, NULL);
		if (val == -1)
			perror("Error");
	}
	else
	{
		waitpid(pid, NULL, 0);
		printf("Done with execve\n");
	}
	return (0);
}

int		ft_pipex(char **argv, t_pipex *pipex_tab)
{
	int i;

	i = 2;
	while (argv[i+1] != NULL)	// Dentro fazer o execve e o pipe
	{
		pipex_tab->comm = get_command(argv[i]);
		if (!pipex_tab->comm)
			return (-1);
		if (ft_execve(pipex_tab) < 0)
			return (-1);
		i++;
	}
	return (1);
}

int main(int argc, char *argv[])
{
	t_pipex	*pipex;

	pipex = NULL;
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
	if (argc >= 5)
	{
		pipex->infile = open(argv[1], O_RDONLY, 0777);
		if (pipex->infile < 1)
			error("Error opening file");
		pipex->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (pipex->outfile < 1)
			error("Error opening file");
	}
	if (ft_pipex(argv, pipex) < 0)
		error("Error with the pipe");
	close(pipex->infile);
	close(pipex->outfile);
	free(pipex);
	return (0);
}