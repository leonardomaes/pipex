/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaes <lmaes@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:12:49 by lmaes             #+#    #+#             */
/*   Updated: 2024/07/02 11:12:51 by lmaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_line(int fd, char *backup)
{
	int		read_bytes;
	char	*buffer;

	read_bytes = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (read_bytes != 0 && !ft_strchr(backup, '\n'))
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(backup);
			free(buffer);
			return (NULL);
		}
		buffer[read_bytes] = '\0';
		backup = ft_strjoin(backup, buffer);
	}
	free(buffer);
	return (backup);
}

char	*dup_line(char *backup)
{
	char	*line;
	size_t		i;

	i = 0;
	if (!backup[i])
		return (NULL);
	while (backup[i] != '\n' && backup[i])
		i++;
	line = malloc((i + 2) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (backup[i] && backup[i] != '\n')
	{
		line[i] = backup[i];
		i++;
	}
	if (backup[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*new_line(char *backup)
{
	int		i;
	int		j;
	char	*new_line;

	i = 0;
	while (backup[i] && backup[i] != '\n')
		i++;
	if (!backup[i])
	{
		free(backup);
		return (NULL);
	}
	i++;
	new_line = (char *)malloc(sizeof(char) * (ft_strlen(backup) - i + 1));
	if (!new_line)
		return (NULL);
	j = 0;
	while (backup[i])
		new_line[j++] = backup[i++];
	new_line[j] = '\0';
	free(backup);
	return (new_line);
}

char	*get_next_line(int fd)
{
	static char	*backup[MAX_FILES];
	char		*line;

	if (fd < 0 || fd > MAX_FILES || BUFFER_SIZE <= 0)
		return (NULL);
	backup[fd] = get_line(fd, backup[fd]);
	if (!backup[fd])
		return (NULL);
	line = dup_line(backup[fd]);
	backup[fd] = new_line(backup[fd]);
	return (line);
}
