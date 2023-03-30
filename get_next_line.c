/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leon <leon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 12:36:30 by leon              #+#    #+#             */
/*   Updated: 2023/03/30 18:08:50 by leon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Genere un buffer mais pas la ligne
//  Besoin de \n
//  valeur statique
/* GNL utilise la fonction read. Je dois definir un buffer et je l'envoie dans
 * la stasth lorsque je trouve la nl. Je renvoie la ligne ou j'extrait la line
 * et free la stash pour la prochaine boucle
 * */

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s != (unsigned char)c && *s != '\0')
		s++;
	if (*s == (unsigned char)c)
		return ((char *)s);
	else
		return (0);
}

char	*ft_strdup(const char *s)
{
	size_t	i;
	size_t	len;
	char	*ptr;

	if (!s)
		return (NULL);
	ptr = NULL;
	len = 0;
	while (s[len])
	{
		len++;
	}
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (s[i])
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	free(s1);
	return (str);
}

int newline_check(char *s)
{
	// if (!s)
	// 	return (0);
	while (*s != '\n' && *s != '\0')
		s++;
	if (*s == '\n')
		return (1);
	else
		return (0);
}

char *return_line(char *s)
{
	char	*str;
	int		i;
	int		len;

	i = 0;
	len = 0;
	if (!s)
		return (NULL);
	while (s[len] != '\n')
	{
		len++;
	}
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (s[i] != '\n')
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\n';
	// free(s);
	return (str);
}

char *free_stash(char *s)
{
	int len;
	int i;
	int j;

	char *str;

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
	free(s);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*buffer = NULL;
	char		*line = NULL;
	char		*temp = NULL;
	static char	*stash;
	int			n;
	n = 1;
	if (fd < 0 || fd > 1023 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (n > 0)
	{
		n = read(fd, buffer, BUFFER_SIZE);
		buffer[n] = 0;
		stash = ft_strjoin(stash, buffer);
 		if ( newline_check(stash) == 1)
		{
			line = return_line(stash);
			//free stash et le newline sinon j'imprime la meme ligne
			break;
		}

	}
	stash = free_stash(stash);
	return (line);
}


int	main(int argc, char **argv)
{
	int	fd;
	char	*line;

	(void)argc;
	fd = open("test.txt", O_RDONLY);
	line = "";
	while (line != NULL) //
	{
		line = get_next_line(fd);
		printf("%s", line);
	}
	fd = close(fd);
	return (0);
}
