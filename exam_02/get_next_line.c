#include "get_next_line.h"

int get_next_line(char **line)
{
	int result = 0;
	int i = 0;
	char *buffer = malloc(100000);
	*line = buffer;
	
	while((result = read(0, &buffer[i], 1)) > 0 && buffer[i] != '\n')
		i++;
	buffer[i] = '\0';
	return (result);
}
#include <stdio.h>
int main(void)
{
	char *line = NULL;
	while (get_next_line(&line) > 0)
	{
		printf("%s\n", line);
		free(line);
		line = NULL;
	}
	printf("%s\n", line);
	free(line);
	line = NULL;
}


//leaks --atExit -- ./a.out
//gcc -g -fsanitize=address ./a.out
