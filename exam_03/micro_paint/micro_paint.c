#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int	ft_error(FILE *file, char *map)
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
		write(1, "\n", 1);
		h++;
	}
}
int	ft_scan_all(FILE *file,char *map, int width, int height)
{
	int scan2 = 0;
	char type, border;
	float x, y, ex, ey;
	int w, h;
	while ((scan2 = fscanf(file, "%c %f %f %f %f %c\n", &type, &x, &y, &ex, &ey, &border)) == 6)
	{
		if ((type != 'r' && type != 'R') || ex <= 0.0f || ey <= 0.0f)
			return (1);
		ex = ex + x;
		ey = ey + y;
		h = 0;
		while (h < height)
		{
			w = 0;
			while (w < width)
			{
				if (w >= x &&w <= ex && h >= y && h <= ey)
				{
					if (type == 'R' || w < x+1 || w > ex-1 || h < y+1 || h > ey-1)
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
	int	scan1 = 0, width, height;
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
1 arg
2 open
3 scan
4 frame
5 malloc + \0
6 memset
7 scan_all (h < height) (w < width)
8 print_pic
9 free
10 close
*/