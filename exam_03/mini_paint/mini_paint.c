#include <stdio.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int	ft_error(FILE *file, char * map)
{
	if (file)
		fclose(file);
	if (map)
		free(map);
	write(1, "Error: Operation file corrupted\n", 32);
	return (1);
}
void	ft_print(char *map, int width, int height)
{
	int h = 0;
	while (h < height)
	{
		write(1, &map[h * width], width);
		write(1, "\n", 1);
		h++;
	}
}

int	ft_scan_all(FILE *file, char *map, int width, int height)
{
	int	scan2;
	int w, h = 0;
	char type, border;
	float x, y, r, dist;
	while ((scan2 = fscanf(file, "%c %f %f %f %c", &type, &x, &y, &r, &border)) == 5)
	{
		if (type != 'C' || type != 'c' || r <= 0.0f)
			return (1);
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
	FILE	*file;
	int	scan1;
	int	width, height;
	char back;
	char *map;

	map = NULL; file = NULL;
	if (argc != 2)
	{
		write(1, "Error: argument\n", 16);
		return (1);
	}
	if (!(file = fopen(argv[1], "r")))
		return (ft_error(file, map));
	if ((scan1 = fscanf(file, "%d %d %c", &width, &height, &back)) != 3)
		return (ft_error(file, map));
	if (width <= 0 || width > 300 || height <= 0 || height > 300)
		return (ft_error(file, map));
	if (!(map = malloc(width * height + 1)))
		return (ft_error(file, map));
	map[width * height] = '\0';
	memset(map, back, width * height);
	if (ft_scan_all(file, map, width, height))
		return (ft_error(file, map));
	ft_print(map, width, height);
	free(map);
	fclose(file);	
	return (0);
}