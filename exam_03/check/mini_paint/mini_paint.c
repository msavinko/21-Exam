#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int ft_error(FILE *file, char *map)
{
	if (map)
		free(map);
	if (file)
		fclose(file);
	write(1, "Error: Operation file corrupted\n", 32);
	return (1);
}

void	ft_print_pic(char *map, int width, int height)
{
	int h = 0;
	while (h < height)
	{
		write(1, &map[h * width], width);
		write (1, "\n", 1);
		h++;
	}
}

int	ft_scan_all(FILE *file, char *map, int width, int height)
{
	int	scan2 = 0, w, h;
	char border, type;
	float x, y, r, dist;
	while ((scan2 = fscanf(file, "%c %f %f %f %c\n", &type, &x, &y, &r, &border)) == 5)
	{
		if ((type != 'c' && type != 'C') || r <= 0.0f)
			return (1);
		h = 0;
		while (h < height)
		{
			w = 0;
			while (w < width)
			{
				dist = sqrtf(powf(x - w, 2.0f) + powf(y - h, 2.0f));
				if (dist <= r)
				{
					if (type == 'C' || dist > r - 1)
						map[h * width + w] = border;
				}
				w++;
			}
			h++;
		}
	}
	if (scan2 != -1)
		return (1);
	return (0);
}

int main(int argc, char **argv)
{
	FILE *file = NULL;
	char *map = NULL;
	int scan1 = 0;
	int width, height;
	char back;

	if (argc != 2)
	{
		write(1, "Error: argument\n", 16);
		return (1);
	}
	if (!(file = fopen(argv[1], "r")))
		return (ft_error(file, map));
	if ((scan1 = fscanf(file, "%d %d %c\n", &width, &height, &back)) != 3)
		return (ft_error(file, map));
	if (width <= 0 || width > 300 || height <= 0 || height > 300)
		return (ft_error(file, map));
	int len = width * height;
	if (!(map = malloc(len + 1)))
		return (ft_error(file, map));
	map[len] = '\0';
	memset(map, back, len);
	if (ft_scan_all(file, map, width, height))
		return (ft_error(file, map));
	ft_print_pic(map, width, height);
	free(map);
	fclose(file);
	return (0);
}

/*
1. arg != 2
2. open !
3. scanf !=3
4. frames <= 0 > 300
5. malloc + \0
6. memset
7. scan all
8. print_pic
9.free
10.close
*/