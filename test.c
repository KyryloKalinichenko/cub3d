#include <stdio.h>
#include "cub_head.h"

int main()
{
	char *line;
	int fd;
	int fd2;

	line = "HEllo";
	fd = open("lol", O_RDONLY);
	fd2 = 0;
	while (0 < (fd2 = get_next_line(fd, &line)))
	{
		printf("%s", line);
		printf("\n--------------\n");
		free(line);
		printf("%i\n", fd2);
	}
	if (fd > 0)
		free(line);
	close(fd);
}