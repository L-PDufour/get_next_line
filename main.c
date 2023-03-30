#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>



int	main(int argc, char **argv)
{
	int		fd;
	int		i;
	char	line;
	static char saved;
	char *test;
	i = 0;
	fd = open("test.txt", O_RDONLY);
	while (i < 2)
	{
		read(fd, line, BUFFER_SIZE);
		test = ft_strjoin(saved , line);
		printf("%s", test);
		//  free(line);
		i++;
	}
	close(fd);
	return (0);
}
