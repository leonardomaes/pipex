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

#include "../includes/pipex.h"

void	error(const char *strerr, t_pipex *pipex)
{
	if (pipex->cmd_paths)
	{
		free_split(pipex->cmd_paths);
		free_split(pipex->args);
	}
	free(pipex);
	perror(strerr);
	exit(1);
}

void	free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free (str);
}

int	open_files(t_pipex **pipex_tab, char *argv[], int argc)
{
	(*pipex_tab)->infile = open(argv[1], O_RDONLY, 0777);
	if ((*pipex_tab)->infile < 1)
		return (-1);
	(*pipex_tab)->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC,
			0644);
	if ((*pipex_tab)->outfile < 1)
		return (-1);
	return (0);
}

char	*get_path(char **envp)
{
	if (!*envp)
    	return (NULL);
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

char	*get_command(char *cmd, char **path)
{
	char	*comm;
	char	*temp;

	while (*path)
	{
		temp = ft_strjoin(*path, "/");
		if (!temp)
		{
			perror("Error allocating memory for command");
			return (NULL);
		}
		comm = ft_strjoin(temp, cmd);
		free(temp);
		if (!comm)
		{
			perror("Error allocating memory for command");
			return (NULL);
		}
		if (access(comm, 0) == 0)
			return (comm);
		free(comm);
		path++;
	}
	return (NULL);
}
