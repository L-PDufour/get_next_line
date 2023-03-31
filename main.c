#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.c"
#include "get_next_line_utils.c"



int	main(int argc, char **argv)
{
	int		fd;
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
