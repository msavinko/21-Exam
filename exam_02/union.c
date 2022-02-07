#include <unistd.h>

int	compare(char *str1, char c, int index)
{
	int i = 0;
	while (i < index)
	{
		if (c == str1[i])
			return (0);
		i++;
	}
	return (1);
}

int main(int argc, char *argv[])
{
	int i = 0, len;
	if (argc == 3)
	{
		while (argv[1][i])
		{
			if (compare(argv[1], argv[1][i], i))
				write (1, &argv[1][i], 1);
			i++;
		}
		len = i;
		i = 0;
		while (argv[2][i])
		{
			if (compare(argv[2], argv[2][i], i))
			{
				if (compare(argv[1], argv[2][i], len))
					write (1, &argv[2][i], 1);
			}
			i++;
		}
	}
	write (1, "\n", 1);
	return (0);
}