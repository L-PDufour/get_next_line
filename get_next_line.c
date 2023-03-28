/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leon <leon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 12:36:30 by leon              #+#    #+#             */
/*   Updated: 2023/03/20 14:24:05 by leon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <string.h>

size_t ft_strlen(const char *s) {
  size_t i;

  if (!s)
    return (0);
  i = 0;
  while (s[i])
    i++;
  return (i);
}

char *ft_strjoin(char const *s1, char const *s2) {
  char *str;
  int i;
  int j;

  i = 0;
  j = 0;
  if (!s1 || !s2)
    return (NULL);
  str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
  if (!str)
    return (NULL);
  while (s1[i] != '\0') {
    str[i] = s1[i];
    i++;
  }
  while (s2[j] != '\0') {
    str[i] = s2[j];
    i++;
    j++;
  }
  str[i] = '\0';
  return (str);
}

char *get_next_line(int fd) {
  char *line;
  char *buffer;
  static char *stash;
  int i;

  if (fd < 0 || BUFFER_SIZE <= 0)
    return (NULL);
  buffer = malloc(BUFFER_SIZE + 1);
  if (!buffer)
    return (NULL);
  while ((i = read(fd, buffer, BUFFER_SIZE)) > 0) {
    stash = ft_strjoin(stash, buffer);
  }
  return (stash);
}

int main(void) {
  int fd;
  char *line;

  fd = open("tests.txt", O_RDONLY);
  while (1) {
    line = get_next_line(fd);
    printf("%s", line);
    if (line == NULL)
      break;
    free(line);
  }
  return (0);
}
