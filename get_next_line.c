/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldufour <ldufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 09:49:41 by leon              #+#    #+#             */
/*   Updated: 2023/04/05 14:17:31 by ldufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
// #include "get_next_line_utils.c"

char	*extract_line(char *str)
{
	char	*line;
	int		i;
	int		len;

	i = 0;
	len = 0;
	if (!str[i])
		return (NULL);
	while (str[len] && str[len] != '\n')
		len++;
	line = malloc(sizeof(char) * (len + 2)); //TODO Leak problems
	if (!line)
		return (NULL);
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char *fill_stash(char *stash, int fd)
{
	char		*buffer;
	int			read_bytes;

	read_bytes = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (!ft_strchr(stash, '\n') && read_bytes > 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[read_bytes] = '\0';
		stash = ft_strjoin(stash, buffer); //TODO Leak problems
	}
	free (buffer);
	return (stash);
}

char *clean_stash(char *str)
{
    char *new_stash;
	int i;
	int j;

    i = 0;
	j = 0;
	if (!str)
        return (NULL);

    while (str[i] && str[i] != '\n')
        i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
    new_stash = malloc(sizeof(char) * ((ft_strlen(str) - i) + 1));
    if (!new_stash)
        return (NULL);
	i++;
	while(str[i])
		new_stash[j++] = str[i++];
	new_stash[j] = '\0';
	free(str);
	return (new_stash);

}

// Dois-je free stash un moment donné ?
// Je dois sortir de ma boucle si vide
char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash;

	if (fd < 0 || fd > 1023 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = fill_stash(stash, fd);
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	stash = clean_stash(stash); //TODO Leak problems
	return (line);
}


