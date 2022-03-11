#ifndef MINI_PAINT_H
# define MINI_PAINT_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <math.h>
# include <stdlib.h>


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

#endif