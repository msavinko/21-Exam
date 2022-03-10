#include <stdio.h>
#include <unistd.h>

typedef struct s_info
{
	int	width;
	int	height;
	char	back;
}	t_info;

int	main(int argc, char**argv)
{
	FILE	*file;
	t_info	info;

	if (argc != 2)
	{
		write(2, "Error: argument\n", 16);
		return (0);
	}
	if (!(file = fopen(argv[1], "rb")))
	{
		write(2, "Error: Operation file corrupted\n", 12);
		return (0);
	}

	// char string[80];
	// fread(string, sizeof(char), 12, file);
	// printf("%s\n", string);

	fscanf(file, "%d %d %c", &info.width, &info.height, &info.back);
	printf("%d %d %c", info.width, info.height, info.back);

	fclose(file);
	return (0);
}
