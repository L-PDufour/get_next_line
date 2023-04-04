/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leon <leon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 09:49:41 by leon              #+#    #+#             */
/*   Updated: 2023/04/04 16:11:29 by leon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
// #include "get_next_line_utils.c"

char *extract_line(char *str) {
  char *line;
  int i;

  i = 0;
  if (!str)
    return (NULL);
  line = malloc(sizeof(char) * 10);
  while (str[i] != '\n' || str[i]) {
    line[i] = str[i];
    i++;
  }
  line[i] = '\0';
  return (str);
}

char *get_next_line(int fd) {
  char *line;
  char *stash;
  char *buffer;
  int read_bytes;

  read_bytes = 1;
  stash = ft_strdup("");
  buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
  while (!ft_strchr(stash, '\n') && read_bytes != 0) {
    read_bytes = read(fd, buffer, BUFFER_SIZE);
    buffer[read_bytes] = '\0';
    stash = ft_strjoin(stash, buffer);
  }
  line = extract_line(stash);
  free(buffer);
  return (line);
}
