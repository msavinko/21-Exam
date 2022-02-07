#include <unistd.h>

int	compare_two_lines(char c, char *str)
{
	int i = 0;
	while (str[i]) 
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}
int compare_one_line(char c, char *str, int index)
{
	int i = 0;
	while (i < index)
	{
		if (c == str[i])
		{
			return (0);
		}
		i++;
	}
	return (1);
}
int main(int argc, char *argv[])
{
	int i = 0;

	if (argc == 3)
	{
		while (argv[1][i])
		{
			if (compare_two_lines(argv[1][i], argv[2]) && compare_one_line(argv[1][i], argv[1], i))
				write(1, &argv[1][i], 1);
			i++;
		}
	}
	write (1, "\n", 1);
	return (0);
}