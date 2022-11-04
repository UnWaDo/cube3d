#include "cube_map.h"
#include <stdio.h>

void	print_map(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			printf("%c", map->map[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
}
