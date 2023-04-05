/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldufour <ldufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 09:49:41 by leon              #+#    #+#             */
/*   Updated: 2023/04/05 11:02:53 by ldufour          ###   ########.fr       */
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
	if (!str)
		return (NULL);
	while (str[len] && str[len] != '\n')
		len++;
	line = malloc(sizeof(char) * (len + 2));
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

char	*clean_stash(char *str)
{
	char	*new_stash;
	int		len;
	int		new_stash_len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	new_stash_len = 0;
	while (str[new_stash_len] && str[new_stash_len] != '\n')
		new_stash_len++;
	new_stash = malloc(sizeof(char) * (len - new_stash_len + 1));
	if (!new_stash)
		return (NULL);
	len = 0;
	while (str[++new_stash_len]) // TODO Leak problems
		new_stash[len++] = str[new_stash_len];
	new_stash[len] = '\0';
	free(str);
	return (new_stash);
}
// Dois-je free stash un moment donné ?
char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash;
	char		*buffer;
	int			read_bytes;

	if (fd < 0 || fd > 1023 || BUFFER_SIZE < 0)
		return (NULL);
	read_bytes = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (!ft_strchr(stash, '\n') && read_bytes > 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes <= 0)
			break;
		buffer[read_bytes] = '\0';
		stash = ft_strjoin(stash, buffer); //TODO Leak problems
	}
	line = extract_line(stash);
	stash = clean_stash(stash); //TODO Leak problems
	free(buffer);
	return (line);
}
