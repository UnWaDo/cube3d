#include "cube_map.h"

static int	check_line(t_map *map, int y, int *heroes)
{
	int	x;

	x = 0;
	while (x < map->width && ft_strchr(WHITESPACES, map->map[y][x]))
	{
		if (y > 0 && map->map[y - 1][x] != WALL_CODE && map->map[y - 1][x] != OUB_CODE)
			return (1);
		x++;
	}
	if (x >= map->width || map->map[y][x++] != WALL_CODE)
		return (1);
	while (x < map->width && !ft_strchr(WHITESPACES, map->map[y][x]))
	{
		if ((y == 0 || y == map->height - 1) && map->map[y][x] != WALL_CODE)
			return (1);
		if (y > 0 && map->map[y][x] != WALL_CODE && map->map[y - 1][x] == OUB_CODE)
			return (1);
		if (!ft_strchr(ALLOWED_CHARS, map->map[y][x]))
			return (1);
		if (ft_strchr(HERO_CODES, map->map[y][x]))
			(*heroes)++;
		x++;
	}
	while (x < map->width)
	{
		if (y > 0 && map->map[y - 1][x] != WALL_CODE && map->map[y - 1][x] != OUB_CODE)
			return (1);
		x++;
	}
	return (0);
}

int	check_map(t_map *map)
{
	int		met_hero;
	int		i;

	i = 0;
	met_hero = 0;
	while (i < map->height && met_hero <= 1 && !check_line(map, i, &met_hero))
		i++;
	if (i < map->height)
		print_error_with_number(MAP_LINE_ERR, i + 1);
	else if (met_hero != 1)
		print_error(MAP_HERO_ERR);
	return (met_hero != 1 || i < map->height);
}
