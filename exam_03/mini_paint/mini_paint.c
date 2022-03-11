#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>

typedef struct s_info
{
	FILE *file;
	int	scan;
	int	scan1;
	int width;
	int height;
	char back;
	char *map;
	int	len;
	char type;
	float x;
	float y;
	float radius;
	char border;
	float	dist;
} t_info;

int	ft_error(t_info *info)
{
	if (info->file)
		fclose(info->file);
	if (info->map)
		free(info->map);
	(void)info;
	write(2, "Error: Operation file corrupted\n", 32);
	return (1);
}
void	ft_init(t_info *info)
{
	info->file = NULL;
	info->map = NULL;
	info->scan = 0;
	info->width = 0;
	info->height = 0;
	info->back = 0;
	info->len = 0;
	info->dist = 0;
}
void	ft_print_pic(t_info *info)
{
	int h = 0;
	while (h < info->height)
	{
		write(1, &info->map[h * info->width], info->width);
		write(1, "\n", 1);
		h++;
	}
}

void ft_draw(t_info *info)
{
	int w, h = 0;
	while (h < info->height)
	{
		w = 0;
		while (w < info->width)
		{
			info->dist = sqrtf(powf(info->x - w, 2.0f) + powf(info->y - h, 2.0f));
			if (info->dist <= info->radius)
			{
				if (info->type == 'C' || info->dist > info->radius - 1)
					info->map[h * info->width + w] = info->border;
			}
			w++;
		}
		h++;
	}
}
int	ft_read_data(t_info *info)
{
	while ((info->scan1 = fscanf(info->file, "%c %f %f %f %c\n", &info->type, &info->x, &info->y, &info->radius, &info->border)) == 5)
	{
		if ((info->type != 'c' && info->type != 'C') || info->radius <= 0.0f)
			return (1);
		ft_draw(info);
	}
	if (info->scan1 != -1)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc != 2)
	{
		write(2, "Error: argument\n", 16);
		return (1);
	}
	ft_init(&info);
	info.file = fopen(argv[1], "r");
	if (info.file == NULL)
		return (ft_error(&info));
	info.scan = fscanf(info.file, "%d %d %c\n", &info.width, &info.height, &info.back);
	if (info.scan != 3 || info.width < 0 || info.width > 300 || info.height < 0 || info.height > 300)
		return (ft_error(&info));
	info.len = info.width * info.height;
	info.map = malloc(info.len + 1);
	memset(info.map, info.back, info.len);
	info.map[info.len] = '\0';

	if (ft_read_data(&info))
		return (ft_error(&info));

	ft_print_pic(&info);	
	free(info.map);
	fclose(info.file);
	return (0);
}