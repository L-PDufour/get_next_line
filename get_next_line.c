/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leon <leon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 09:49:41 by leon              #+#    #+#             */
/*   Updated: 2023/04/08 17:09:54 by leon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// #include "get_next_line_utils.c"

char	*extract_line(char *str)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str[i])
	{
		// ft_free(&str);
		return (NULL);
	}
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	i++;
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
	{
		ft_free(&line);
		return (NULL);
	}
	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		line[j++] = str[i++];
	if (str[i] == '\n')
		line[j++] = str[i++];
	line[j] = 0;
	return (line);
}

char	*fill_stash(char *stash, int fd)
{
	char	*buffer;
	int		read_bytes;

	read_bytes = 1;
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
	{
		ft_free(&buffer);
		return (NULL);
	}
	while (!ft_strchr(stash, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes < 0)
		{
			ft_free(&buffer);
			ft_free(&stash);
			return (NULL);
		}
		buffer[read_bytes] = 0;
		stash = ft_strjoin(stash, buffer);
	}
	ft_free(&buffer);
	return (stash);
}

char	*clean_stash(char *str)
{
	char	*new_stash;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str)
	{
		ft_free(&str);
		return (NULL);
	}
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		ft_free(&str);
		return (NULL);
	}
	new_stash = malloc(sizeof(char) * ((ft_strlen(str) - i + 1)));
	if (!new_stash)
	{
		ft_free(&new_stash);
		return (NULL);
	}
	i++;
	while (str[i])
		new_stash[j++] = str[i++];
	new_stash[j] = 0;
	ft_free(&str);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash = NULL;

	line = NULL;
	if (fd < 0 || fd > 1023 || BUFFER_SIZE <= 0)
		return (NULL);
	if (read(fd, line, 0) < 0)
	{
		ft_free(&stash);
		return (stash);
	}
	stash = fill_stash(stash, fd);
	if (!stash)
	{
		ft_free(&stash);
		return (NULL);
	}
	line = extract_line(stash);
	stash = clean_stash(stash);
	// printf("line est %s\n", line);
	return (line);
}
