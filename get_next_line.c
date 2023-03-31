/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leon <leon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 09:49:41 by leon              #+#    #+#             */
/*   Updated: 2023/03/31 16:40:01 by leon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
// #include "get_next_line_utils.c"

int	newline_check(char *s)
{
	if (!s)
		return (0);
	while (*s != '\n' && *s != '\0')
		s++;
	if (*s == '\n')
		return (1);
	else
		return (0);
}

char	*return_line(char *s)
{
	char	*str;
	int		i;
	int		len;

	i = 0;
	len = 0;
	if (!s)
		return (NULL);
	while (s[len] != '\n' && s[len != '\0'])
	{
		len++;
	}
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (s[i] != '\n' && s[i] != '\0')
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\n';
	// if (s)
	// 	free(s);
	return (str);
}

char	*free_stash(char *s)
{
	int		len;
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	len = ft_strlen(s);
	while (s[i] != '\n' && s[i] != '\0')
		i++;
	str = malloc(sizeof(char) * (len - i));
	i++;
	while (s[i])
		str[j++] = s[i++];
	str[j] = '\0';
	if (s)
		free(s);
	return (str);
}

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	char		*line;
	static char	*stash;
	int			n;

	if (!stash)
		stash = ft_strdup("");
	if (fd < 0 || fd > 1023 || BUFFER_SIZE <= 0)
		return (0);
	if (newline_check(stash) == 1 )
			line = return_line(stash);
	n = 0;
	while (n > 0)
	{
		n = read(fd, buffer, BUFFER_SIZE);
		buffer[n] = 0;
		stash = ft_strjoin(stash, buffer);
		if (newline_check(stash) == 1)
		{
			line = return_line(stash);
			stash = free_stash(stash);
			break ;
		}
	}
	return (line);
}
