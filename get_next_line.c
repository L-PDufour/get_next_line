/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leon <leon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 09:49:41 by leon              #+#    #+#             */
/*   Updated: 2023/04/04 20:36:31 by leon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "get_next_line_utils.c"

char	*extract_line(char *str)
{
	char	*line;
	int		i;
	int		len;

	i = 0;
	len = 0;
	if (!str)
		return (NULL);
	while (str[len] && str[len] != '\n')
		len++;
	line = malloc(sizeof(char) * (len + i));
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
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash;
	char		*buffer;
	int			read_bytes;

	if (fd < 0 || fd > 1023 || BUFFER_SIZE < 0)
		return (NULL);
	read_bytes = 1;
	stash = ft_strdup("");
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while (!ft_strchr(stash, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		buffer[read_bytes] = '\0';
		stash = ft_strjoin(stash, buffer);
	}
	line = extract_line(stash);
	free(buffer);
	return (line);
}
