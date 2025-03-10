# include <unistd.h>
# include <stdlib.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1024
#endif

char *get_next_line(int fd)
{
	int i;

	i = 0;
	char character;
	int rd = read(fd, &character, BUFFER_SIZE - BUFFER_SIZE + 1);
	char *line = malloc(100000);

	if(BUFFER_SIZE <= 0)
	{
		free(line);
		return(NULL);
	}
	while(rd > 0)
	{
		line[i] = character;
		i++;
		if(character == '\n')
			break ;
		rd = read(fd, &character, BUFFER_SIZE - BUFFER_SIZE + 1);
	}
	line[i] = '\0';
	if(rd == -1 || i == 0 || (line[i - 1] && rd == 0))
	{
		free(line);
		return(NULL);
	}
	return(line);
}


#include <fcntl.h>
#include <stdio.h>
int	main(int argc, char **argv)
{
	int		fd;
	char	*line;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		line = get_next_line(fd);
		while (line != NULL)
		{
			printf("%s", line);
			free(line);
			line = get_next_line(fd);
		}
		close(fd);
	}
	return (0);
}
